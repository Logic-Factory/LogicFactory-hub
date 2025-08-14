//
// Created by zephyr on 2022/9/9.
//

#include <utility>

#include "../share/netlist.h"
using namespace std;

bool cmp_Depth(const PASyn::Cut& cut_1, const PASyn::Cut& cut_2) {
    return cut_1.min_depth < cut_2.min_depth || (cut_1.min_depth == cut_2.min_depth && cut_1.area < cut_2.area)
           || (cut_1.min_depth == cut_2.min_depth && cut_1.area == cut_2.area && cut_1.area_flow < cut_2.area_flow) || (cut_1.min_depth == cut_2.min_depth && cut_1.area == cut_2.area && cut_1.area_flow == cut_2.area_flow && cut_1.power < cut_2.power);
}

bool cmp_area_flow(const PASyn::Cut& cut_1, const PASyn::Cut& cut_2) {
    return cut_1.area_flow < cut_2.area_flow || (cut_1.area_flow == cut_2.area_flow && cut_1.fin < cut_2.fin)
           || (cut_1.area_flow == cut_2.area_flow && cut_1.fin == cut_2.fin && cut_1.min_depth < cut_2.min_depth) || (cut_1.area_flow == cut_2.area_flow && cut_1.fin == cut_2.fin && cut_1.min_depth == cut_2.min_depth && cut_1.power < cut_2.power);
}

bool cmp_Area(const PASyn::Cut& cut_1, const PASyn::Cut& cut_2) {
    return cut_1.area < cut_2.area || (cut_1.area == cut_2.area && cut_1.fin < cut_2.fin)
           || (cut_1.area == cut_2.area && cut_1.fin == cut_2.fin && cut_1.min_depth < cut_2.min_depth)|| (cut_1.area == cut_2.area && cut_1.fin == cut_2.fin && cut_1.min_depth == cut_2.min_depth && cut_1.power < cut_2.power);
}

bool cmp_sad(const PASyn::Cut& cut_1, const PASyn::Cut& cut_2) { // compare static power per node
    return cut_1.sad < cut_2.sad || (cut_1.sad == cut_2.sad && cut_1.min_depth < cut_2.min_depth) || (cut_1.sad == cut_2.sad && cut_1.min_depth == cut_2.min_depth && cut_1.area < cut_2.area)
           || (cut_1.sad == cut_2.sad && cut_1.min_depth == cut_2.min_depth && cut_1.area == cut_2.area && cut_1.area_flow < cut_2.area_flow);
}

bool cmp_oisa(const PASyn::Cut& cut_1, const PASyn::Cut& cut_2) { // compare out-cut in-cut switching activity
    return cut_1.oisa < cut_2.oisa || (cut_1.oisa == cut_2.oisa && cut_1.min_depth < cut_2.min_depth) || (cut_1.oisa == cut_2.oisa && cut_1.min_depth == cut_2.min_depth && cut_1.area < cut_2.area)
           || (cut_1.oisa == cut_2.oisa && cut_1.min_depth == cut_2.min_depth && cut_1.area == cut_2.area && cut_1.area_flow < cut_2.area_flow);
}

bool cmp_iad(const PASyn::Cut& cut_1, const PASyn::Cut& cut_2) { // compare input arrival time differences
    return cut_1.iad < cut_2.iad || (cut_1.iad == cut_2.iad && cut_1.min_depth < cut_2.min_depth) || (cut_1.iad == cut_2.iad && cut_1.min_depth == cut_2.min_depth && cut_1.area < cut_2.area)
           || (cut_1.iad == cut_2.iad && cut_1.min_depth == cut_2.min_depth && cut_1.area == cut_2.area && cut_1.area_flow < cut_2.area_flow);
}

bool cmp_power(const PASyn::Cut& cut_1, const PASyn::Cut& cut_2) { // compare power
    double coefficient = 6.32147e-2;
    double cut1_power = cut_1.oisa*coefficient+cut_1.sad*cut_1.input_nodes.size();
    double cut2_power = cut_2.oisa*coefficient+cut_2.sad*cut_2.input_nodes.size();
    return cut1_power < cut2_power || (cut1_power == cut2_power && cut_1.min_depth < cut_2.min_depth) || (cut1_power == cut2_power && cut_1.min_depth == cut_2.min_depth && cut_1.area < cut_2.area)
           || (cut1_power == cut2_power && cut_1.min_depth == cut_2.min_depth && cut_1.area == cut_2.area && cut_1.area_flow < cut_2.area_flow);
}

std::string select_standard_cell(PASyn::Technology& technology, const std::vector<std::string>& cells, const std::string& target) {
    double min_value = INT_MAX;
    double coefficient = 0.2357964;
    std::string result;
    //for(auto& cell: cells)
      //  std::cout<<cell<<" ";
    //std::cout<<"\n";
    for(auto& cell_name: cells) {
        auto& cell = technology.cells[cell_name];
        if (target == "area" || target == "area_flow") {
            if(min_value > cell->area) {
                result = cell->name;
                min_value = cell->area/cell->inputs.size();
            }
        } else if (target == "delay" || target == "depth") {
            if(min_value > cell->ave_delay) {
                result = cell->name;
                min_value = cell->ave_delay;
            }
        } else if (target == "power" || target == "glitch") {
            if(min_value > cell->ave_internal) {
                result = cell->name;
                min_value = (cell->ave_internal*coefficient + cell->leakage)/cell->inputs.size();
            }
        } else {
            assert(false);
        }
    }
    return result;
}

double get_area(PASyn::Technology& technology, PASyn::Netlist &netlist, const string& now, map<string, int> counter, map<set<string>, PASyn::TruthTable*> cut_to_truth[], map<string, int>& node_index, map<string, double>& area_map,  map<PASyn::TruthTable, std::vector<string>>& technology_truth_tables, string target) {
    if (netlist.has_node(now)->inputs.empty())
        return 0;
    double res;
    if(check_equivalence(cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut_inputs], technology_truth_tables).empty())
        res = INT_MAX;
    else
        res = area_map[select_standard_cell(technology, check_equivalence(cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut_inputs], technology_truth_tables), target)];

    for (const string& input : netlist.has_node(now)->best_cut_inputs) {
        if (counter[input] == 0) {
            double input_area = get_area(technology, netlist, input, counter, cut_to_truth, node_index, area_map, technology_truth_tables, target);
            if(abs(input_area - INT_MAX) < 1e-4)
                res = INT_MAX;
            else
                res += input_area;
        }
    }
    return res;
}


double get_sad(PASyn::Technology& technology, PASyn::Netlist &netlist, const string& now, map<set<string>, PASyn::TruthTable*> cut_to_truth[], map<string, double>& area_map,map<string, int>& node_index, map<PASyn::TruthTable, std::vector<string>>& technology_truth_tables, string target) {
    double res;
    int node_count = 0;
    if(check_equivalence(cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut_inputs], technology_truth_tables).empty())
        res = INT_MAX;
    else {
        std::queue<std::string> q;
        std::map<std::string, bool> visited;
        q.push(now);
        while(!q.empty()) {
            auto cur_node = q.front();
            q.pop();
            for (auto &input: netlist.has_node(cur_node)->inputs) {
                if (visited[input] ||
                    netlist.has_node(now)->best_cut_inputs.find(input) != netlist.has_node(now)->best_cut_inputs.end())
                    continue;
                visited[input] = true;
                node_count++;
                q.push(input);
            }
        }
        res = area_map[select_standard_cell(technology, check_equivalence(cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut_inputs],
                                         technology_truth_tables), target)] / node_count;
    }
    return res;
}

double get_oisa(PASyn::Netlist &netlist, const string& now, map<set<string>, PASyn::TruthTable*> cut_to_truth[], map<string, double>& area_map,map<string, int>& node_index, map<PASyn::TruthTable, std::vector<string>>& technology_truth_tables) {
    double in_cell_sa=0, out_cell_sa=0;
    double res;
    if(check_equivalence(cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut_inputs], technology_truth_tables).empty())
        res = INT_MAX;
    else {
        for(auto& cut_input: netlist.has_node(now)->best_cut_inputs) {
            for(auto& entry : netlist.has_node(cut_input)->inputs)
                out_cell_sa += netlist.has_node(entry)->probability_1[0] * (1-netlist.has_node(entry)->probability_1[0]);
        }
        out_cell_sa += netlist.has_node(now)->probability_1[0] * (1-netlist.has_node(now)->probability_1[0]);

        for(auto& cut_input: netlist.has_node(now)->best_cut_inputs) {
            in_cell_sa += netlist.has_node(cut_input)->probability_1[0] * (1-netlist.has_node(cut_input)->probability_1[0]);
        }
        res = out_cell_sa / in_cell_sa;
        // TODO: calculate in_cell_sa in a more precise way
    }
    return res;
}

double get_iad(PASyn::Netlist &netlist, const string& now, map<set<string>, PASyn::TruthTable*> cut_to_truth[], map<string, double>& area_map,map<string, int>& node_index, map<PASyn::TruthTable, std::vector<string>>& technology_truth_tables) {
    double res;
    int min=INT_MAX, max=INT_MIN;
    if(check_equivalence(cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut_inputs], technology_truth_tables).empty())
        res = INT_MAX;
    else {
        for(auto& cut_input: netlist.has_node(now)->best_cut_inputs) {
            max = max > netlist.has_node(cut_input)->max_depth ? max : netlist.has_node(cut_input)->max_depth;
            min = min < netlist.has_node(cut_input)->max_depth ? min : netlist.has_node(cut_input)->max_depth;
        }
        res = max - min;
    }
    return res;
}

void reference(PASyn::Netlist& netlist, const string& now, map<string, bool>& used, map<string, bool> visited, map<string, int> counter, string cell_type="un_mapped") {
    if (netlist.has_node(now)->inputs.empty())
        return;
    visited[now] = true;
    netlist.has_node(now)->cell_type = std::move(cell_type);
    for (const string& input : netlist.has_node(now)->best_cut_inputs) {
        used[input] = true;
        counter[input]++;
        if (!visited[input])
            reference(netlist, input, used, visited, counter, netlist.has_node(input)->cell_type);
    }
}

void dereference(PASyn::Technology& technology, PASyn::Netlist& netlist, const string& now, map<string, bool>& used, double &area_mem, map<string, int>& counter, map<string, double>& area_map, map<set<string>, PASyn::TruthTable*> cut_to_truth[], map<string, int>& node_index, map<PASyn::TruthTable, std::vector<string>>& technology_truth_tables, const string& target) {
    if (netlist.has_node(now)->inputs.empty())
        return;
    if(check_equivalence(cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut_inputs], technology_truth_tables).empty())
        area_mem = INT_MAX;
    else
        area_mem+= area_map[select_standard_cell(technology, check_equivalence(cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut_inputs], technology_truth_tables), target)];
    for (const string& input : netlist.has_node(now)->best_cut_inputs) {
        if (counter[input] > 0) {
            counter[input] = counter[input] - 1;
            if (counter[input] == 0) {
                used[input] = false;
                //if(now.find("_inv") != std::string::npos)
                //    netlist.delete_inverter(now);
                dereference(technology, netlist, input, used, area_mem, counter, area_map, cut_to_truth, node_index, technology_truth_tables, target);
            }
        }
    }
}

void presetting(PASyn::Technology& technology, map<PASyn::TruthTable, std::vector<string>>& truth_tables, map<string, double> & area_map) {
    for(auto& standard_cell: technology.cells) {
        PASyn::TruthTable truth_table {standard_cell.second->functions[0]};
        truth_tables[truth_table].emplace_back(standard_cell.first);
        area_map[standard_cell.first] = standard_cell.second->area;
    }
}

double Recover(PASyn::Technology& technology, PASyn::Netlist& netlist, map<string, int>& node_index, map<string, int> counter, map<set<string>, PASyn::TruthTable*> cut_to_truth[], map<string, bool>& used, map<string, double>& area_map, map<PASyn::TruthTable, std::vector<string>>& technology_truthtable, string target) {
    map<string, bool> visited;
    queue<string> Q;
    used.clear();
    counter.clear();
    double area = 0;
    unsigned int dep = 0;
    for (auto output : netlist.outputs) {
        Q.push(output->name);
        visited[output->name] = true;
        used[output->name] = true;
        dep = max(dep, netlist.has_node(output)->min_depth);
    }


    while (!Q.empty()) {
        string now = Q.front();
        Q.pop();
        netlist.has_node(now)->fin = (1.0 * netlist.has_node(now)->fin + 2 * counter[now]) / 3;   // fanin refs used in abc
        if (netlist.has_node(now)->inputs.empty())
            continue;
        area += area_map[select_standard_cell(technology, check_equivalence(cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut.input_nodes], technology_truthtable), target)];
        for (const string& st : netlist.has_node(now)->best_cut.input_nodes) {
            counter[st] = counter[st] + 1;
            used[st] = true;
            if (!visited[st]) {
                Q.push(st);
                visited[st] = true;
            }
        }
        //if(now.find("_inv") != std::string::npos)
        //    netlist.delete_inverter(now);
    }
    return area;
}

void cut_enumeration(PASyn::Technology& technology, vector<string>& topology_result, PASyn::Netlist& netlist, map<string, int>& node_index, map<string, int> counter, map<set<string>, PASyn::TruthTable*> cut_to_truth[], map<string, bool>& used, map<string, double>& area_map, const string& target, map<PASyn::TruthTable, std::vector<string>>& technology_truth_tables, int max_input_size= 4, unsigned int num_max_stored_cuts= 20) {
    map<string, bool> visited;
    for (const string &now: topology_result) {
        if (netlist.has_node(now)->inputs.empty())
            continue;
        assert(netlist.has_node(now)->inputs.size() <= 2);
        if (netlist.has_node(now)->inputs.size() == 2) {
            string input1 = netlist.has_node(now)->inputs[0];
            string input2 = netlist.has_node(now)->inputs[1];
            for (int t = 1; t <= max_input_size; t++)
                for (const set<string> &c1: netlist.has_node(input1)->cuts[t]) {
                    for (int k = 1; k <= max_input_size; k++)
                        for (const set<string> &c2: netlist.has_node(input2)->cuts[k]) {
                            set<string> st = c1;
                            st.insert(c2.begin(), c2.end());
                            if (st.size() > (unsigned) max_input_size)
                                continue;
                            auto *truth_table = new PASyn::TruthTable();
                            truth_table->generate_input_2(cut_to_truth[node_index[input1]][c1],
                                                          cut_to_truth[node_index[input2]][c2], c1, c2, st,
                                                          netlist.has_node(now)->functions[0].type);
                            auto result = check_equivalence(truth_table, technology_truth_tables, true);
                            if (!result.first.empty()) {
                                netlist.has_node(now)->cuts[st.size()].insert(st);
                                cut_to_truth[node_index[now]].insert(
                                        pair<set<string>, PASyn::TruthTable *>(st, truth_table));
                                //netlist.add_inverter(result.second, now);
                            } else
                                //delete truth_table;
                                continue;
                        }
                }
        }

        if (netlist.has_node(now)->inputs.size() == 1) {
            string input1 = netlist.has_node(now)->inputs[0];
            for (int k = 1; k <= max_input_size; k++)
                for (const set<string> &c1: netlist.has_node(input1)->cuts[k]) {
                    auto *truth_table = new PASyn::TruthTable();
                    truth_table->generate_input_1(cut_to_truth[node_index[input1]][c1],
                                                  netlist.has_node(now)->functions[0].type);
                    if (check_equivalence(truth_table, technology_truth_tables).empty()) {
                        netlist.has_node(now)->cuts[k].insert(c1);
                        cut_to_truth[node_index[now]].insert(pair<set<string>, PASyn::TruthTable *>(c1, truth_table));
                    } else //delete truth_table;
                        continue;
                }
        }

        set<string> last_best_cut_name = netlist.has_node(now)->best_cut_inputs;
        double Area_mem = 0;

        if (used[now])
            dereference(technology, netlist, now, used, Area_mem, counter, area_map, cut_to_truth, node_index,
                        technology_truth_tables, target);

        vector<PASyn::Cut> Cuts[10], Ct;
        for (int k = 1; k <= max_input_size; k++) {
            for (const set<string> &ct: netlist.has_node(now)->cuts[k]) {
                unsigned int dep = 0, fin = 0;
                double area = 0, sad = 0, oisa = 0, iad = 0;
                double AF;
                if (target == "area")
                    AF = netlist.has_node(now)->area;
                else if (target == "area_flow")
                    AF = 0;
                for (const string &nt: ct) {
                    dep = max(dep, netlist.has_node(nt)->min_depth);
                    if (target == "area_flow")
                        AF += netlist.has_node(nt)->area_flow;
                    fin += counter[nt];
                }
                dep++;
                if (dep > netlist.has_node(now)->min_depth)
                    continue;
                netlist.has_node(now)->best_cut_inputs = ct;
                area = get_area(technology, netlist, now, counter, cut_to_truth, node_index, area_map,
                                technology_truth_tables, target);
                sad = get_sad(technology, netlist, now, cut_to_truth, area_map, node_index, technology_truth_tables,
                              target);
                oisa = get_oisa(netlist, now, cut_to_truth, area_map, node_index, technology_truth_tables);
                iad = get_oisa(netlist, now, cut_to_truth, area_map, node_index, technology_truth_tables);
                if (target == "area_flow")
                    AF = (AF + area) / max(1.0, 1.0 * fin);
                //printf("%d\n", area);
                Cuts[k].emplace_back(ct, now, dep, area, fin, AF, sad, oisa, iad);
                Ct.emplace_back(ct, now, dep, area, fin, AF, sad, oisa, iad);
            }
        }
        for (int k = 1; k <= max_input_size; k++) {
            if (target == "area")
                sort(Cuts[k].begin(), Cuts[k].end(), cmp_Area);
            else if (target == "area_flow")
                sort(Cuts[k].begin(), Cuts[k].end(), cmp_area_flow);
            else if (target == "power")
                sort(Cuts[k].begin(), Cuts[k].end(), cmp_power);
            else if (target == "glitch")
                sort(Cuts[k].begin(), Cuts[k].end(), cmp_iad);
            netlist.has_node(now)->cuts[k].clear();
            unsigned int len = Cuts[k].size();
            for (unsigned int i = 0; i < min(num_max_stored_cuts, len); i++) {
                netlist.has_node(now)->cuts[k].insert(Cuts[k][i].input_nodes);
            }
        }
        netlist.has_node(now)->cuts[1].insert(set<string>{now});
        sort(Ct.begin(), Ct.end(), cmp_Area);
        if (Ct.empty() || Ct[0].area > Area_mem)
            netlist.has_node(now)->best_cut_inputs = last_best_cut_name;
        else {
            if (target == "area_flow")
                netlist.has_node(now)->area_flow = Ct[0].area_flow;
            netlist.has_node(now)->min_depth = Ct[0].min_depth;
            netlist.has_node(now)->best_cut_inputs = Ct[0].input_nodes;
            netlist.has_node(now)->best_cut = Ct[0];
        }
        if (used[now]) {
            auto result = PASyn::check_equivalence(
                    cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut_inputs], technology_truth_tables, true);
            reference(netlist, now, used, visited, counter, select_standard_cell(technology, result.first, target));
            netlist.has_node(now)->num_inverters = result.second.first + result.second.second;
        }
    }
}

void cut_enumeration_initial(PASyn::Technology& technology, PASyn::Netlist& netlist, map<string, int>& node_index, map<set<string>, PASyn::TruthTable*> cut_to_truth[], vector<string>& topology_result, map<string, double>& area_map, map<PASyn::TruthTable, std::vector<string>>& technology_truth_tables, int max_input_size= 4, unsigned int num_max_stored_cuts= 20) {
    int count_id=0;
    queue<string> Q;    // for topological sort
    map<string, int> in_degree;

    for (auto& node: netlist.nodes) {
        in_degree[node->name] = int(node->inputs.size());
        node->min_depth = 0;
        node->best_cut_inputs.clear();
    }

    for (auto& input : netlist.inputs) {           // Initial queue
        if(!node_index[input->name])
            node_index[input->name] = ++count_id;
        netlist.has_node(input)->cuts[1].insert(set<string>{input->name});
        netlist.has_node(input)->min_depth = 0;
        netlist.has_node(input)->area = 0;
        netlist.has_node(input)->area_flow = 0;
        netlist.has_node(input)->fin = 0;
        netlist.has_node(input)->best_cut_inputs = set<string> {input->name};
        netlist.has_node(input)->num_inverters = 0;
        netlist.has_node(input)->best_cut = PASyn::Cut(set<string> {input->name}, input->name, 0, 0, 0, 0, 0, 0, 0);
        auto *truth_table = new PASyn::TruthTable("01");
        cut_to_truth [node_index [input->name]].insert(pair<set<string>, PASyn::TruthTable *>(set<string> {input->name} , truth_table));
        topology_result.push_back(input->name);
        for (const string& nt : netlist.has_node(input)->outputs[0]) {
            in_degree[nt]--;      // in degree
            if (in_degree[nt] == 0)
                Q.push(nt);
        }
    }

    while (!Q.empty()) {
        string now = Q.front();
        if(!node_index[now])//check E[1]
            node_index[now] = ++count_id;
        topology_result.push_back(now);
        Q.pop();
        netlist.has_node(now)->cuts[1].insert(set < string > {now});  // the trivial cut
        auto *truth_table = new PASyn::TruthTable("01");
        cut_to_truth[node_index[now]].insert(pair < set < string > , PASyn::TruthTable * > (set < string > {now}, truth_table));
        assert(netlist.has_node(now)->inputs.size() <= 2);
        if (netlist.has_node(now)->inputs.size() == 2) {        // merge cuts of its two children
            string input1 = netlist.has_node(now)->inputs[0];
            string input2 = netlist.has_node(now)->inputs[1];
            netlist.has_node(input1)->fin++;
            netlist.has_node(input2)->fin++;
            for (int t = 1; t <= max_input_size; t++)
                for (const set <string> &c1: netlist.has_node(input1)->cuts[t]) {
                    for (int k = 1; k <= max_input_size; k++)
                        for (const set <string>& c2: netlist.has_node(input2)->cuts[k]) {
                            set <string> st = c1;
                            st.insert(c2.begin(), c2.end());
                            if (st.size() > (unsigned) max_input_size)
                                continue;
                            auto *_truth_table = new PASyn::TruthTable();
                            _truth_table->num_bits = st.size();
                            _truth_table->generate_input_2(cut_to_truth[node_index[input1]][c1], cut_to_truth[node_index[input2]][c2], c1, c2, st,
                                               netlist.has_node(now)->functions[0].type);
                            auto result = check_equivalence(_truth_table, technology_truth_tables, true);
                            if (!result.first.empty()) {
                                netlist.has_node(now)->cuts[st.size()].insert(st);
                                cut_to_truth[node_index[now]].insert(pair<set<string>, PASyn::TruthTable *>(st, _truth_table));
                                //netlist.add_inverter(result.second, now);
                            }
                            else
                                delete _truth_table;
                        }
                }
        }

        if (netlist.has_node(now)->inputs.size() == 1) {    // inherit cuts from its child
            string input1 = netlist.has_node(now)->inputs[0];
            netlist.has_node(input1)->fin++;
            for (int k = 1; k <= max_input_size; k++)
                for (const set <string> &c1: netlist.has_node(input1)->cuts[k]) {
                    auto *_truth_table = new PASyn::TruthTable();
                    _truth_table->generate_input_1(cut_to_truth[node_index[input1]][c1], netlist.has_node(now)->functions[0].type);
                    if (check_equivalence(_truth_table, technology_truth_tables).empty()) {
                        netlist.has_node(now)->cuts[k].insert(c1);
                        cut_to_truth[node_index[now]].insert(pair<set<string>, PASyn::TruthTable *>(c1, _truth_table));
                    }
                    else delete _truth_table;
                }
        }
        for (const string &nt: netlist.has_node(now)->outputs[0]) {
            in_degree[nt]--;
            if (in_degree[nt] == 0)
                Q.push(nt);
        }

/*Calculate dep, areaflow, exact area*/
        vector <PASyn::Cut> Cuts[10], Ct;
        netlist.has_node(now)->min_depth = INT_MAX;
        netlist.has_node(now)->area = INT_MAX;
        netlist.has_node(now)->area_flow = INT_MAX;
        netlist.has_node(now)->fin = 0;

//printf("now to deal with %s\n", now.c_str());
        for (int k = 1; k <= max_input_size; k++) {
            for (const set <string> &ct: netlist.has_node(now)->cuts[k]) {
                unsigned int dep = 0;
                double area = area_map[select_standard_cell(technology, check_equivalence(cut_to_truth[node_index[now]][ct], technology_truth_tables), "depth")];
                double AF = 0;
                for (const string &nt: ct) {
                    dep = max(dep, netlist.has_node(nt)->min_depth);
                    area += netlist.has_node(nt)->area;
                    AF += netlist.has_node(nt)->area_flow;
//      printf("### %s %s %d %d\n", now.c_str(), nt.c_str(),dep,netlist.has_node(nt)->area);
                }
                dep++;
                AF /= max(1.0, 1.0 * double(netlist.has_node(now)->outputs.size()));
                Cuts[k].emplace_back(ct, now, dep, area, 0, AF, 0, 0, 0);
                Ct.emplace_back(ct, now, dep, area, 0, AF, 0, 0, 0);
            }
        }
        for (int k = 1; k <= max_input_size; k++) {
            sort(Cuts[k].begin(), Cuts[k].end(), cmp_Depth);
            netlist.has_node(now)->cuts[k].clear();
            unsigned int len = Cuts[k].size();
            for (unsigned int i = 0; i < min(num_max_stored_cuts, len); i++) {        // store num_max_stored_cuts priority cuts for each input
                netlist.has_node(now)->cuts[k].insert(Cuts[k][i].input_nodes);
            }
        }
        auto cur_node = netlist.has_node(now);
        cur_node->cuts[1].insert(set < string > {now});
        sort(Ct.begin(), Ct.end(), cmp_Depth);
        //for(auto& cut: Ct)
          //  std::cout<<cut.input_nodes.size()<<" ";
        //std::cout<<std::endl;
        cur_node->min_depth = Ct[0].min_depth;
        cur_node->area_flow = Ct[0].area_flow;
        cur_node->area = Ct[0].area;
        cur_node->best_cut_inputs = Ct[0].input_nodes;
        cur_node->best_cut = Ct[0];
        //cout<<technology_truth_tables.size()<<endl;
        //std::cout<<cur_node->name<<"\n";
        auto result = PASyn::check_equivalence(cut_to_truth[node_index[now]][netlist.has_node(now)->best_cut_inputs], technology_truth_tables, true);
        cur_node->num_inverters = result.second.first + result.second.second;
        cur_node->cell_type = select_standard_cell(technology, result.first, "depth");
        //cout<<technology_truth_tables.size()<<endl<<endl;
    }
}

void PASyn::technology_mapping(PASyn::Netlist& netlist, PASyn::Technology& technology) {
    map<set<string>, PASyn::TruthTable*> cut_to_truth[10005];
    map<PASyn::TruthTable, std::vector<string>> technology_truth_tables;
    vector<string> topology_result;
    map<string, int> counter;   // fanin ref (= fanout)
    map<string, int> node_index;
    map<string, bool> used;
    map<string, double> area_map;
    //int num_max_stored_cuts = 20;   // record the maximum number of stored Cuts
    int max_input_size = 4;
    presetting(technology, technology_truth_tables, area_map);
    node_index.clear();
    int i=0;
    //clock_t IF_END = clock();
    topology_result.clear();        // store the topological order
    counter.clear();

    cut_enumeration_initial(technology, netlist, node_index, cut_to_truth, topology_result, area_map, technology_truth_tables);
    //Enumerate Priority Cuts
    std::string last_target = "depth";
    for (double last_value =1e10;;)
    { // a large number, iterate until convergence
        std::cout<<"iteration "<<i<<" begin\n";
        double gain = Recover(technology, netlist, node_index, counter, cut_to_truth, used, area_map, technology_truth_tables, last_target);
        if (gain == last_value)
            break;
        last_value = gain;
        for (const string& now : topology_result) {
            //cout << now << " " << netlist.has_node(now)->area_flow << " "  << netlist.has_node(now)->area << endl;
            if (netlist.has_node(now)->inputs.empty())
                continue;
            for (int i = 0; i <= max_input_size; i++)
                netlist.has_node(now)->cuts[i].clear();
        }

        cut_enumeration(technology, topology_result, netlist, node_index, counter, cut_to_truth, used, area_map, "power", technology_truth_tables, max_input_size);
        Recover(technology, netlist, node_index, counter, cut_to_truth, used, area_map, technology_truth_tables, "power");
        last_target = "power";

        for (const string& now : topology_result) {
            if (netlist.has_node(now)->inputs.empty())
                continue;
            for (int i = 0; i <= max_input_size; i++)
                netlist.has_node(now)->cuts[i].clear();
        }
        cut_enumeration(technology, topology_result, netlist, node_index, counter, cut_to_truth, used, area_map,
                        "area_flow", technology_truth_tables, max_input_size);
        for (const string& now : topology_result) {
            if (netlist.has_node(now)->inputs.empty())
                continue;
            for (int i = 0; i <= max_input_size; i++)
                netlist.has_node(now)->cuts[i].clear();
        }
        Recover(technology, netlist, node_index, counter, cut_to_truth, used, area_map, technology_truth_tables, "area");

        cut_enumeration(technology, topology_result, netlist, node_index, counter, cut_to_truth, used, area_map,
                        "area", technology_truth_tables, max_input_size);
        for (const string& now : topology_result) {
            if (netlist.has_node(now)->inputs.empty())
                continue;
            for (int i = 0; i <= max_input_size; i++)
                netlist.has_node(now)->cuts[i].clear();
        }
        cut_enumeration(technology, topology_result, netlist, node_index, counter, cut_to_truth, used, area_map,
                        "glitch", technology_truth_tables, max_input_size);
        last_target = "power";
        std::cout<<"iteration "<<i++<<" end\n";
    }
}

void PASyn::technology_mapping_api(const std::string& input, const std::string& technology_input, const std::string& output) {
    Technology technology{};
    Netlist netlist{};
    read_liberty(technology_input, technology);
    PASyn::read_blif(input, netlist);
    technology_mapping(netlist, technology);
    write_verilog(output, netlist, technology, true);
}

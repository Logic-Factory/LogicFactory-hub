//
// Created by zephyr on 2022/2/5.
//
#include "netlist.h"

// Transform an integer to a binary vector representation
// 5 -> 1 0 1
std::vector<int> PASyn::int_to_bvector(int n, unsigned int fix_length) {
    std::vector<int> result;
    while (n != 0) {
        result.emplace_back(n % 2);
        n /= 2;
    }
    unsigned int padding = fix_length - result.size();
    for(int i=0; i<padding; i++)
        result.emplace_back(0);
    std::reverse(result.begin(), result.end());
    return result;
}

int PASyn::bvector_to_int(const std::vector<int>& b_vector) {
    int result = 0;
    for(auto& entry: b_vector) {
        result = result << 1;
        result += entry;
    }
    return result;
}

inline bool is_on_set(const std::vector<std::pair<std::vector<int>, bool>> &function, std::vector<int> vec) {
    if(function[0].second) {
        for (auto entry: function) {
            assert(entry.first.size() == vec.size() && entry.second);
            bool flag = true;
            for (int i = 0; i < vec.size(); i++) {
                if (vec[i] != entry.first[i] && entry.first[i] != -1) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                return true;
        }
        return false;
    }
    else {
        for (auto entry: function) {
            assert(entry.first.size() == vec.size() && !entry.second);
            bool flag = true;
            for (int i = 0; i < vec.size(); i++) {
                if (vec[i] != entry.first[i] && entry.first[i] != -1) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                return false;
        }
        return true;
    }
}

inline void deal_with_glitch_prop(PASyn::Cell *cell, PASyn::Function &function, std::vector<int> &initial_vector,
                                  std::vector<int> &after_vector,
                                  std::vector<std::map<std::vector<int>, int>> &glitch_1x_propagate,
                                  std::vector<std::map<std::vector<int>, int>> &glitch_0x_propagate, bool x) {
    for (int input_index = 0; input_index < cell->inputs.size(); input_index++) {
        std::vector<int> inter_vector = initial_vector;
        if (inter_vector[input_index] == 0) {
            inter_vector[input_index] = 1;
            if (is_on_set(function.function, inter_vector) == x) {
                std::vector<int> polynomial(cell->inputs.size() * 2, 0);
                for (int k = 0; k < initial_vector.size(); k++)
                    polynomial[initial_vector[k] == 1 ? 2 * k : 2 * k + 1]++;
                for (int k = 0; k < after_vector.size(); k++)
                    polynomial[after_vector[k] == 1 ? 2 * k : 2 * k + 1]++;
                glitch_1x_propagate[input_index][polynomial] += 1;
            }
        } else {
            inter_vector[input_index] = 0;
            if (is_on_set(function.function, inter_vector) == x) {
                std::vector<int> polynomial(cell->inputs.size() * 2, 0);
                for (int k = 0; k < initial_vector.size(); k++)
                    polynomial[initial_vector[k] == 1 ? 2 * k : 2 * k + 1]++;
                for (int k = 0; k < after_vector.size(); k++)
                    polynomial[after_vector[k] == 1 ? 2 * k : 2 * k + 1]++;
                glitch_0x_propagate[input_index][polynomial] += 1;
            }
        }
    }
}

// Glitch and switch preprocess for technology cell, in order to fast propagate
// Not for glitch generation
void PASyn::switch_pre_process(PASyn::Technology &technology) {
    for (auto &cell: technology.cells) {
        for (auto &function: cell.second->functions) {
            std::vector<std::map<std::vector<int>, int>> glitch_11_propagate, glitch_10_propagate, glitch_01_propagate, glitch_00_propagate;
            glitch_00_propagate.reserve(cell.second->inputs.size());
            glitch_00_propagate.resize(cell.second->inputs.size());
            glitch_01_propagate.reserve(cell.second->inputs.size());
            glitch_01_propagate.resize(cell.second->inputs.size());
            glitch_10_propagate.reserve(cell.second->inputs.size());
            glitch_10_propagate.resize(cell.second->inputs.size());
            glitch_11_propagate.reserve(cell.second->inputs.size());
            glitch_11_propagate.resize(cell.second->inputs.size());

            int input_permutation = 1 << int(cell.second->inputs.size());

            for (int i = 0; i < input_permutation; i++) {
                for (int j = 0; j < input_permutation; j++) {
                    std::vector<int> initial_vector = PASyn::int_to_bvector(i, cell.second->inputs.size());
                    std::vector<int> after_vector = PASyn::int_to_bvector(j, cell.second->inputs.size());
                    bool initial_on = is_on_set(function.function, initial_vector);
                    if (initial_on) {
                        deal_with_glitch_prop(cell.second, function, initial_vector, after_vector, glitch_10_propagate,
                                              glitch_00_propagate, false);
                    } else {
                        deal_with_glitch_prop(cell.second, function, initial_vector, after_vector, glitch_11_propagate,
                                              glitch_01_propagate, true);
                    }
                }
            }
            cell.second->glitch_10_propagate.emplace_back(glitch_10_propagate);
            cell.second->glitch_11_propagate.emplace_back(glitch_11_propagate);
            cell.second->glitch_00_propagate.emplace_back(glitch_00_propagate);
            cell.second->glitch_01_propagate.emplace_back(glitch_01_propagate);
        }
    }
}

// Calculate depth and network load capacitance
void pre_process(PASyn::Netlist &netlist, PASyn::Technology &technology) {
    std::queue<PASyn::Node *> queue; //used for broad first traverse
    for (auto &node: netlist.inputs) {
        queue.emplace(node);
    }
    std::map<std::string, int> topology_count;

    for (auto &node: netlist.nodes) {
        topology_count[node->name] = int(node->inputs.size());
    }
    while (!queue.empty()) {
        PASyn::Node *node = queue.front();
        // assert 判断有误，需要修正
        assert(node->cell_type != "un_mapped" || node->inputs.empty());
        queue.pop();
        double load_capacitance = 0;
        for (auto &output_name: node->outputs[0]) {
            // NOTE:For AIG only
            PASyn::Node *output = netlist.has_node(output_name);
            output->max_depth = output->max_depth <= node->max_depth ? node->max_depth + 1 : output->max_depth;
            topology_count[output->name]--;
            int index = int(std::distance(output->inputs.begin(),
                                          std::find(output->inputs.begin(), output->inputs.end(), node->name)));
            load_capacitance += technology.cells[output->cell_type]->inputs[index].capacitance;
            if (topology_count[output->name] == 0)
                queue.emplace(output);
        }
        node->load_capacitance = load_capacitance;
    }
}

inline void calculate_switch_prob(double &rise_from_1, double &rise_from_0, double &fall_from_1, double &fall_from_0,
                                  PASyn::Cell *cell, int pin_index) {
    int input_permutation = 1 << int(cell->inputs.size());
    auto function = cell->functions[0].function;

    for (int i = 0; i < input_permutation; i++) {
        for (int j = 0; j < input_permutation; j++) {
            std::vector<int> initial_vector = PASyn::int_to_bvector(i, cell->inputs.size());
            std::vector<int> after_vector = PASyn::int_to_bvector(j, cell->inputs.size());
            initial_vector[pin_index] = false;
            after_vector[pin_index] = true;
            bool initial_on = is_on_set(function, initial_vector);
            bool after_on = is_on_set(function, after_vector);
            rise_from_1 += int(after_on && !initial_on);
            fall_from_1 += int(!after_on && initial_on);
            initial_vector[pin_index] = true;
            after_vector[pin_index] = false;
            initial_on = is_on_set(function, initial_vector);
            after_on = is_on_set(function, after_vector);
            rise_from_0 += int(after_on && !initial_on);
            fall_from_0 += int(!after_on && initial_on);
        }
    }

    rise_from_0 /= input_permutation * input_permutation;
    rise_from_1 /= input_permutation * input_permutation;
    fall_from_0 /= input_permutation * input_permutation;
    fall_from_1 /= input_permutation * input_permutation;
}

void propagate_glitch(PASyn::Cell *cell, PASyn::Netlist &netlist, PASyn::Node *node) {
    for (int output_index = 0; output_index < node->outputs.size(); output_index++) {
        for (int i = 0; i < node->inputs.size(); i++) {
            auto input = netlist.has_node(node->inputs[i]);
            for (auto &entry: cell->glitch_11_propagate[output_index][i]) {
                double temp_result = input->glitch_1;
                for (int j = 0; j < entry.first.size(); j++) {
                    temp_result *= j % 2 == 0 ? netlist.has_node(node->inputs[j/2])->probability_1[0] :
                                   (1 - netlist.has_node(node->inputs[j/2])->probability_1[0]);
                }
                node->glitch_1 += temp_result;
            }

            for (auto &entry: cell->glitch_01_propagate[output_index][i]) {
                double temp_result = input->glitch_0;
                for (int j = 0; j < entry.first.size(); j++) {
                    temp_result *= j % 2 == 0 ? netlist.has_node(node->inputs[j/2])->probability_1[0] :
                                   (1 - netlist.has_node(node->inputs[j/2])->probability_1[0]);
                }
                node->glitch_1 += temp_result;
            }

            for (auto &entry: cell->glitch_10_propagate[output_index][i]) {
                double temp_result = input->glitch_1;
                for (int j = 0; j < entry.first.size(); j++) {
                    temp_result *= j % 2 == 0 ? netlist.has_node(node->inputs[j/2])->probability_1[0] :
                                   (1 - netlist.has_node(node->inputs[j/2])->probability_1[0]);
                }
                node->glitch_0 += temp_result;
            }

            for (auto &entry: cell->glitch_00_propagate[output_index][i]) {
                double temp_result = input->glitch_0;
                for (int j = 0; j < entry.first.size(); j++) {
                    temp_result *= j % 2 == 0 ? netlist.has_node(node->inputs[j/2])->probability_1[0] :
                                   (1 - netlist.has_node(node->inputs[j/2])->probability_1[0]);
                }
                node->glitch_0 += temp_result;
            }
        }
    }
}

// Will calculate the timing of each node and propagate glitch
void PASyn::calculate_timing(Netlist &netlist, Technology &technology) {
    std::queue<PASyn::Node *> queue; //used for broad first traverse
    for (auto & input : netlist.inputs) {
        queue.push(input);
    }
    std::map<std::string, int> topology_count;

    for (auto &node: netlist.nodes) {
        topology_count[node->name] = int(node->inputs.size());
    }
    while (!queue.empty()) {
        PASyn::Node *node = queue.front();
        assert(node->cell_type != "un_mapped" || node->inputs.empty());
        queue.pop();

        for (auto &output_name: node->outputs[0]) {
            PASyn::Node *output = netlist.has_node(output_name);
            topology_count[output->name]--;
            if (topology_count[output->name] == 0)
                queue.emplace(output);
        }

        if (node->inputs.empty())
            continue;

        // <arrival_time, <input_index, <rise_from_0, rise_from_1>, <fall_from_0, fall_from_1>>>
        std::map<double, std::pair<int, std::pair<std::pair<double, double>, std::pair<double, double>>>> arrival_time_dic;
        auto lut = technology.cells[node->cell_type]->outputs[0].timing.begin();
        double rise_delay = 0, fall_delay = 0, rise_transition = 0, fall_transition = 0;
        double fall_prob = 0, rise_prob = 0;
        double output_time = 0;
        for (int i = 0; i < node->inputs.size(); i++, lut++) {
            auto input = netlist.has_node(node->inputs[i]);
            // probability of this standard cell to rise when this input rise to 1; ...
            double rise_from_1 = 0, rise_from_0 = 0, fall_from_1 = 0, fall_from_0 = 0;
            calculate_switch_prob(rise_from_1, rise_from_0, fall_from_1, fall_from_0, technology.cells[node->cell_type],
                                  i);
            fall_prob += fall_from_0 + fall_from_1;
            rise_prob += rise_from_0 + rise_from_1;
            rise_delay += interpolate(lut->second.look_up_tables["cell_rise"].index_1,
                                      lut->second.look_up_tables["cell_rise"].index_2,
                                      lut->second.look_up_tables["cell_rise"].values, node->load_capacitance,
                                      input->rise_transition) * rise_from_1;
            rise_delay += interpolate(lut->second.look_up_tables["cell_rise"].index_1,
                                      lut->second.look_up_tables["cell_rise"].index_2,
                                      lut->second.look_up_tables["cell_rise"].values, node->load_capacitance,
                                      input->fall_transition) * rise_from_0;
            fall_delay += interpolate(lut->second.look_up_tables["cell_fall"].index_1,
                                      lut->second.look_up_tables["cell_fall"].index_2,
                                      lut->second.look_up_tables["cell_fall"].values, node->load_capacitance,
                                      input->rise_transition) * fall_from_1;
            fall_delay += interpolate(lut->second.look_up_tables["cell_fall"].index_1,
                                      lut->second.look_up_tables["cell_fall"].index_2,
                                      lut->second.look_up_tables["cell_fall"].values, node->load_capacitance,
                                      input->fall_transition) * fall_from_0;

            rise_transition += interpolate(lut->second.look_up_tables["rise_transition"].index_1,
                                           lut->second.look_up_tables["rise_transition"].index_2,
                                           lut->second.look_up_tables["rise_transition"].values, node->load_capacitance,
                                           input->rise_transition) * rise_from_1;
            rise_transition += interpolate(lut->second.look_up_tables["rise_transition"].index_1,
                                           lut->second.look_up_tables["rise_transition"].index_2,
                                           lut->second.look_up_tables["rise_transition"].values, node->load_capacitance,
                                           input->fall_transition) * rise_from_0;
            fall_transition += interpolate(lut->second.look_up_tables["fall_transition"].index_1,
                                           lut->second.look_up_tables["fall_transition"].index_2,
                                           lut->second.look_up_tables["fall_transition"].values, node->load_capacitance,
                                           input->rise_transition) * fall_from_1;
            fall_transition += interpolate(lut->second.look_up_tables["fall_transition"].index_1,
                                           lut->second.look_up_tables["fall_transition"].index_2,
                                           lut->second.look_up_tables["fall_transition"].values, node->load_capacitance,
                                           input->fall_transition) * fall_from_0;

            assert(rise_prob != 0 && fall_prob != 0);
            rise_delay /= rise_prob;
            fall_delay /= fall_prob;
            rise_transition /= rise_prob;
            fall_transition /= fall_prob;

            double expected_delay = (rise_delay * rise_prob + fall_delay * fall_prob) / (rise_prob + fall_prob);
            output_time = output_time > input->output_time + expected_delay ? output_time : input->output_time +
                                                                                            expected_delay;
            arrival_time_dic[input->output_time] = std::make_pair(i, std::make_pair(std::make_pair(rise_from_0, rise_from_1), std::make_pair(fall_from_0, fall_from_1)));
        }

        // Glitch generation
        /*
        if (i != node->inputs.size() &&
            (input->output_time - netlist.has_node(node->inputs[i - 1])->output_time) > 1e-4) {
            node->glitch_1 +=
                    (fall_from_1 + fall_from_0) * (1 - node->probability_1[0]) * (1 - input->probability_1[0]) *
                    input->probability_1[0];
            node->glitch_0 += (rise_from_0 + rise_from_1) * node->probability_1[0] * (1 - input->probability_1[0]) *
                              input->probability_1[0];
        }
         */
        for(auto _entry=arrival_time_dic.begin(); _entry != arrival_time_dic.end(); _entry++) {
            auto entry = _entry;
            if (entry != arrival_time_dic.begin() && (entry->first - (entry--)->first) > 1e-4) {
                // <arrival_time, <input_index, <rise_from_0, rise_from_1>, <fall_from_0, fall_from_1>>>
                node->glitch_1 += (entry->second.second.first.first * (1 - netlist.has_node(node->inputs[entry->second.first])->probability_1[0])
                        + entry->second.second.first.second * netlist.has_node(node->inputs[entry->second.first])->probability_1[0]) *
                        (1 - node->probability_1[0]);
                node->glitch_0 += (entry->second.second.second.first * (1 - netlist.has_node(node->inputs[entry->second.first])->probability_1[0])
                        + entry->second.second.second.second * netlist.has_node(node->inputs[entry->second.first])->probability_1[0]) *
                                node->probability_1[0];
            }
        }

        node->output_time = output_time;
        propagate_glitch(technology.cells[node->cell_type], netlist, node);
    }

    for(auto& node: netlist.outputs) {
        netlist.delay = node->output_time > netlist.delay ? node->output_time : netlist.delay;
    }
}

void PASyn::calculate_probability_1(Netlist &netlist) {
    std::map<Node *, unsigned int> in_degree;
    std::queue<Node *> topology;
    for (auto &node: netlist.inputs)
        topology.push(node);
    for (auto &node: netlist.nodes)
        in_degree[node] = node->inputs.size();
    while (!topology.empty()) {
        Node *now = topology.front();
        topology.pop();
        double result = 0;
        std::vector<double> input_probability_1;

        for (auto &_input: now->inputs) {
            auto input = netlist.has_node(_input);
            assert(input->probability_1[0] != -1);
            input_probability_1.emplace_back(input->probability_1[0]);
        }

        for (int i = 0; i < now->functions.size(); i++) {
            if (now->functions[i].function.empty())
                continue;
            /*
            for (auto &entry: now->functions[i].function) {
                double _result = 1;
                for (int j = 0; j < entry.first.size(); j++) {
                    switch (entry.first[j]) {
                        case 0:
                            _result *= (1 - input_probability_1[j]);
                            break;
                        case 1:
                            _result *= input_probability_1[j];
                            break;
                        case -1:
                            _result *= 1;
                            break;
                        default:
                            assert(false);
                    }
                }
                result += _result;
            }
             */
            int input_permutation = 1 << int(now->functions[i].function.front().first.size());
            for(int j=0; j<input_permutation; j++) {
                std::vector<int> input_vector = PASyn::int_to_bvector(j, now->functions[i].function.front().first.size());
                if(is_on_set(now->functions[i].function, input_vector)) {
                    double _result = 1;
                    for(int k=0; k<input_vector.size(); k++)
                        _result *= input_vector[k] == 0 ? (1-input_probability_1[k]) : input_probability_1[k];
                    result += _result;
                }
            }
            now->probability_1[i] = now->functions[i].function.front().second ? result : 1 - result;
        }
        for (auto &_output: now->outputs[0]) {
            auto output = netlist.has_node(_output);
            if (--in_degree[output] == 0) {
                topology.push(output);
            }
        }
    }
}

double calculate_static_power(PASyn::Netlist &netlist, PASyn::Technology &technology) {
    double static_power = 0;
    for (auto &node: netlist.nodes) {
        if (node->cell_type == "not_mapped" && !node->inputs.empty())
            assert(false);
        if (node->inputs.empty())
            continue;
        static_power += technology.cells[node->cell_type]->leakage;
    }
    return static_power;
}

double calculate_internal_power(PASyn::Netlist &netlist, PASyn::Technology &technology) {
    double internal_power = 0;
    for (auto &node: netlist.nodes) {
        if (node->cell_type == "not_mapped" && !node->inputs.empty())
            assert(false);
        if (node->inputs.empty())
            continue;
        PASyn::Cell *cell = technology.cells[node->cell_type];
        double num_switch =
                2 * (1 - node->probability_1[0]) * node->probability_1[0] + 2 * node->glitch_0 + 2 * node->glitch_1;
        double toggle_rate = num_switch / netlist.delay;
        for (auto &output: cell->outputs) {
            auto lut = output.internal_power.begin();
            for (int i = 0; i < node->inputs.size(); i++, lut++) {
                PASyn::Node *input = netlist.has_node(node->inputs[i]);
                // input transition for input node is 0
                double fall_power = PASyn::interpolate(lut->second.look_up_tables["fall_power"].index_1,
                                                       lut->second.look_up_tables["fall_power"].index_2,
                                                       lut->second.look_up_tables["fall_power"].values,
                                                       node->load_capacitance, input->fall_transition);
                double rise_power = PASyn::interpolate(lut->second.look_up_tables["rise_power"].index_1,
                                                       lut->second.look_up_tables["rise_power"].index_2,
                                                       lut->second.look_up_tables["rise_power"].values,
                                                       node->load_capacitance, input->rise_transition);
                internal_power += (fall_power + rise_power) * toggle_rate;
            }
        }
    }
    return internal_power;
}

double calculate_dynamic_power(PASyn::Netlist &netlist, PASyn::Technology &technology) {
    double dynamic_power = 0;

    for (auto &node: netlist.nodes) {
        if (node->inputs.empty())
            continue;
        double num_switch =
                2 * (1 - node->probability_1[0]) * node->probability_1[0] + 2 * node->glitch_0 + 2 * node->glitch_1;
        double toggle_rate = num_switch / netlist.delay;
        dynamic_power += 0.5 * toggle_rate * pow(technology.working_voltage, 2) * node->load_capacitance;
    }
    return dynamic_power;
}

double calculate_wire_power(PASyn::Netlist &netlist, PASyn::Technology &technology) {
    double wire_power = 0;

    for (auto &node: netlist.nodes) {
        if (node->inputs.empty())
            continue;
        double num_switch =
                2 * (1 - node->probability_1[0]) * node->probability_1[0] + 2 * node->glitch_0 + 2 * node->glitch_1;
        double toggle_rate = num_switch / netlist.delay;
        wire_power += 0.5 * toggle_rate * pow(technology.working_voltage, 2) * PASyn::wire_length(netlist, node);
    }
    return wire_power;
}

//std::pair<double, double> PASyn::calculate_power(Netlist &netlist, Technology &technology) {
std::vector<double> PASyn::calculate_power(Netlist &netlist, Technology &technology) {
    std::vector<double> result;
    pre_process(netlist, technology);
    /*for(auto node: netlist.nodes)
        std::cout<<node->load_capacitance<<" "<<node->max_depth<<"\n";
        */
    calculate_probability_1(netlist);
    /*
     * for(auto node: netlist.nodes)
        std::cout<<node->probability_1[0]<<"\n";
        */
    calculate_timing(netlist, technology);
    /*for(auto node: netlist.nodes)
        std::cout<<node->output_time<<"\n";
        */
    double static_power = calculate_static_power(netlist, technology) * 1e-6;
    /*for(auto node: netlist.nodes)
        std::cout<<static_power<<"\n";
        */
    result.emplace_back(static_power);
    double dynamic_power = (calculate_dynamic_power(netlist, technology));
    result.emplace_back(dynamic_power);
    double internal_power = (calculate_internal_power(netlist, technology));
    result.emplace_back(internal_power);
    double wire_power = (calculate_wire_power(netlist, technology));
    result.emplace_back(wire_power);
    double total_power = static_power + dynamic_power + internal_power + wire_power;
    result.emplace_back(total_power);

    // internal: intercept 66.5044902081977     slope 201.35061141
    // switch  : intercept 61.39212329037025    slope 13.99372074
    // wire    : intercept -44.07551507267508   slope: 8.69726908
    return result;
}

std::vector<double> PASyn::calculate_power_api(std::string &input, std::string &technology_input, bool gym_using) {
    Technology technology{};
    Netlist netlist{};
    read_liberty(technology_input, technology);
    switch_pre_process(technology);
    PASyn::read_blif(input, netlist, &technology);
    return calculate_power(netlist, technology);
}

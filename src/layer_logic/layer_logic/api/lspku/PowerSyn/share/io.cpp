//
// Created by zephyr on 2022/10/27.
//
#include "netlist.h"

std::vector<std::string> PASyn::split(const std::string &str, char terminal) {
    std::vector<std::string> split_str;
    std::string::size_type end_pos, start_pos;
    start_pos = str.find(terminal);
    end_pos = 0;
    while (std::string::npos != start_pos) {
        split_str.push_back(str.substr(end_pos, start_pos - end_pos));

        end_pos = start_pos + 1;
        while (str[end_pos] == terminal)
            end_pos++;
        start_pos = str.find(terminal, end_pos);
    }
    if (end_pos != str.length())
        split_str.push_back(str.substr(end_pos));

    return split_str;
}


std::string PASyn::filter_string(const std::string &str, std::vector<char> dic) {
    std::string new_str;
    for (auto &ch: str) {
        if (std::find(dic.begin(), dic.end(), ch) != dic.end())
            continue;
        else
            new_str += ch;
    }
    return new_str;
}

void PASyn::read_blif(const std::string &file, Netlist &netlist, Technology *technology) {
    // If clear flag is set, redundant edges will be removed automatically
    std::ifstream fin(file, std::ios::in);
    assert(fin.is_open());

    // Clear existing netlist
    if (!netlist.nodes.empty()) {
        netlist = Netlist();
    }

    char temp_char;
    std::string temp_str;
    while (std::getline(fin, temp_str)) {
        if (temp_str[0] == '#' || temp_str.empty())
            continue;
        while (temp_str[temp_str.length() - 1] == '\\') {
            temp_str = temp_str.substr(0, temp_str.length() - 1);
            std::string _temp_str;
            std::getline(fin, _temp_str);
            temp_str += _temp_str;
        }
        std::vector<std::string> str = PASyn::split(temp_str);
        if (str[0] == ".model")
            netlist.name = str[1];
        else if (str[0] == ".end")
            continue;
        else if (str[0] == ".inputs") {
            for (auto it = str.begin() + 1; it != str.end(); it++) {
                Node *node = new Node(*it);
                node->probability_1.emplace_back(0.5);
                node->outputs.emplace_back(std::vector<std::string>());
                node->num_fanout.emplace_back(0);
                node->min_depth = 1;
                node->max_depth = 1;
                node->functions = std::vector<Function>(1, Function());
                netlist.add_node(node);
                netlist.inputs.emplace_back(node);
            }
        } else if (str[0] == ".outputs") {
            for (auto it = str.begin() + 1; it != str.end(); it++) {
                Node *node = new Node(*it);
                node->probability_1.emplace_back(-1);
                node->outputs.emplace_back(std::vector<std::string>());
                node->num_fanout.emplace_back(0);
                netlist.add_node(node);
                netlist.outputs.emplace_back(node);
            }
        } else if (str[0] == ".names") {
            std::string function;
            while (true) {
                fin >> temp_char;
                fin.putback(temp_char);
                if (temp_char == '.')
                    break;
                else {
                    std::string _temp_str;
                    std::getline(fin, _temp_str);
                    if (!function.empty())
                        function += "\n";
                    function += _temp_str;
                }
            }

            int num_inputs = int(str.size()) - 2;
            for (auto it = str.begin() + 1; it != str.end() - 1; it++) {
                auto input = netlist.has_node(*it);
                if (input != nullptr) {
                    (input->num_fanout[0])++;
                    input->outputs[0].emplace_back(*(PASyn::split(*(str.end() - 1), '=').end() - 1));
                } else {
                    Node *node = new Node(*it);
                    node->probability_1.emplace_back(-1);
                    node->outputs.emplace_back(std::vector<std::string>(1, *(PASyn::split(*(str.end() - 1), '=').end() - 1)));
                    node->num_fanout.emplace_back(1);
                    netlist.add_node(node);
                }
            }

            auto node = netlist.has_node(*(str.end() - 1));
            if (node != nullptr) {
                node->num_fanin = num_inputs;
                node->inputs = std::vector<std::string>(str.begin() + 1, str.end() - 1);
                node->functions = std::vector<Function>(1, Function(num_inputs, function));
                node->probability_1 = std::vector<double>(1, -1);
            } else {
                node = new Node(*(str.end() - 1), num_inputs, std::vector<unsigned int>(1, 0),
                                std::vector<std::string>(str.begin() + 1, str.end() - 1),
                                std::vector<Function>(1, Function(num_inputs, function)),
                                std::vector<double>(1, -1));
                netlist.add_node(node);
            }
            for (auto it = str.begin() + 1; it != str.end() - 1; it++)
                netlist.edges.emplace_back(new Edge(netlist.has_node(*it), node));
        } else if (str[0] == ".gate" || str[0] == ".subckt") {
            Cell &cell = *technology->cells[str[1]];
            std::map<std::string, std::string> inputs_map;
            for (int i = 2; i <= cell.inputs.size() + 1; i++) {
                std::vector<std::string> _temp_str = PASyn::split(str[i], '=');
                inputs_map[*(_temp_str.begin())] = *(_temp_str.end() - 1);
                auto input = netlist.has_node(*(_temp_str.end() - 1));
                if (input != nullptr) {
                    (input->num_fanout[0])++;
                    input->outputs[0].emplace_back(*(PASyn::split(*(str.end() - 1), '=').end() - 1));
                } else {
                    Node *node = new Node(*(_temp_str.end() - 1));
                    node->probability_1.emplace_back(-1);
                    node->outputs.emplace_back(std::vector<std::string>(1, *(PASyn::split(*(str.end() - 1), '=').end() - 1)));
                    node->num_fanout.emplace_back(1);
                    netlist.add_node(node);
                }
            }
            std::vector<std::string> inputs;
            inputs.reserve(inputs_map.size());
            for (auto &pair: inputs_map)
                inputs.emplace_back(pair.second);
            // TODO: dual-output support not finished
            Node *node = netlist.has_node(*(str.end() - 1));
            if (node != nullptr) {
                node->num_fanin = int(cell.inputs.size());
                node->inputs = inputs;
                node->functions = cell.functions;
                node->probability_1 = std::vector<double>(1, -1);
                node->cell_type = cell.name;
            } else {
                node = new Node(*(PASyn::split(*(str.end() - 1), '=').end() - 1), int(cell.inputs.size()),
                                std::vector<unsigned int>(1, 0), inputs,
                                cell.functions, std::vector<double>(1, -1), cell.name);
                netlist.add_node(node);
            }
            for (auto &input: inputs) {
                netlist.edges.emplace_back(new Edge(netlist.has_node(input), node));
            }
        } else {
            std::cout << "Not implemented error";
            assert(false);
        }
    }
}

void PASyn::write_blif(const std::string &file, Netlist &netlist) {
    std::ofstream fout(file);
    assert(fout.is_open());
    fout << "# Generated by Power-Aware-LogicSynthesis Project zephyr." << std::endl;
    fout << ".model " << netlist.name << std::endl;
    fout << ".inputs";
    for (auto &input: netlist.inputs) {
        fout << " " << input->name;
    }
    fout << std::endl;
    fout << ".outputs";
    for (auto &output: netlist.outputs) {
        fout << " " << output->name;
    }
    fout << std::endl;
    for (auto &node: netlist.nodes) {
        if (node->functions.empty())
            continue;
        fout << ".names";
        for (auto &input: node->inputs)
            fout << " " << input;
        fout << " " << node->name << std::endl;
        // NOTE: do not support dual output.
        assert(node->functions.size() <= 1);

        for (auto &function: node->functions[0].function) {
            for (auto &input: function.first)
                fout << input;
            fout << (function.first.empty() ? "" : " ") << (function.second ? 1 : 0) << std::endl;
        }
    }
    fout.close();
}

void input_look_up_table(std::ifstream &fin, PASyn::LookUpTable &look_up_table, int num_index_1, int num_index_2) {
    std::string temp_str;
    while (fin >> temp_str) {
        if (temp_str == "index_1") {
            std::getline(fin, temp_str);
            temp_str = temp_str.substr();
            while (*(temp_str.end() - 1) != ';') {
                std::string _temp_string;
                std::getline(fin, _temp_string);
                temp_str += _temp_string;
            }
            temp_str = PASyn::filter_string(temp_str, std::vector<char>{'\\', ',', '(', '"', ')', ';'});
            std::stringstream sin(temp_str);
            for (int i = 0; i < num_index_1; i++) {
                double temp_double;
                sin >> temp_double;
                look_up_table.index_1.emplace_back(temp_double);
            }
        } else if (temp_str == "index_2") {
            std::getline(fin, temp_str);
            temp_str = temp_str.substr();
            while (*(temp_str.end() - 1) != ';') {
                std::string _temp_string;
                std::getline(fin, _temp_string);
                temp_str += _temp_string;
            }
            temp_str = PASyn::filter_string(temp_str, std::vector<char>{'\\', ',', '(', '"', ')', ';'});
            std::stringstream sin(temp_str);
            for (int i = 0; i < num_index_2; i++) {
                double temp_double;
                sin >> temp_double;
                look_up_table.index_2.emplace_back(temp_double);
            }
        } else if (temp_str == "values") {
            std::getline(fin, temp_str);
            temp_str = temp_str.substr();
            while (*(temp_str.end() - 1) != ';') {
                std::string _temp_string;
                std::getline(fin, _temp_string);
                temp_str += _temp_string;
            }
            temp_str = PASyn::filter_string(temp_str, std::vector<char>{'\\', ',', '(', '"', ')', ';'});
            std::stringstream sin(temp_str);
            for (int i = 0; i < num_index_1; i++) {
                std::vector<double> value_index_i;
                for (int j = 0; j < num_index_2; j++) {
                    double temp_double;
                    sin >> temp_double;
                    value_index_i.emplace_back(temp_double);
                }
                look_up_table.values.emplace_back(value_index_i);
            }
        } else if (temp_str == "}")
            break;
    }
}

void input_timing(std::ifstream &fin, PASyn::Cell_Output &output) {
    PASyn::Timing_or_Power timing{};
    std::string temp_str;
    fin >> temp_str; //for '{'
    std::string related_pin;
    std::string timing_sense;
    while (fin >> temp_str) {
        if (temp_str == "related_pin") {
            fin >> temp_str >> temp_str;
            related_pin = temp_str.substr(1, temp_str.length() - 3);
        } else if (temp_str == "timing_sense") {
            fin >> temp_str >> temp_str;
            timing_sense = temp_str.substr(0, temp_str.length() - 1);
        } else if (temp_str == "}")
            break;
        else if (temp_str.find("cell_rise") != -1) {
            std::vector<std::string> strings = PASyn::split(*(PASyn::split(temp_str, '_').end() - 1), 'x');
            int index_1 = stoi(strings[0]), index_2 = stoi(strings[1]);
            fin >> temp_str; // for "{"
            PASyn::LookUpTable look_up_table{};
            input_look_up_table(fin, look_up_table, index_1, index_2);
            timing.look_up_tables["cell_rise"] = look_up_table;
        } else if (temp_str.find("rise_transition") != -1) {
            std::vector<std::string> strings = PASyn::split(*(PASyn::split(temp_str, '_').end() - 1), 'x');
            int index_1 = stoi(strings[0]), index_2 = stoi(strings[1]);
            fin >> temp_str; // for "{"
            PASyn::LookUpTable look_up_table{};
            input_look_up_table(fin, look_up_table, index_1, index_2);
            timing.look_up_tables["rise_transition"] = look_up_table;
        } else if (temp_str.find("cell_fall") != -1) {
            std::vector<std::string> strings = PASyn::split(*(PASyn::split(temp_str, '_').end() - 1), 'x');
            int index_1 = stoi(strings[0]), index_2 = stoi(strings[1]);
            fin >> temp_str; // for "{"
            PASyn::LookUpTable look_up_table{};
            input_look_up_table(fin, look_up_table, index_1, index_2);
            timing.look_up_tables["cell_fall"] = look_up_table;
        } else if (temp_str.find("fall_transition") != -1) {
            std::vector<std::string> strings = PASyn::split(*(PASyn::split(temp_str, '_').end() - 1), 'x');
            int index_1 = stoi(strings[0]), index_2 = stoi(strings[1]);
            fin >> temp_str; // for "{"
            PASyn::LookUpTable look_up_table{};
            input_look_up_table(fin, look_up_table, index_1, index_2);
            timing.look_up_tables["fall_transition"] = look_up_table;
        }
    }
    output.timing[related_pin] = timing;
}

void input_internal_power(std::ifstream &fin, PASyn::Cell_Output &output) {
    PASyn::Timing_or_Power internal_power{};
    std::string temp_str;
    fin >> temp_str; //for '{'
    std::string related_pin;
    std::string timing_sense;
    while (fin >> temp_str) {
        if (temp_str == "related_pin") {
            fin >> temp_str >> temp_str;
            related_pin = temp_str.substr(1, temp_str.length() - 3);
        } else if (temp_str == "}")
            break;
        else if (temp_str.find("rise_power") != -1) {
            std::vector<std::string> strings = PASyn::split(*(PASyn::split(temp_str, '_').end() - 1), 'x');
            int index_1 = stoi(strings[0]), index_2 = stoi(strings[1]);
            fin >> temp_str; // for "{"
            PASyn::LookUpTable look_up_table{};
            input_look_up_table(fin, look_up_table, index_1, index_2);
            internal_power.look_up_tables["rise_power"] = look_up_table;
        } else if (temp_str.find("fall_power") != -1) {
            std::vector<std::string> strings = PASyn::split(*(PASyn::split(temp_str, '_').end() - 1), 'x');
            int index_1 = stoi(strings[0]), index_2 = stoi(strings[1]);
            fin >> temp_str; // for "{"
            PASyn::LookUpTable look_up_table{};
            input_look_up_table(fin, look_up_table, index_1, index_2);
            internal_power.look_up_tables["fall_power"] = look_up_table;
        }
    }
    output.internal_power[related_pin] = internal_power;
}

void PASyn::read_liberty(const std::string &file, Technology &technology) {
    std::ifstream fin(file, std::ios::in);
    assert(fin.is_open());
    std::string temp_str;
    while (fin >> temp_str) {
        if (temp_str == "nom_voltage") {
            double working_voltage;
            fin>>temp_str>>temp_str;
            std::stringstream sin(temp_str.substr(0, temp_str.length() - 1));
            sin>>working_voltage;
            technology.working_voltage = working_voltage;
        }
        if (temp_str == "cell") {
            int num_output = 0;
            std::string name;
            double area;
            double leakage;
            std::vector<Cell_Input> inputs;
            std::vector<Cell_Output> outputs;
            std::vector<std::string> function_str;
            bool is_sequential = false, is_triple = false;

            fin >> name;
            name = name.substr(1, name.length() - 2);
            int count = 0;
            while (fin >> temp_str) {
                if (temp_str == "}") {
                    count--;
                    if (count == 0)
                        break;
                } else if (temp_str == "{") {
                    count++;
                } else if (temp_str == "area") {
                    fin >> temp_str; //for ":"
                    fin >> temp_str;
                    temp_str = temp_str.substr(0, temp_str.length() - 1);
                    std::istringstream sin(temp_str);
                    sin >> area;
                } else if (temp_str == "cell_leakage_power") {
                    fin >> temp_str; //for ":"
                    fin >> temp_str;
                    temp_str = temp_str.substr(0, temp_str.length() - 1);
                    std::istringstream sin(temp_str);
                    sin >> leakage;
                } else if (temp_str == "ff" || temp_str == "latch") {
                    is_sequential = true;
                } else if (std::regex_match(temp_str, std::regex("pin\\([a-z, A-Z, 0-9]+\\)"))) {
                    std::string pin_name = temp_str.substr(4, temp_str.length() - 5);
                    if (pin_name == "EN") {
                        is_triple = true;
                        continue;
                    }
                    while (fin >> temp_str) {
                        if (temp_str == "direction") {
                            fin >> temp_str >> temp_str; //for ":"
                            if (temp_str == "input;") {
                                std::string _capacitance, _rise_capacitance, _fall_capacitance;
                                double capacitance, rise_capacitance, fall_capacitance;
                                fin >> temp_str >> temp_str >> _capacitance;
                                fin >> temp_str >> temp_str >> _rise_capacitance;
                                fin >> temp_str >> temp_str >> _fall_capacitance;
                                std::stringstream sin1(_capacitance.substr(0, _capacitance.length() - 1));
                                sin1 >> capacitance;
                                std::stringstream sin2(_rise_capacitance.substr(0, _rise_capacitance.length() - 1));
                                sin2 >> rise_capacitance;
                                std::stringstream sin3(_fall_capacitance.substr(0, _fall_capacitance.length() - 1));
                                sin3 >> fall_capacitance;
                                inputs.emplace_back(
                                        Cell_Input(pin_name, capacitance, rise_capacitance, fall_capacitance));
                                break;
                            } else if (temp_str == "output;") {
                                num_output++;
                                std::string _capacitance, _rise_capacitance, _fall_capacitance, _max_capacitance;
                                double capacitance, rise_capacitance, fall_capacitance, max_capacitance;
                                fin >> temp_str >> temp_str >> _capacitance;
                                fin >> temp_str >> temp_str >> _rise_capacitance;
                                fin >> temp_str >> temp_str >> _fall_capacitance;
                                fin >> temp_str >> temp_str >> _max_capacitance;
                                std::stringstream sin1(_capacitance.substr(0, _capacitance.length() - 1));
                                sin1 >> capacitance;
                                std::stringstream sin2(_rise_capacitance.substr(0, _rise_capacitance.length() - 1));
                                sin2 >> rise_capacitance;
                                std::stringstream sin3(_fall_capacitance.substr(0, _fall_capacitance.length() - 1));
                                sin3 >> fall_capacitance;
                                std::stringstream sin4(_max_capacitance.substr(0, _max_capacitance.length() - 1));
                                sin4 >> max_capacitance;
                                Cell_Output output(pin_name, capacitance, rise_capacitance, fall_capacitance,
                                                   max_capacitance);
                                while (fin >> temp_str) {
                                    if (temp_str == "function") {
                                        fin >> temp_str;
                                        std::getline(fin, temp_str); //for ":"
                                        function_str.emplace_back(temp_str.substr(2, temp_str.length() - 4));
                                    } else if (temp_str == "timing()") {
                                        input_timing(fin, output);
                                    } else if (temp_str == "internal_power()") {
                                        input_internal_power(fin, output);
                                    } else if (temp_str == "}") {
                                        count--;
                                        break;
                                    } else if (temp_str == "three_state") {
                                        is_triple = true;
                                        break;
                                    }
                                }
                                outputs.emplace_back(output);
                                break;
                            } else if (temp_str.find("clock") != std::string::npos) {
                                is_sequential = true;
                                break;
                            }
                            if (count == 1) break;
                        } else if (temp_str == "{") {
                            count++;
                        }
                    }
                }
            }
            sort(inputs.begin(), inputs.end());
            double ave_delay=0, ave_internal=0;
            int delay_count=0, internal_count=0;
            if (is_sequential or is_triple)
                continue;
            for(auto& output: outputs) {
                for(auto& input: output.timing) {
                    for(auto& entry: input.second.look_up_tables) {
                        for(auto& index: entry.second.values) {
                            for (auto &value: index) {
                                ave_delay += value;
                                delay_count++;
                            }
                        }
                    }
                }
                for(auto& input: output.internal_power) {
                    for(auto& entry: input.second.look_up_tables) {
                        for(auto& index: entry.second.values) {
                            for (auto &value: index) {
                                ave_internal += value;
                                internal_count++;
                            }
                        }
                    }
                }
            }
            // if(name.find("CLKBUF") != std::string::npos)
            //     name=name.insert(name.size()-2, "_X");
            // else
            //     name=name.insert(name.rfind('X'), "_");
            Cell *cell = new Cell(name, area, leakage, inputs, outputs, function_str, ave_delay/delay_count, ave_internal/internal_count);
            if(num_output != 1)
                continue;
            technology.cells[name] = cell;
        }
    }
    fin.close();
    //Special trick begins
    for(auto& entry: technology.cells) {
        auto cell = entry.second;
        if(cell->name == "AOI21_X1" || cell->name == "OAI21_X1") {
            cell->inputs[0].name = "A1";cell->inputs[1].name = "A2";cell->inputs[2].name = "B";cell->outputs[0].name="ZN";
        } else if(cell->name == "AOI22_X1") {
            cell->inputs[0].name = "A1";cell->inputs[1].name = "A2";cell->inputs[2].name = "B1";cell->inputs[3].name = "B2";cell->outputs[0].name="ZN";
        } else if(cell->name.find("BUF") != std::string::npos) {
            cell->inputs[0].name = "I"; cell->outputs[0].name = "Z";
        } else if(cell->name.find("INV") != std::string::npos) {
            cell->inputs[0].name = "I"; cell->outputs[0].name = "ZN";
        } else if(cell->name == "MUX2_X1") {
            cell->inputs[0].name = "I0";cell->inputs[1].name = "I1";cell->inputs[2].name = "S";cell->outputs[0].name="Z";
        } else if(cell->name.find("NAND") != std::string::npos || cell->name.find("NOR") != std::string::npos ||cell->name.find("XNOR") != std::string::npos) {
            for(int i=0; i<cell->inputs.size(); i++)cell->inputs[i].name="A"+ std::to_string(i+1); cell->outputs[0].name="ZN";
        } else {
            for (int i = 0; i < cell->inputs.size(); i++)cell->inputs[i].name = "A" + std::to_string(i + 1);cell->outputs[0].name = "Z";
        }
    }
    //Special trick ends
}

void PASyn::write_verilog(const std::string &file, Netlist &netlist, Technology& technology, bool mapped) {
    std::ofstream fout(file);
    std::cout<<file;
    assert(fout.is_open());
    int num_inverters = 0;
    if(mapped) {
        std::queue<Node*> q;
        //std::map<std::pair<std::string, std::string>, int> wire_index_map;
        //<output, input> -> index
        std::map<std::string, bool> visited;
        std::vector<std::string> wires;
        int wire_index = 1, node_index = 0;

        for(auto& output: netlist.outputs) {
            q.push(output);
        }
        while(!q.empty()) {
            auto now = q.front();
            q.pop();
            for(auto& input: now->best_cut_inputs) {
                if(visited[input] || netlist.has_node(input)->inputs.empty())
                    continue;
                else {
                    visited[input] = true;
                    wires.emplace_back(input);
                    //wire_index_map[std::make_pair(now->name, input)] = wire_index++;
                    q.push(netlist.has_node(input));
                }
            }
        }

        fout<<"module top(";
        for(auto & input : netlist.inputs) {
            auto name = input->name;
            if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                replace(name.begin(), name.end(), '[', '_');
                replace(name.begin(), name.end(), ']', '_');
            }
            fout<<name<<", ";
        }
        for(auto it = netlist.outputs.begin(); it != netlist.outputs.end(); it++) {
            auto name = (*it)->name;
            if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                replace(name.begin(), name.end(), '[', '_');
                replace(name.begin(), name.end(), ']', '_');
            }
            fout<<name;
            if(it != netlist.outputs.end()-1) {
                fout<<", ";
            }
            else
                fout<<");\n";
        }

        for(auto& wire:wires) {
            auto name = wire;
            if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                replace(name.begin(), name.end(), '[', '_');
                replace(name.begin(), name.end(), ']', '_');
            }
            fout<<"  wire "+ name<<";\n";
        }
        for (auto& entry: netlist.tmp_edges) {
            auto name = entry->source->name;
            if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                replace(name.begin(), name.end(), '[', '_');
                replace(name.begin(), name.end(), ']', '_');
            }
            fout<<"  wire "+ name + ";\n";
        }
        for(auto & input : netlist.inputs) {
            auto name = input->name;
            if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                replace(name.begin(), name.end(), '[', '_');
                replace(name.begin(), name.end(), ']', '_');
            }
            fout<<"  input "<<name<<";\n";
        }
        for(auto & output : netlist.outputs) {
            auto name = output->name;
            if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                replace(name.begin(), name.end(), '[', '_');
                replace(name.begin(), name.end(), ']', '_');
            }
            fout<<"  output "<<name<<";\n";
        }

        for(auto& output: netlist.outputs) {
            q.push(output);
        }

        wire_index = 0;
        visited.clear();
        while(!q.empty()) {
            auto now = q.front();
            q.pop();
            if(now->inputs.empty())
                continue;
            num_inverters += now->num_inverters;
            fout<<"  "<<now->cell_type<<" "<<"n_n"+ std::to_string(node_index++)<<" (\n";
            auto it = now->best_cut_inputs.begin();
            for(int i=0; i<now->best_cut_inputs.size(); i++, it++) {
                //if(wire_index_map[std::make_pair(now->name, now->inputs[i])] == 0)
                    auto name = *it;
                    if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                        replace(name.begin(), name.end(), '[', '_');
                        replace(name.begin(), name.end(), ']', '_');
                    }
                    fout<<"    ."<<technology.cells[now->cell_type]->inputs[i].name<<"("<<name<<"),\n";
                //else
                //    fout<<"    ."<<technology.cells[now->cell_type]->inputs[i].name<<"(w"<<wire_index_map[std::make_pair(now->name, now->inputs[i])]<<"),\n";
                if(!visited[*it]){
                    visited[*it] = true;
                    q.push(netlist.has_node(*it));
                }
                else {
                    continue;
                }
            }
            auto name = now->name;
            if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                replace(name.begin(), name.end(), '[', '_');
                replace(name.begin(), name.end(), ']', '_');
            }
            fout<<"    ."<<technology.cells[now->cell_type]->outputs[0].name<<"("<<name<<")\n  );\n";
        }
        for(auto& entry: netlist.tmp_inverters) {
            fout<<"  "<<entry->cell_type<<" "<<"n"+ std::to_string(node_index++)<<" (\n";
            auto name = entry->inputs[0];
            if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                replace(name.begin(), name.end(), '[', '_');
                replace(name.begin(), name.end(), ']', '_');
            }
            fout<<"    ."<<technology.cells[entry->cell_type]->inputs[0].name<<"("<<name<<",\n";
            name = entry->name;
            if (name.find('[') != std::string::npos && name.find(']') != std::string::npos) {
                replace(name.begin(), name.end(), '[', '_');
                replace(name.begin(), name.end(), ']', '_');
            }
            fout<<"    ."<<technology.cells[entry->cell_type]->outputs[0].name<<"("<<name<<")\n  );\n";
        }
        fout<<"endmodule\n";
    }
    std::cout<<num_inverters;
}

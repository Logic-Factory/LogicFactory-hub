//
// Created by zephyr on 2021/11/12.
//

#include "netlist.h"

#include <utility>

std::string PASyn::infix_to_prefix(std::string infix_exp) {
    std::string prefix_exp;
    std::stack<char> s1, s2;
    std::reverse(infix_exp.begin(), infix_exp.end());
    for (auto &ch: infix_exp) {
        if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
            s2.push(ch);
        else {
            switch (ch) {
                case ')':
                    s1.push(ch);
                    break;
                case '(': {
                    while (!s1.empty()) {
                        if (s1.top() != ')') {
                            s2.push(s1.top());
                            s1.pop();
                        } else {
                            s1.pop();
                            break;
                        }
                    }
                    break;
                }
                case '!':
                    s1.push(ch);
                    break;
                case '&': {
                    if (s1.empty() || s1.top() == ')') {
                        s1.push(ch);
                        break;
                    }
                    while (!s1.empty() && s1.top() != ')' && (s1.top() == '!')) {
                        s2.push(s1.top());
                        s1.pop();
                    }
                    s1.push(ch);
                    break;
                }
                case '+': {
                    if (s1.empty() || s1.top() == ')') {
                        s1.push(ch);
                        break;
                    }
                    while (!s1.empty() && s1.top() != ')' && (s1.top() != '!' || s1.top() != '&' || s1.top() != '^')) {
                        s2.push(s1.top());
                        s1.pop();
                    }
                    s1.push(ch);
                    break;
                }
                case '^':
                    if (s1.empty() || s1.top() == ')') {
                        s1.push(ch);
                        break;
                    }
                    while (!s1.empty() && s1.top() != ')' && (s1.top() != '!' || s1.top() != '&')) {
                        s2.push(s1.top());
                        s1.pop();
                    }
                    s1.push(ch);
                    break;
                default:
                    assert(false);
            }
        }
    }
    while (!s1.empty()) {
        if (s1.top() != ')')
            s2.push(s1.top());
        s1.pop();
    }
    while (!s2.empty()) {
        prefix_exp += s2.top();
        s2.pop();
    }
    return prefix_exp;
}

void get_exp_function(std::vector<std::pair<std::vector<int>, bool>> &, std::istringstream &,
                      std::map<std::string, int> &, bool);

void generate_fun(std::vector<std::pair<std::vector<int>, bool>> &result, std::istringstream &sin,
                  std::map<std::string, int> &input_index, bool input) {
    char temp;
    sin >> temp;
    if (temp == '!' || temp == '&' || temp == '^' || temp == '+') {
        sin.putback(temp);
        get_exp_function(result, sin, input_index, input);
    } else {
        if (result.empty()) {
            std::vector<int> result_entry(input_index.size(), -1);
            result_entry[input_index[std::string(1, temp)]] = int(input);
            result.emplace_back(std::make_pair(result_entry, true));
            // Warning: Assume in PLA format the output is on-set
        } else {
            for (auto vec = result.begin(); vec != result.end();) {
                if((*vec).first[input_index[std::string(1, temp)]] != -1 && (*vec).first[input_index[std::string(1, temp)]] != int(input)) {
                    vec = result.erase(vec);
                }
                else {
                    (*vec).first[input_index[std::string(1, temp)]] = int(input);
                    vec++;
                }
            }
        }
    }
}

void get_exp_function(std::vector<std::pair<std::vector<int>, bool>> &result, std::istringstream &sin,
                      std::map<std::string, int> &input_index, bool target) {
    char op, temp1, temp2;
    sin >> op;
    switch (op) {
        case '!':
            generate_fun(result, sin, input_index, !target);
            break;
        case '&':
            if (target) {
                generate_fun(result, sin, input_index, true);
                generate_fun(result, sin, input_index, true);
            } else {
                std::vector<std::pair<std::vector<int>, bool>> result_copy(result);
                generate_fun(result, sin, input_index, false);
                generate_fun(result_copy, sin, input_index, false);
                for (auto &vector: result_copy)
                    result.emplace_back(vector);
            }
            break;
        case '+':
            if (!target) {
                generate_fun(result, sin, input_index, false);
                generate_fun(result, sin, input_index, false);
            } else {
                std::vector<std::pair<std::vector<int>, bool>> result_copy(result);
                generate_fun(result, sin, input_index, true);
                generate_fun(result_copy, sin, input_index, true);
                for (auto &vector: result_copy)
                    result.emplace_back(vector);
            }
            break;
        case '^':
            if (target) {
                std::vector<std::pair<std::vector<int>, bool>> result_copy(result);
                std::istringstream sin_copy(sin.tellg() == -1 ? "" : sin.str().substr(sin.tellg()));
                generate_fun(result, sin, input_index, true);
                generate_fun(result, sin, input_index, false);
                generate_fun(result_copy, sin_copy, input_index, false);
                generate_fun(result_copy, sin_copy, input_index, true);
                for (auto &vector: result_copy)
                    result.emplace_back(vector);
            } else {
                std::vector<std::pair<std::vector<int>, bool>> result_copy(result);
                std::istringstream sin_copy(sin.tellg() == -1 ? "" : sin.str().substr(sin.tellg()));
                generate_fun(result, sin, input_index, true);
                generate_fun(result, sin, input_index, true);
                generate_fun(result_copy, sin_copy, input_index, false);
                generate_fun(result_copy, sin_copy, input_index, false);
                for (auto &vector: result_copy)
                    result.emplace_back(vector);
            }
            break;
        default:
            // Buffer situation
            assert(input_index.size() == 1);
            std::vector<int> result_entry(1, 1);
            result.emplace_back(std::make_pair(result_entry, true));
    }
}

PASyn::Function::Function(int _num_input, const std::string &_function) {
    num_input = _num_input;
    if (_num_input == 0) {
        if (_function.empty()) {
            function.emplace_back(std::make_pair(std::vector<int>(), false));
            type = 0;
        } else {
            function.emplace_back(std::make_pair(std::vector<int>(), true));
            type = 1;
        }
        return;
    }
    std::vector<std::string> entries = PASyn::split(_function, '\n');
    for (auto &entry: entries) {
        std::vector<std::string> _temp_str = PASyn::split(entry);
        std::vector<int> inputs;
        for (char i: _temp_str[0])
            inputs.emplace_back(i == '1' ? 1 : (i == '0' ? 0 : -1));
        function.emplace_back(std::make_pair(inputs, _temp_str[1] == "1"));
    }

    if (_num_input <= 2) {
        type = FunctionType.at(_function);
    }
}

PASyn::Function::Function(const std::vector<Cell_Input> &inputs, std::string _function_str) {
    for (auto it=_function_str.begin(); it != _function_str.end();) {
        if (*it == ' ') {
            if((*(it-1) >= 65 && *(it-1) <= 90) || (*(it+1) >= 65 && *(it+1) <= 90))
                *it = '&';
            else {
                it = _function_str.erase(it);
                continue;
            }
        }
        it++;
    }

    std::string prefix_exp = PASyn::infix_to_prefix(_function_str);
    std::vector<std::pair<std::vector<int>, bool>> _function;
    std::map<std::string, int> inputs_index;
    for (int i = 0; i < inputs.size(); i++) {
        inputs_index[inputs[i].name] = i;
    }

    std::istringstream sin(prefix_exp);
    get_exp_function(_function, sin, inputs_index, true);

    function = _function;
    num_input = int(inputs.size());
    if (num_input <= 2) {
        std::string function_str;
        for (auto &ch: prefix_exp)
            if ((!(ch >= 65 && ch <= 90)) && (!(ch >= 97 && ch <= 122)))
                function_str += ch;
        type = function_str.empty() ? 2 : FunctionType.at(function_str);
    }
}

PASyn::Netlist::~Netlist() {
    for (auto &node: nodes)
        delete node;
    for (auto &edge: edges)
        delete edge;
}

PASyn::Node *PASyn::Netlist::has_node(PASyn::Node *node) {
    for (auto &_node: nodes)
        if (_node->name == node->name)
            return _node;
    return nullptr;
}

PASyn::Node *PASyn::Netlist::has_node(const std::string &node) {
    for (auto &_node: nodes)
        if (_node->name == node)
            return _node;
    for (auto &_node: tmp_inverters)
        if (_node->name == node)
            return _node;
    return nullptr;
}

void PASyn::Netlist::add_node(PASyn::Node *node) {
    Node *node_pos = has_node(node);
    if (node_pos != nullptr) {
        node_pos->update_function(node->functions);
        node_pos->inputs = node->inputs;
        if (node_pos->num_fanout < node->num_fanout) {
            node_pos->outputs = node->outputs;
            node_pos->num_fanout = node->num_fanout;
        }
        node_pos->num_fanin = node->num_fanin;
        node_pos->cell_type = node->cell_type;
        delete node;
    } else {
        nodes.emplace_back(node);
    }
}

void PASyn::Netlist::clear() {
    for(auto& node: nodes)
        delete node;
    for(auto& edge: edges)
        delete edge;
}

void PASyn::Netlist::add_inverter(std::pair<int, int> inverter_index, std::string now) {
    auto node = has_node(now);
    for(int i=0; i<inverter_index.first; i++) {
        Node* inverter = new Node(node->inputs[i]+"_inv", 1, std::vector<unsigned int>(1, 1), std::vector<std::string>{node->inputs[i]}, std::vector<Function>(1, Function(1, "0 1")),
                                  std::vector<double>(1, -1));
        tmp_inverters.emplace_back(inverter);
        for(auto& input: node->inputs) {
            input += "_inv";
            tmp_edges.emplace_back(new Edge(node, inverter));
        }
    }
    if(inverter_index.second == 1) {
        Node* inverter = new Node(node->name+"_inv", 1, std::vector<unsigned int>(1, node->num_fanout[0]), std::vector<std::string>{node->name}, std::vector<Function>(1, Function(1, "0 1")),
                                  std::vector<double>(1, -1));
        inverter->outputs = node->outputs;
        tmp_inverters.emplace_back(inverter);
        for(auto& entry: node->outputs) {
            for (auto &output: entry) {
                *(std::find(has_node(output)->inputs.begin(), has_node(output)->inputs.end(), node->name)) = node->name+"_inv";
                tmp_edges.emplace_back(new Edge(inverter, has_node(output)));
            }
        }
    }
}

void PASyn::Netlist::delete_inverter(std::string node) {
    for(auto& entry: has_node(node)->outputs) {
        for (auto &output: entry) {
            *(std::find(has_node(output)->inputs.begin(), has_node(output)->inputs.end(), node)) = node.substr(0, node.find("_inv"));
            delete has_edge(has_node(node), has_node(output));
        }
    }
    tmp_inverters.erase(std::find(tmp_inverters.begin(), tmp_inverters.end(), has_node(node)));
    delete has_node(node);
    delete has_edge(has_node(has_node(node)->inputs[0]), has_node(node));
}

PASyn::Edge *PASyn::Netlist::has_edge(Node* source, Node* drain) {
    for(auto& edge: edges) {
        if(edge->source->name == source->name && edge->drain->name == drain->name)
            return edge;
    }
    for(auto& edge: tmp_edges) {
        if(edge->source->name == source->name && edge->drain->name == drain->name)
            return edge;
    }
    return nullptr;
}

void PASyn::Node::update_function(std::vector<PASyn::Function> &_functions) {
    functions = _functions;
}

inline std::string negate(const std::string& str) {
    std::string result;
    for(auto ch: str)
        result += ch == '0' ? '1' :'0';
    return result;
}

std::set<std::pair<std::string, std::pair<int, int>>> PASyn::npn(const std::string& str, bool negate_input, bool negate_output) {
    std::vector<std::pair<std::string, std::pair<int, int>>> result = {std::make_pair(str, std::make_pair(0, 0))};
    // permute inputs
    switch (str.size()) {
        case 2: {
            break;
        }
        case 4: {
            std::string tmp(str);
            std::swap(tmp[1], tmp[2]);
            result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0)));
            break;
        }
        case 8: {
            std::string tmp(str);//123
            std::swap(tmp[1], tmp[2]), std::swap(tmp[5], tmp[6]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//132
            std::swap(tmp[2], tmp[4]), std::swap(tmp[5], tmp[3]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//213
            std::swap(tmp[4], tmp[1]), std::swap(tmp[2], tmp[4]), std::swap(tmp[3], tmp[5]), std::swap(tmp[5], tmp[6]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//231
            std::swap(tmp[1], tmp[2]), std::swap(tmp[2], tmp[4]), std::swap(tmp[3], tmp[6]), std::swap(tmp[5], tmp[6]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//312
            std::swap(tmp[1], tmp[4]), std::swap(tmp[3], tmp[6]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0)));//321
            break;
        }
        case 16: {
            std::string tmp(str);//1234
            std::swap(tmp[1], tmp[2]), std::swap(tmp[5], tmp[6]), std::swap(tmp[9], tmp[10]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//1243
            std::swap(tmp[1], tmp[2]), std::swap(tmp[2], tmp[4]), std::swap(tmp[3], tmp[6]), std::swap(tmp[5], tmp[6]), std::swap(tmp[9], tmp[10]), std::swap(tmp[10], tmp[12]), std::swap(tmp[14], tmp[11]), std::swap(tmp[14], tmp[13]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//1342
            std::swap(tmp[4], tmp[2]), std::swap(tmp[5], tmp[3]), std::swap(tmp[12], tmp[10]), std::swap(tmp[13], tmp[11]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//1324
            std::swap(tmp[4], tmp[1]), std::swap(tmp[6], tmp[3]), std::swap(tmp[12], tmp[9]), std::swap(tmp[14], tmp[11]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//1432
            std::swap(tmp[1], tmp[4]), std::swap(tmp[2], tmp[4]), std::swap(tmp[3], tmp[5]), std::swap(tmp[5], tmp[6]), std::swap(tmp[9], tmp[12]), std::swap(tmp[10], tmp[12]), std::swap(tmp[13], tmp[11]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//1423

            std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[9]), std::swap(tmp[6], tmp[10]), std::swap(tmp[7], tmp[11]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//2134
            std::swap(tmp[1], tmp[2]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[10]), std::swap(tmp[6], tmp[9]), std::swap(tmp[7], tmp[11]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//2143
            std::swap(tmp[1], tmp[2]), std::swap(tmp[2], tmp[4]), std::swap(tmp[3], tmp[6]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[10]), std::swap(tmp[6], tmp[12]), std::swap(tmp[7], tmp[14]), std::swap(tmp[12], tmp[9]), std::swap(tmp[14], tmp[11]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//2341
            std::swap(tmp[2], tmp[4]), std::swap(tmp[3], tmp[5]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[9]), std::swap(tmp[6], tmp[12]), std::swap(tmp[7], tmp[13]), std::swap(tmp[10], tmp[12]), std::swap(tmp[11], tmp[13]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//2314
            std::swap(tmp[1], tmp[4]), std::swap(tmp[2], tmp[4]), std::swap(tmp[3], tmp[5]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[12]), std::swap(tmp[6], tmp[9]), std::swap(tmp[7], tmp[13]), std::swap(tmp[12], tmp[10]), std::swap(tmp[13], tmp[11]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//2413
            std::swap(tmp[1], tmp[4]), std::swap(tmp[3], tmp[6]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[12]), std::swap(tmp[6], tmp[10]), std::swap(tmp[7], tmp[14]), std::swap(tmp[9], tmp[12]), std::swap(tmp[11], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//2431

            std::swap(tmp[2], tmp[8]), std::swap(tmp[3], tmp[9]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[9]), std::swap(tmp[6], tmp[10]), std::swap(tmp[7], tmp[11]), std::swap(tmp[10], tmp[12]), std::swap(tmp[11], tmp[13]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//3124
            std::swap(tmp[1], tmp[2]), std::swap(tmp[2], tmp[8]), std::swap(tmp[3], tmp[10]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[10]), std::swap(tmp[6], tmp[9]), std::swap(tmp[7], tmp[11]), std::swap(tmp[12], tmp[10]), std::swap(tmp[14], tmp[11]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//3142
            std::swap(tmp[2], tmp[8]), std::swap(tmp[3], tmp[9]), std::swap(tmp[6], tmp[12]), std::swap(tmp[7], tmp[13]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//3214
            std::swap(tmp[1], tmp[2]), std::swap(tmp[2], tmp[8]), std::swap(tmp[3], tmp[10]), std::swap(tmp[5], tmp[6]), std::swap(tmp[6], tmp[12]), std::swap(tmp[7], tmp[14]), std::swap(tmp[9], tmp[10]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//3241
            std::swap(tmp[1], tmp[4]), std::swap(tmp[2], tmp[8]), std::swap(tmp[3], tmp[12]), std::swap(tmp[6], tmp[9]), std::swap(tmp[7], tmp[13]), std::swap(tmp[14], tmp[11]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//3412
            std::swap(tmp[1], tmp[4]), std::swap(tmp[2], tmp[8]), std::swap(tmp[3], tmp[12]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[6]), std::swap(tmp[6], tmp[10]), std::swap(tmp[7], tmp[14]), std::swap(tmp[9], tmp[10]), std::swap(tmp[13], tmp[11]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//3421

            std::swap(tmp[1], tmp[8]), std::swap(tmp[2], tmp[8]), std::swap(tmp[3], tmp[9]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[10]), std::swap(tmp[6], tmp[9]), std::swap(tmp[7], tmp[11]), std::swap(tmp[9], tmp[12]), std::swap(tmp[13], tmp[11]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//4123
            std::swap(tmp[1], tmp[8]), std::swap(tmp[3], tmp[10]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[9]), std::swap(tmp[6], tmp[10]), std::swap(tmp[7], tmp[11]), std::swap(tmp[9], tmp[12]), std::swap(tmp[11], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//4132
            std::swap(tmp[1], tmp[8]), std::swap(tmp[2], tmp[8]), std::swap(tmp[3], tmp[9]), std::swap(tmp[5], tmp[12]), std::swap(tmp[6], tmp[12]), std::swap(tmp[7], tmp[13]), std::swap(tmp[9], tmp[10]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//4213
            std::swap(tmp[1], tmp[8]), std::swap(tmp[3], tmp[10]), std::swap(tmp[5], tmp[12]), std::swap(tmp[7], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//4231
            std::swap(tmp[1], tmp[8]), std::swap(tmp[2], tmp[4]), std::swap(tmp[3], tmp[12]), std::swap(tmp[4], tmp[8]), std::swap(tmp[5], tmp[9]), std::swap(tmp[6], tmp[9]), std::swap(tmp[7], tmp[13]), std::swap(tmp[9], tmp[10]), std::swap(tmp[14], tmp[11]), std::swap(tmp[13], tmp[14]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0))), tmp = str;//4312
            std::swap(tmp[1], tmp[8]), std::swap(tmp[2], tmp[4]), std::swap(tmp[3], tmp[12]), std::swap(tmp[10], tmp[5]), std::swap(tmp[7], tmp[14]), std::swap(tmp[13], tmp[11]), result.emplace_back(std::make_pair(tmp, std::make_pair(0, 0)));//4321
            break;
        }
        default:
            std::cout<<"Not implemented\n";
            assert(false);
    }

    // negate inputs
    if(negate_input) {
        switch (str.size()) {
            case 2:
                break;
            case 4: {
                std::string tmp(str.begin() + 2, str.end());
                tmp.append(str.begin(), str.begin() + 2);
                result.emplace_back(std::make_pair(tmp, std::make_pair(1, 0)));
                tmp = str, std::reverse(tmp.begin(), tmp.end());
                result.emplace_back(std::make_pair(tmp, std::make_pair(2, 0)));
                break;
            }
            case 8: {
                std::string tmp(str.begin() + 4, str.end());
                tmp.append(str.begin(), str.begin() + 4);
                result.emplace_back(std::make_pair(tmp, std::make_pair(1, 0)));
                tmp = str.substr(6, 2), tmp += str.substr(4, 2), tmp += str.substr(2, 2), tmp += str.substr(0, 2);
                result.emplace_back(std::make_pair(tmp, std::make_pair(2, 0)));
                tmp = str, std::reverse(tmp.begin(), tmp.end());
                result.emplace_back(std::make_pair(tmp, std::make_pair(3, 0)));
                break;
            }
            case 16: {
                std::string tmp(str.begin() + 8, str.end());
                tmp.append(str.begin(), str.begin() + 8);
                result.emplace_back(std::make_pair(tmp, std::make_pair(1, 0)));
                tmp = str.substr(12, 4), tmp += str.substr(8, 4), tmp += str.substr(4, 4), tmp += str.substr(0, 4);
                result.emplace_back(std::make_pair(tmp, std::make_pair(2, 0)));
                tmp = str.substr(14, 2), tmp += str.substr(12, 2), tmp += str.substr(10, 2), tmp += str.substr(8,
                                                                                                               2), tmp += str.substr(
                        6, 2), tmp += str.substr(4, 2), tmp += str.substr(2, 2), tmp += str.substr(0, 2);
                result.emplace_back(std::make_pair(tmp, std::make_pair(3, 0)));
                tmp = str, std::reverse(tmp.begin(), tmp.end());
                result.emplace_back(std::make_pair(tmp, std::make_pair(4, 0)));
                break;
            }
            default:
                std::cout << "Not implemented\n";
                assert(false);
        }
    }

    // negate output
    if(negate_output) {
        std::vector<std::pair<std::string, std::pair<int, int>>> tmp;
        tmp.reserve(result.size());
        for (auto &entry: result)
            tmp.emplace_back(std::make_pair(negate(entry.first), std::make_pair(entry.second.first, 1)));
        result.insert(result.begin(), tmp.begin(), tmp.end());
    }

    return {result.begin(), result.end()};
}

/*bool PASyn::TruthTable::operator==(PASyn::TruthTable &truth_table) const{
    std::set<std::pair<std::string, std::pair<int, int>>> npn_string = PASyn::npn(truth_table.str, true, true);
    for(auto& entry: npn_string)
        if(str == entry.first)
            return true;
    return false;
}*/

std::pair<bool, std::pair<int, int>> PASyn::TruthTable::equal(TruthTable& truth_table) const {
    std::set<std::pair<std::string, std::pair<int, int>>> npn_string = PASyn::npn(truth_table.str, true, true);
    for(auto& entry: npn_string)
        if(str == entry.first)
            return std::make_pair(true, entry.second);
    return std::make_pair(false, std::make_pair(0, 0));
}

PASyn::TruthTable::TruthTable(PASyn::Function &functions) {
    num_bits = functions.num_input;
    std::string _str;
    char target_value = functions.function[0].second ? '1' : '0';
    char invert_target = functions.function[0].second ? '0' : '1';
    for(int i=0; i<1<<num_bits; i++) {
        std::vector<int> binary;
        int temp = i;
        bool flag1 = true;
        while(temp) {
            binary.insert(binary.begin(), temp%2);
            temp/=2;
        }
        while(binary.size() < num_bits)
            binary.insert(binary.begin(), 0);
        for(auto& entry: functions.function) {
            bool flag2 = true;
            for(int j=0; j<num_bits; j++) {
                if(entry.first[j] != binary[j] && entry.first[j] != -1)
                    flag2 = false;
            }
            if(flag2) {
                _str += target_value;
                flag1 = false;
                break;
            }
        }
        if(flag1)
            _str+=invert_target;
    }
    str = _str;
}

PASyn::TruthTable::TruthTable(const std::string& function) {
    num_bits = int(log(double(function.size()))/log(2));
    str = function;
}

void PASyn::TruthTable::generate_input_1(PASyn::TruthTable * truth_table, int op) {
    for(auto& value: truth_table->str) {
        char ch;
        switch (op) {
            case 2:
                ch = value;
                break;
            case 3:
                ch = value == '0' ? '1' : '0';
                break;
            default:
                assert(false);
        }
        str += ch;
    }
}

bool PASyn::TruthTable::operator<(const PASyn::TruthTable &other) const {
    return str < other.str;
}

inline void generate_partial_index(std::map<int, int>& map, const std::vector<int>& bit_index, unsigned int num_inputs) {
    unsigned end = 1<<num_inputs;
    std::vector<int> b_vector;
    std::vector<int> b_vector_slice;
    b_vector.reserve(num_inputs);
    b_vector_slice.reserve(num_inputs);
    for(int i=0; i<end; i++) {
        b_vector = PASyn::int_to_bvector(i, num_inputs);
        for(auto& entry: bit_index)
            b_vector_slice.emplace_back(b_vector[entry]);
        map[i] = PASyn::bvector_to_int(b_vector_slice);
        b_vector_slice.clear();
    }
}

void PASyn::TruthTable::generate_input_2(PASyn::TruthTable *in1, PASyn::TruthTable *in2,
                                         const std::set<std::string> &in1_inputs,
                                         const std::set<std::string> &in2_inputs, const std::set<std::string> &new_inputs, int op) {
    std::map<int, int> new_in1_index, new_in2_index;
    std::vector<int> bit_index_in1, bit_index_in2;
    int i=0;
    for(auto& entry: new_inputs) {
        if(in1_inputs.find(entry) != in1_inputs.end())
            bit_index_in1.emplace_back(i);
        if(in2_inputs.find(entry) != in2_inputs.end())
            bit_index_in2.emplace_back(i);
        i++;
    }
    generate_partial_index(new_in1_index, bit_index_in1, new_inputs.size());
    generate_partial_index(new_in2_index, bit_index_in2, new_inputs.size());

    unsigned int size = 1<<new_inputs.size();
    for(int index = 0; index<size; index++) {
        char in1_ch = in1->str[new_in1_index[index]], in2_ch = in2->str[new_in2_index[index]];
        char ch;
        switch (op) {
            case 4:
                ch = (in1_ch == '0' && in2_ch == '0') ? '0' : '1';
                break;
            case 5:
                ch = (in1_ch == '0' && in2_ch == '0') ? '1' : '0';
                break;
            case 6:
                // NOTE: here may exist asymmetry problem
                ch = (in1_ch == '0' && in2_ch == '1') ? '0' : '1';
                break;
            case 7:
                // NOTE: here may exist asymmetry problem
                ch = (in1_ch == '0' && in2_ch == '1') ? '1' : '0';
                break;
            case 8:
                ch = (in1_ch == '1' && in2_ch == '1') ? '0' : '1';
                break;
            case 9:
                ch = (in1_ch == '1' && in2_ch == '1') ? '1' : '0';
                break;
            case 12:
                ch = ((in1_ch == '1' && in2_ch == '1') || (in1_ch == '1' && in2_ch == '0')) ? '1' : '0';
                break;
            case 13:
                ch = ((in1_ch == '1' && in2_ch == '1') || (in1_ch == '0' && in2_ch == '1')) ? '1' : '0';
                break;
            case 14:
                ch = ((in1_ch == '1' && in2_ch == '1') || (in1_ch == '0' && in2_ch == '0')) ? '0' : '1';
                break;
            case 15:
                ch = ((in1_ch == '1' && in2_ch == '1') || (in1_ch == '0' && in2_ch == '0')) ? '1' : '0';
                break;
            case 16:
                ch = ((in1_ch == '0' && in2_ch == '0') || (in1_ch == '1' && in2_ch == '0')) ? '1' : '0';
                break;
            case 17:
                ch = ((in1_ch == '0' && in2_ch == '0') || (in1_ch == '0' && in2_ch == '1')) ? '1' : '0';
                break;
            default:
                assert(false);
        }
        str += ch;
    }
}

std::vector<std::string> PASyn::check_equivalence(PASyn::TruthTable* truth_table,  std::map<PASyn::TruthTable, std::vector<std::string>>& technology_truth_tables) {
    for(auto& entry: technology_truth_tables) {
        auto result = entry.first.equal(*truth_table);
        if(result.first)
            return entry.second;
    }
    return std::vector<std::string>{};
}

std::pair<std::vector<std::string>, std::pair<int, int>> PASyn::check_equivalence(TruthTable* truth_table,  std::map<TruthTable, std::vector<std::string>>& technology_truth_tables, bool npn) {
    assert(npn);
    for(auto& entry: technology_truth_tables) {
        auto result = entry.first.equal(*truth_table);
        if(result.first)
            return std::make_pair(entry.second, result.second);
    }
    return std::make_pair(std::vector<std::string>{}, std::make_pair(0, 0));
}
//
// Created by zephyr on 2021/11/12.
// Modified by zephyr on 2023/7/18
//

#include "netlist.h"
#include "../utility/utility.h"
#include <utility>

std::string infix_to_prefix(std::string infix_exp) {
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

NET::Function::Function(int _num_input, const std::string &_function) {
    num_input = _num_input;
    if (_num_input == 0) {
        if (_function.empty()) {
            function.emplace_back(std::vector<int>(), false);
            type = 0;
        } else {
            function.emplace_back(std::vector<int>(), true);
            type = 1;
        }
        return;
    }
    std::vector<std::string> entries = split(_function, '\n');
    for (auto &entry: entries) {
        std::vector<std::string> _temp_str = split(entry);
        std::vector<int> inputs;
        for (char i: _temp_str[0])
            inputs.emplace_back(i == '1' ? 1 : (i == '0' ? 0 : -1));
        function.emplace_back(inputs, _temp_str[1] == "1");
    }
    if (_num_input <= 2) {
        type = FunctionType.at(_function);
    }
}

void NET::Netlist::rename(Node *node, std::string new_name) {

    for (auto &input: node->inputs) {
        for (auto &_node: this->has_node(input)->outputs[0])
            if (_node == node->name)
                _node = new_name;
    }

    for (auto &output: node->outputs[0]) {
        for (auto &_node: this->has_node(output)->inputs) {
            if (_node == node->name)
                _node = new_name;
        }
    }
    node->name = new_name;
}

NET::Function::Function(int type) {
    num_input = 2;
    std::string _function;
    switch (type) {
        case 4:
            _function = "00 0";
            break;
        case 7:
            _function = "01 1";
            break;
        case 9:
            _function = "11 1";
            break;
        case 12:
            _function = "10 1\n 11 1";
            break;
        case 13:
            _function = "01 1\n 11 1";
            break;
        case 14:
            _function = "01 1\n 10 1";
            break;
        default:
            assert(false);
    }
    std::vector<std::string> entries = split(_function, '\n');
    for (auto &entry: entries) {
        std::vector<std::string> _temp_str = split(entry);
        std::vector<int> inputs;
        for (char i: _temp_str[0])
            inputs.emplace_back(i == '1' ? 1 : (i == '0' ? 0 : -1));
        function.emplace_back(std::make_pair(inputs, _temp_str[1] == "1"));
    }
    this->type = type;
}

NET::Netlist::~Netlist() {
    for (auto &node: nodes)
        delete node;
    for (auto &edge: edges)
        delete edge;
}

NET::Node *NET::Netlist::has_node(NET::Node *node) {
    for (auto &_node: nodes)
        if (_node->name == node->name)
            return _node;
    return nullptr;
}

NET::Node *NET::Netlist::has_node(const std::string &node) {
    for (auto &_node: nodes)
        if (_node->name == node)
            return _node;
    return nullptr;
}

void NET::Netlist::add_node(NET::Node *node) {
    Node *node_pos = has_node(node);
    if (node_pos != nullptr) {
        //std::cout<<node->name<<" A\n";
        node_pos->update_function(node->functions);
        node_pos->inputs = node->inputs;
        if (node_pos->num_fanout < node->num_fanout) {
            node_pos->outputs = node->outputs;
            node_pos->num_fanout = node->num_fanout;
        }
        node_pos->num_fanin = node->num_fanin;
        node_pos->cell_type = node->cell_type;
        //delete node;
    } else {
        //std::cout<<node->name<<" B\n";
        nodes.emplace_back(node);
    }
}

void NET::Netlist::clear() {
    for (auto &node: nodes)
        delete node;
    for (auto &edge: edges)
        delete edge;
}

NET::Edge *NET::Netlist::has_edge(Node *source, Node *drain) {
    for (auto &edge: edges) {
        if (edge->source->name == source->name && edge->drain->name == drain->name)
            return edge;
    }
    return nullptr;
}


NET::Netlist::Netlist(const Netlist &netlist) {
    for (auto &node: netlist.nodes) {
        this->nodes.emplace_back(new Node(*node));
    }
    this->name = netlist.name;
    for (auto &node: netlist.inputs) {
        this->inputs.emplace_back(this->has_node(node->name));
    }
    for (auto &node: netlist.outputs) {
        this->outputs.emplace_back(this->has_node(node->name));
    }
    for (auto &edge: netlist.edges) {
        this->edges.emplace_back(new Edge(this->has_node(edge->source->name), this->has_node(edge->drain->name)));
    }
}

void NET::Node::update_function(std::vector<NET::Function> &_functions) {
    functions = _functions;
}

inline void
generate_partial_index(std::map<int, int> &map, const std::vector<int> &bit_index, unsigned int num_inputs) {
    unsigned end = 1 << num_inputs;
    std::vector<int> b_vector;
    std::vector<int> b_vector_slice;
    b_vector.reserve(num_inputs);
    b_vector_slice.reserve(num_inputs);
    for (int i = 0; i < end; i++) {
        b_vector = int_to_bvector(i, num_inputs);
        for (auto &entry: bit_index)
            b_vector_slice.emplace_back(b_vector[entry]);
        map[i] = bvector_to_int(b_vector_slice);
        b_vector_slice.clear();
    }
}

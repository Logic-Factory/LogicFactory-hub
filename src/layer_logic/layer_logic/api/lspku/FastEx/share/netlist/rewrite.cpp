//
// Created by zephyr on 7/17/2023.
//
#include "netlist.h"
#include "../utility/utility.h"


std::string extract_truth_table(const NET::Function &function) {
    std::vector<bool> truth_table_vector;
    if (function.function[0].second) {
        truth_table_vector = std::vector<bool>(1 << function.num_input, false);
        for (auto &entry: function.function) {
            auto truth_table_index = bvector_to_int(entry.first, true);
            for (auto &index: truth_table_index)
                truth_table_vector[index] = true;
        }
    } else {
        truth_table_vector = std::vector<bool>(1 << function.num_input, true);
        for (auto &entry: function.function) {
            auto truth_table_index = bvector_to_int(entry.first, true);
            for (auto &index: truth_table_index)
                truth_table_vector[index] = false;
        }
    }

    std::string result;
    for (int i = 0; i < truth_table_vector.size(); i += 4) {
        int temp = 0;
        for (int j = 0; j < 4; j++) {
            temp = truth_table_vector[i + j] + (temp << 1);
        }
        result += temp < 10 ? std::to_string(temp) : std::string(1, 'a' + temp - 10);
    }
    return result;
}

void initialize_signal_probability(NET::Netlist &netlist, std::vector<double> input_signal_probability = {}) {
    //topology sort
    std::map<std::string, int> name_inputs;
    std::queue<NET::Node *> topological_queue;
    std::vector<NET::Node *> topological_order;
    for (auto &node: netlist.nodes)
        name_inputs[node->name] = node->inputs.size();

    for (auto &input: netlist.inputs) {
        topological_queue.push(input);
    }
    if (!input_signal_probability.empty()) {
        for (int i = 0; i < netlist.inputs.size(); i++)
            netlist.inputs[i]->signal_probability[0] = input_signal_probability[i];
    }
    while (!topological_queue.empty()) {
        auto node = topological_queue.front();
        topological_queue.pop();
        topological_order.emplace_back(node);
        for (auto &output: node->outputs[0]) {
            name_inputs[output]--;
            if (name_inputs[output] == 0) {
                topological_queue.push(netlist.has_node(output));
            }
        }
    }

    //initial signal probability of being 1 in topological order
    for (auto &node: topological_order) {
        if (node->signal_probability[0] != -1)
            continue;
        double signal_probability = 0;
        for (auto &entry: node->functions[0].function) {
            double result = 1;
            for (int i = 0; i < entry.first.size(); i++) {
                if (entry.first[i] == 1)
                    result *= netlist.has_node(node->inputs[i])->signal_probability[0];
                else if (entry.first[i] == 0)
                    result *= (1 - netlist.has_node(node->inputs[i])->signal_probability[0]);
            }
            signal_probability += result;

        }
        signal_probability = node->functions[0].function[0].second ? signal_probability : 1 - signal_probability;
        node->signal_probability[0] = signal_probability;
    }
}

void substitute_node(std::map<std::string, bool> &name_count,
                     std::map<std::pair<std::string, std::string>, NET::Netlist *> &optimal_library,
                     NET::Netlist &netlist, NET::Node *original_node, const std::string &truth_table) {
    std::string label = "5+5+5+5";
    std::cout<<truth_table<<"\n";
    if (optimal_library[std::make_pair(truth_table, label)] == nullptr) {
        std::cout << truth_table << "?\n";
        return;
    }
    NET::Netlist *sub_netlist = new NET::Netlist(*optimal_library[std::make_pair(truth_table, label)]);
    //NET::Netlist* sub_netlist = new NET::Netlist(*optimal_library.begin()->second);

    // rename and add new internal nodes
    for (auto node: sub_netlist->nodes) {
        //std::cout<<node->name;
        if (std::find(sub_netlist->inputs.begin(), sub_netlist->inputs.end(), node) == sub_netlist->inputs.end() &&
            std::find(sub_netlist->outputs.begin(), sub_netlist->outputs.end(), node) == sub_netlist->outputs.end()) {
            std::string new_name = "n_" + std::to_string(netlist.nodes.size());
            if (name_count[new_name]) {
                new_name = "new_" + new_name;
            }
            sub_netlist->rename(node, new_name);
            name_count[new_name] = true;
            netlist.add_node(node);
        }
    }

    // delete original node from outputs of its inputs
    for (auto &input: original_node->inputs) {
        netlist.has_node(input)->outputs[0].erase(
                std::find(netlist.has_node(input)->outputs[0].begin(), netlist.has_node(input)->outputs[0].end(),
                          original_node->name));
    }

    // add inputs of sub-netlist to outputs of inputs of original node; update input information to sub netlists
    assert(original_node->inputs.size() == sub_netlist->inputs.size());
    for (int i = 0; i < sub_netlist->inputs.size(); i++) {
        netlist.has_node(original_node->inputs[i])->outputs[0].insert(
                netlist.has_node(original_node->inputs[i])->outputs[0].begin(),
                sub_netlist->inputs[i]->outputs[0].begin(), sub_netlist->inputs[i]->outputs[0].end());
        sub_netlist->rename(sub_netlist->inputs[i], original_node->inputs[i]);
    }

    // update original node
    sub_netlist->rename(sub_netlist->outputs[0], original_node->name);
    sub_netlist->outputs[0]->num_fanout = original_node->num_fanout;
    sub_netlist->outputs[0]->outputs = original_node->outputs;
    netlist.add_node(sub_netlist->outputs[0]);

    // add new internal edges
    for (auto &edge: sub_netlist->edges) {
        netlist.edges.emplace_back(edge);
    }
}

void substitute_node(std::map<std::string, bool> &name_count,
                     std::map<std::pair<std::string, std::string>, NET::Netlist *> &optimal_library,
                     NET::Netlist &netlist, NET::Node *original_node, const std::string &truth_table,
                     int num_stratifications) {
    // std::string label = std::to_string(
    //         netlist.has_node(original_node->inputs[0])->signal_probability[0] / (1.0 / num_stratifications));
    // for (int i = 1; i < original_node->inputs.size(); i++) {
    //     label += "+" + std::to_string(
    //             netlist.has_node(original_node->inputs[i])->signal_probability[0] / (1.0 / num_stratifications));
    // }
    std::string label = "5+5+5+5";
    if (optimal_library[std::make_pair(truth_table, label)] == nullptr) {
        //std::cout << truth_table << "?\n";
        return;
    }

    NET::Netlist *sub_netlist = new NET::Netlist(*optimal_library[std::make_pair(truth_table, label)]);
    // rename and add new internal nodes
    for (auto node: sub_netlist->nodes) {
        if (std::find(sub_netlist->inputs.begin(), sub_netlist->inputs.end(), node) == sub_netlist->inputs.end() &&
            std::find(sub_netlist->outputs.begin(), sub_netlist->outputs.end(), node) == sub_netlist->outputs.end()) {
            std::string new_name = "n_" + std::to_string(netlist.nodes.size());
            if (name_count[new_name])
                new_name = "new_" + new_name;
            sub_netlist->rename(node, new_name);
            name_count[new_name] = true;
            netlist.add_node(node);
        }
    }

    // delete original node from outputs of its inputs
    for (auto &input: original_node->inputs) {
        netlist.has_node(input)->outputs[0].erase(
                std::find(netlist.has_node(input)->outputs[0].begin(), netlist.has_node(input)->outputs[0].end(),
                          original_node->name));
    }

    // add inputs of sub-netlist to outputs of inputs of original node; update input information to sub netlists
    assert(original_node->inputs.size() == sub_netlist->inputs.size());
    for (int i = 0; i < sub_netlist->inputs.size(); i++) {
        netlist.has_node(original_node->inputs[i])->outputs[0].insert(
                netlist.has_node(original_node->inputs[i])->outputs[0].begin(),
                sub_netlist->inputs[i]->outputs[0].begin(), sub_netlist->inputs[i]->outputs[0].end());
        sub_netlist->rename(sub_netlist->inputs[i], original_node->inputs[i]);
    }

    // update original node
    sub_netlist->rename(sub_netlist->outputs[0], original_node->name);
    sub_netlist->outputs[0]->num_fanout = original_node->num_fanout;
    sub_netlist->outputs[0]->outputs = original_node->outputs;
    netlist.add_node(sub_netlist->outputs[0]);

    // add new internal edges
    for (auto &edge: sub_netlist->edges) {
        netlist.edges.emplace_back(edge);
    }
}

void negate(std::string &tt) {
    for (auto &ch: tt) {
        if (ch == '0') ch = 'f';
        else if (ch == '1') ch = 'e';
        else if (ch == '2') ch = 'd';
        else if (ch == '3') ch = 'c';
        else if (ch == '4') ch = 'b';
        else if (ch == '5') ch = 'a';
        else if (ch == '6') ch = '9';
        else if (ch == '7') ch = '8';
        else if (ch == '8') ch = '7';
        else if (ch == '9') ch = '6';
        else if (ch == 'a') ch = '5';
        else if (ch == 'b') ch = '4';
        else if (ch == 'c') ch = '3';
        else if (ch == 'd') ch = '2';
        else if (ch == 'e') ch = '1';
        else if (ch == 'f') ch = '0';
        else
            assert(false);
    }
}

void NET::lut_rewrite(Netlist &netlist, const std::string &library) {
    std::map<std::pair<std::string, std::string>, NET::Netlist *> optimal_library;
    read_netlist_library(library, optimal_library);
    std::cout << "Finish library loading\n";
    std::map<std::string, bool> name_count;
    for (auto &node: netlist.nodes) {
        name_count[node->name] = true;
    }
    //for (auto &node: netlist.nodes) {

    for (int i = 0; i < netlist.nodes.size(); i++) {
        Node *node = netlist.nodes[i];
        //if(node == nullptr)
        //    std::cout<<netlist.nodes[i]->name<<"\n";
        //std::cout<<node->name<<" "<<i<<"\n";
        if (node->functions[0].type == -1 || node->inputs.size() < 4)
            continue;

        std::string truth_table = extract_truth_table(node->functions[0]);
        if (truth_table[0] > '7')
            negate(truth_table);
        substitute_node(name_count, optimal_library, netlist, node, truth_table);
    }
}

// Assert all nodes in netlist is a k lut; Assert each sub-netlist in library is a k lut
void NET::lut_rewrite_power(Netlist &netlist, const std::string &library) {
    std::map<std::pair<std::string, std::string>, NET::Netlist *> optimal_library;
    read_netlist_library(library, optimal_library);

    std::cout << "Finish library loading\n";
    initialize_signal_probability(netlist);
    std::cout << "Finish signal probability initialization\n";
    std::map<std::string, bool> name_count;
    for (auto &node: netlist.nodes) {
        name_count[node->name] = true;
    }

    for (int i = 0; i < netlist.nodes.size(); i++) {
        Node *node = netlist.nodes[i];
        if (node->functions[0].type == -1 || node->inputs.size() < 4)
            continue;

        std::string truth_table = extract_truth_table(node->functions[0]);
        if(truth_table[0] > '7')
           negate(truth_table);
        substitute_node(name_count, optimal_library, netlist, node, truth_table, 20);
    }
}
//
// Created by zephyr on 2022/4/14.
//
#include "netlist.h"

double net_range(PASyn::Netlist &netlist, PASyn::Node *node) {
    int range = 1;
    for (auto &output: node->outputs[0]) {
        range = netlist.has_node(output)->max_depth - node->max_depth <= range ? range :
                netlist.has_node(output)->max_depth - node->max_depth;
    }
    return range;
}

double mutual_contraction(PASyn::Netlist &netlist, PASyn::Node *node) {
    return 0;
}

double ispl(PASyn::Netlist &netlist, PASyn::Node &node) {
    return 0;
}

double PASyn::wire_length(Netlist &netlist, Node *node) {
    if (node->outputs.size() == 2)
        return mutual_contraction(netlist, node);
    else
        return net_range(netlist, node);
}
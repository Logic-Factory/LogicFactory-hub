//
// Created by zephyr on 2021/11/12.
//

#ifndef NETLIST_NETLIST_H
#define NETLIST_NETLIST_H

#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <regex>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cassert>
#include <cmath>
#include <climits>

namespace NET {
    static const std::map<std::string, int> FunctionType = {
            {"",           0},
            {"1",          1},
            {"0 0",        2},
            {"1 1",        2},
            {"0 1",        3},
            {"1 0",        3},
            {"!",          3},
            {"00 0",       4},
            {"+",          4},
            {"00 1",       5},
            {"&!!",        5},
            {"!+",         5},
            {"01 0",       6},
            {"+!",         6},
            {"10 0",       6},
            {"01 1",       7},
            {"&!",         7},
            {"10 1",       7},
            {"11 0",       8},
            {"!&",         8},
            {"+!!",        8},
            {"11 1",       9},
            {"&",          9},
            {"00 0\n01 0", 12},
            {"10 1\n11 1", 12},
            {"01 0\n00 0", 12},
            {"11 1\n10 1", 12},
            {"00 0\n10 0", 13},
            {"01 1\n11 1", 13},
            {"10 0\n00 0", 13},
            {"11 1\n01 1", 13},
            {"00 0\n11 0", 14},
            {"01 1\n10 1", 14},
            {"11 0\n00 0", 14},
            {"^",          14},
            {"^!!",        14},
            {"10 1\n01 1", 14},
            {"01 0\n10 0", 15},
            {"^!",         15},
            {"!^",         15},
            {"00 1\n11 1", 15},
            {"10 0\n01 0", 15},
            {"11 1\n00 1", 15},
            {"01 0\n11 0", 16},
            {"00 1\n10 1", 16},
            {"11 0\n01 0", 16},
            {"10 1\n00 1", 16},
            {"00 1\n01 1", 17},
            {"10 0\n11 0", 17},
            {"01 1\n00 1", 17},
            {"11 0\n10 0", 17}
    };


    class Function {
    public:
        Function(int _num_input, const std::string &_function); // For blif reader
        Function(int type);

        Function() : num_input(0), type(-1) {};
        unsigned int num_input;
        std::vector<std::pair<std::vector<int>, bool>> function;
        // For AIG only
        int type{};
    };

    class Node {
    public:
        explicit Node(std::string _name) : name(std::move(_name)), cell_type("not_mapped"), num_fanin(0), min_depth(1),
                                           num_fanout(std::vector<unsigned int>(1, 0)),
                                           max_depth(1) {
            signal_probability.emplace_back(-1);
        }

        explicit Node(std::string _name, int _num_fanin, std::vector<unsigned int> _num_fanout,
                      std::vector<std::string> _inputs,
                      std::vector<Function> _functions, std::vector<double> _signal_probability,
                      unsigned int _min_depth = 1, unsigned int _max_depth = 1)
                : name(std::move(_name)), num_fanin(_num_fanin), min_depth(_min_depth), max_depth(_max_depth),
                  num_fanout(std::move(_num_fanout)), inputs(std::move(_inputs)), functions(std::move(_functions)),
                  signal_probability(std::move(_signal_probability)) {
            outputs.emplace_back(std::vector<std::string>());
        }

        Node(const Node &) = default;

        std::string name;
        std::string cell_type;
        std::vector<std::string> inputs;
        std::vector<std::vector<std::string>> outputs;
        unsigned int num_fanin;
        unsigned int min_depth, max_depth;
        std::vector<unsigned int> num_fanout;
        std::vector<Function> functions;
        std::vector<double> signal_probability;
        double area{}, area_flow{}, fin{};

        void update_function(std::vector<Function> &_function);
    };

    class Edge {
    public:
        Edge(Node *_source, Node *_drain) : source(_source), drain(_drain) {}

        Node *source;
        Node *drain;
    };

    class Netlist {
    public:
        ~Netlist();

        Netlist(const Netlist &netlist);

        Netlist() = default;

        std::string name;
        std::vector<Node *> nodes;
        std::vector<Edge *> edges;
        std::vector<Node *> outputs;
        std::vector<Node *> inputs;

        void add_node(Node *node);

        // If no such node in netlist, return nullptr otherwise its pointer
        Node *has_node(Node *node);

        Node *has_node(const std::string &node);

        Edge *has_edge(Node *source, Node *drain);

        void rename(Node *node, std::string new_name);

        void clear();   // clear redundant node inputs and edges
    };

    void read_blif(const std::string &file, Netlist &netlist);

    void write_blif(const std::string &file, Netlist &netlist);

    void write_verilog(const std::string &file, Netlist &netlist, bool mapped = true);

    void read_netlist_library(const std::string &library, std::map<std::pair<std::string, std::string>, Netlist *> &);

    void lut_rewrite_power(Netlist &netlist, const std::string &library);

    void lut_rewrite(Netlist &netlist, const std::string &library);
}

#endif //NETLIST_NETLIST_H

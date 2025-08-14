//
// Created by zephyr on 2021/11/12.
//

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

namespace PASyn {
    static const std::map<std::string, int> FunctionType = {
            {"",            0},
            {"1",           1},
            {"0 0",         2},
            {"1 1",         2},
            {"0 1",         3},
            {"1 0",         3},
            {"!",           3},
            {"00 0",        4},
            {"+",           4},
            {"00 1",        5},
            {"&!!",         5},
            {"!+",          5},
            {"01 0",        6},
            {"+!",          6},
            {"10 0",        6},
            {"01 1",        7},
            {"&!",          7},
            {"10 1",        7},
            {"11 0",        8},
            {"!&",          8},
            {"+!!",         8},
            {"11 1",        9},
            {"&",           9},
            {"00 0\n01 0",  12},
            {"10 1\n 11 1", 12},
            {"01 0\n00 0",  12},
            {"11 1\n 10 1", 12},
            {"00 0\n10 0",  13},
            {"01 1\n 11 1", 13},
            {"10 0\n00 0",  13},
            {"11 1\n 01 1", 13},
            {"00 0\n11 0",  14},
            {"01 1\n 10 1", 14},
            {"11 0\n00 0",  14},
            {"^",           14},
            {"^!!",         14},
            {"10 1\n 01 1", 14},
            {"01 0\n10 0",  15},
            {"^!",          15},
            {"!^",          15},
            {"00 1\n 11 1", 15},
            {"10 0\n01 0",  15},
            {"11 1\n 00 1", 15},
            {"01 0\n11 0",  16},
            {"00 1\n 10 1", 16},
            {"11 0\n01 0",  16},
            {"10 1\n 00 1", 16},
            {"00 1\n01 1",  17},
            {"10 0\n 11 0", 17},
            {"01 1\n00 1",  17},
            {"11 0\n 10 0", 17}
    };

    class LookUpTable {
    public:
        std::vector<double> index_1;
        std::vector<double> index_2;
        std::vector<std::vector<double>> values;
    };

    class Timing_or_Power {
    public:
        std::map<std::string, LookUpTable> look_up_tables;
    };

    class Cell_Output {
    public:
        Cell_Output() : capacitance(0), rise_capacitance(0), fall_capacitance(0), max_capacitance(0) {};

        Cell_Output(std::string _name, double _capacitance, double _rise_capacitance, double _fall_capacitance,
                    double _max_capacitance) : name(std::move(
                _name)), capacitance(_capacitance), rise_capacitance(_rise_capacitance),
                                               fall_capacitance(_fall_capacitance),
                                               max_capacitance(_max_capacitance) {};

        std::string name;
        double capacitance;
        double rise_capacitance;
        double fall_capacitance;
        double max_capacitance;
        std::map<std::string, Timing_or_Power> timing;
        std::map<std::string, Timing_or_Power> internal_power;
    };

    class Cell_Input {
    public:
        Cell_Input() : capacitance(0), rise_capacitance(0), fall_capacitance(0) {};

        Cell_Input(std::string _name, double _capacitance, double _rise_capacitance, double _fall_capacitance) : name(
                std::move(
                        _name)), capacitance(_capacitance), rise_capacitance(_rise_capacitance), fall_capacitance(
                _fall_capacitance) {};

        std::string name;
        double capacitance;
        double rise_capacitance;
        double fall_capacitance;

        bool operator<(const Cell_Input &a) const {
            return this->name < a.name;
        }
    };

    class Function {
    public:
        Function(int _num_input, const std::string &_function); // For blif reader
        Function(const std::vector<Cell_Input> &inputs, std::string _function_str); // For liberty reader
        Function() : num_input(0), type(-1) {};
        unsigned int num_input;
        std::vector<std::pair<std::vector<int>, bool>> function;
        // For AIG only
        int type{};
    };

    class TruthTable {

        // str[i] is the value of ith permutation of inputs
        // str[5] is the value of input[n*0, 1, 0, 1]
    public:
        std::string str;

        explicit TruthTable(int _num_bits = 2) : num_bits(_num_bits) {};

        explicit TruthTable(Function &function);

        explicit TruthTable(const std::string &function);

        //bool operator==(TruthTable& truth_table) const;
        std::pair<bool, std::pair<int, int>> equal(TruthTable &truth_table) const;

        void generate_input_2(TruthTable *in1, TruthTable *in2, const std::set<std::string> &in1_inputs,
                              const std::set<std::string> &in2_inputs, const std::set<std::string> &new_inputs, int op);

        void generate_input_1(TruthTable *, int op);

        bool operator<(const TruthTable &other) const;

        unsigned int num_bits;
    };

    class Cut {
    public:
        std::set<std::string> input_nodes;
        std::string name;
        unsigned int min_depth{};
        double fin{};
        double area_flow{}, area{};
        double power{};
        double sad, oisa, iad; // for power analysis
        //TruthTable str;
        Cut() {};

        Cut(std::set<std::string> _input_nodes, std::string _name, unsigned int _min_depth, double _area, double _fin,
            double _area_flow, double _sad, double _oisa, double _iad) : input_nodes(std::move(_input_nodes)),
                                                                         name(std::move(_name)), min_depth(_min_depth),
                                                                         area(_area), fin(_fin), area_flow(_area_flow),
                                                                         sad(_iad), oisa(_oisa), iad(_iad) {};

        bool operator<(const Cut &cut) const {
            return min_depth > cut.min_depth || (min_depth == cut.min_depth && area < cut.area)
                   || (min_depth == cut.min_depth && area == cut.area && area_flow < cut.area_flow);
        }
    };

    class Node {
    public:
        explicit Node(std::string _name) : name(std::move(_name)), cell_type("not_mapped"), num_fanin(0), min_depth(1),
                                           num_fanout(std::vector<unsigned int>(1, 0)),
                                           max_depth(1), load_capacitance(0), fall_delay(0), fall_transition(0),
                                           rise_delay(0), rise_transition(0), glitch_0(0), glitch_1(0),
                                           num_inverters(0) {}

        explicit Node(std::string _name, int _num_fanin, std::vector<unsigned int> _num_fanout, std::vector<std::string> _inputs,
                      std::vector<Function> _functions, std::vector<double> _probability_1,
                      std::string _cell_type = "not_mapped", unsigned int _min_depth = 1, unsigned int _max_depth = 1)
                : name(std::move(_name)), num_fanin(_num_fanin), min_depth(_min_depth), max_depth(_max_depth),
                  num_fanout(std::move(_num_fanout)), inputs(std::move(_inputs)), functions(std::move(_functions)),
                  probability_1(std::move(_probability_1)), cell_type(std::move(_cell_type)), load_capacitance(0),
                  fall_delay(0), fall_transition(0), rise_delay(0), rise_transition(0), glitch_0(0), glitch_1(0),
                  num_inverters(0) {
            outputs.emplace_back(std::vector<std::string>());
        }

        std::string name;
        std::string cell_type;
        std::vector<std::string> inputs;
        std::vector<std::vector<std::string>> outputs;
        unsigned int num_fanin;
        unsigned int min_depth, max_depth;
        std::vector<unsigned int> num_fanout;
        std::vector<double> probability_1;
        std::vector<Function> functions;
        double load_capacitance, fall_transition, rise_transition, rise_delay, fall_delay;
        double glitch_1, glitch_0;
        double output_time{};
        double area{}, area_flow{}, fin{};
        int num_inverters;

        std::set<std::set<std::string> > cuts[7];  //K cuts, set<string> is a cut, cut[i] is the number of cuts with i inputs
        std::set<std::string> best_cut_inputs; //represent cut
        Cut best_cut;           // First Cut (= best_cut_inputs), the best cut in the priority cut set

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

        std::string name;
        std::vector<Node *> nodes;
        std::vector<Edge *> edges;
        std::vector<Node *> outputs;
        std::vector<Node *> inputs;
        double delay;

        void add_node(Node *node);

        // If no such node in netlist, return nullptr otherwise its pointer
        Node *has_node(Node *node);

        Node *has_node(const std::string &node);

        Edge *has_edge(Node *source, Node *drain);

        void clear();   // clear redundant node inputs and edges

        void add_inverter(std::pair<int, int>, std::string node);

        void delete_inverter(std::string node);

        //add or delete inverter created by npn matching, only used in technology mapping
        std::vector<Node *> tmp_inverters;
        std::vector<Edge *> tmp_edges;
        //designed for npn matching created inverters
    };

    class Cell {
    public:
        Cell(std::string _name, double _area, double _leakage, const std::vector<Cell_Input> &_inputs,
             std::vector<Cell_Output> _outputs, const std::vector<std::string> &_functions,
             double _ave_delay, double _ave_internal) : name(std::move(_name)), area(_area), leakage(_leakage),
                                                        inputs(_inputs), outputs(std::move(_outputs)),
                                                        ave_delay(_ave_delay), ave_internal(_ave_internal) {
            for (auto &_function: _functions)
                functions.emplace_back(Function(_inputs, _function));
        }


        std::string name;
        double area;
        double leakage;
        double ave_delay, ave_internal;
        std::vector<Cell_Input> inputs;
        // Inputs should and will be in dictionary order
        std::vector<Cell_Output> outputs;
        std::vector<Function> functions;

        // Different from PLA format
        // Each entry in the map is an indeterminate
        // In vector k represent variable pi^k or (1-pi)^k exist in the indeterminate where 1<=i+1<num_inputs
        // In the order of p0, 1-p0, p1, 1-p1, ..., pn, 1-pn
        // The second integer is the coefficient of this indeterminate
        // glitch*[i][j] is the propagation for ith output and jth input
        std::vector<std::vector<std::map<std::vector<int>, int>>> glitch_11_propagate, glitch_10_propagate, glitch_01_propagate, glitch_00_propagate;
    };

    class Technology {
    public:
        std::map<std::string, Cell *> cells;
        double working_voltage;
    };

    // Only get the necessary information like function, power and area
    void read_liberty(const std::string &file, Technology &);

    void read_blif(const std::string &file, Netlist &netlist, Technology *technology = nullptr);

    void write_blif(const std::string &file, Netlist &netlist);

    void write_verilog(const std::string &file, Netlist &netlist, Technology &technology, bool mapped = true);

    void calculate_probability_1(Netlist &netlist);

    // Calculate timing of each node and get glitch at the same time
    void calculate_timing(Netlist &netlist, Technology &technology);

    //std::pair<double, double> calculate_power(Netlist &netlist, Technology &technology);
    std::vector<double> calculate_power(Netlist &netlist, Technology &technology);

    std::vector<double> calculate_power_api(std::string &netlist, std::string &technology, bool gym_using);

    std::vector<double> get_feature(const std::string &file);

    std::vector<double> get_feature_basic(const std::string &file);

    std::vector<double> get_feature_glitch(const std::string &file);

    double
    interpolate(std::vector<double> &x_axis, std::vector<double> &y_axis, std::vector<std::vector<double>> values,
                double x, double y);

    void switch_pre_process(Technology &technology);

    double wire_length(Netlist &netlist, Node *node);

    std::set<std::pair<std::string, std::pair<int, int>>>
    npn(const std::string &str, bool negate_input = false, bool negate_output = false);

    std::vector<std::string> check_equivalence(TruthTable *truth_table,
                                               std::map<PASyn::TruthTable, std::vector<std::string>> &technology_truth_tables);

    //return the standard cell name having same truth_table as cut
    //return "None" if no standard cell satisfies
    std::pair<std::vector<std::string>, std::pair<int, int>>
    check_equivalence(TruthTable *truth_table, std::map<TruthTable, std::vector<std::string>> &technology_truth_tables,
                      bool npn);

    void technology_mapping(Netlist &netlist, PASyn::Technology &technology);

    void technology_mapping_api(const std::string &input, const std::string &technology_input, const std::string &output);

    std::vector<int> int_to_bvector(int n, unsigned int fix_length = 0);

    int bvector_to_int(const std::vector<int> &b_vector);

    std::vector<std::string> split(const std::string &str, char terminal = ' ');
    std::string filter_string(const std::string &str, std::vector<char> dic);
    std::string infix_to_prefix(std::string infix_exp);
}


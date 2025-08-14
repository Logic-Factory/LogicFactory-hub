//
// Created by zephyr on 2022/2/23.
//
#include "netlist.h"
#include <climits>
#include <ctime>

inline void
type_count(std::vector<std::vector<double>> &type_trans, std::vector<double> &type_proportion, PASyn::Node *input,
           PASyn::Node *output) {
    // For AIG only
    if(input->functions[0].type == -1 || input->functions[0].type == 0 || input->functions[0].type == 1)
        return;
    type_proportion[input->functions[0].type - 2]++;
    type_trans[input->functions[0].type - 2][output->functions[0].type - 2]++;
}

inline void
type_count_basic(std::vector<double> &type_proportion, PASyn::Node *input,
           PASyn::Node *output) {
    // For AIG only
    if(input->functions[0].type == -1 || input->functions[0].type == 0 || input->functions[0].type == 1)
        return;
    type_proportion[input->functions[0].type - 2]++;
}

inline void
type_count_glitch(std::vector<std::vector<double>> &type_trans, std::vector<double> &type_proportion, PASyn::Node *input,
           PASyn::Node *output, std::vector<double> &type_glitch) {
    // For AIG only
    if(input->functions[0].type == -1 || input->functions[0].type == 0 || input->functions[0].type == 1)
        return;
    type_proportion[input->functions[0].type - 2]++;
    type_trans[input->functions[0].type - 2][output->functions[0].type - 2]++;
    type_glitch[input->functions[0].type - 2] += input->max_depth - input->min_depth;
}

// Will do type count at the same time
void
cal_depth(PASyn::Netlist &netlist, std::vector<std::vector<double>> &type_trans, std::vector<double> &type_proportion) {
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
        queue.pop();
        for (auto &output_name: node->outputs[0]) {
            // NOTE:For AIG only
            PASyn::Node *output = netlist.has_node(output_name);
            type_count(type_trans, type_proportion, node, output);
            output->max_depth = output->max_depth <= node->max_depth ? node->max_depth + 1 : output->max_depth;
            if (output->min_depth == 1)
                output->min_depth = node->min_depth + 1;
            else
                output->min_depth = output->min_depth >= node->min_depth ? node->min_depth + 1 : output->min_depth;
            topology_count[output->name]--;
            if (topology_count[output->name] == 0)
                queue.emplace(output);
        }
    }
}

// Will do type count at the same time
void
cal_depth_basic(PASyn::Netlist &netlist, std::vector<double> &type_proportion) {
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
        queue.pop();
        for (auto &output_name: node->outputs[0]) {
            // NOTE:For AIG only
            PASyn::Node *output = netlist.has_node(output_name);
            type_count_basic(type_proportion, node, output);
            output->max_depth = output->max_depth <= node->max_depth ? node->max_depth + 1 : output->max_depth;
            topology_count[output->name]--;
            if (topology_count[output->name] == 0)
                queue.emplace(output);
        }
    }
}

// Will do type count at the same time
void
cal_depth_glitch(PASyn::Netlist &netlist, std::vector<std::vector<double>> &type_trans, std::vector<double> &type_proportion,
                 std::vector<double> &type_glitch) {
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
        queue.pop();
        for (auto &output_name: node->outputs[0]) {
            // NOTE:For AIG only
            PASyn::Node *output = netlist.has_node(output_name);
            type_count_glitch(type_trans, type_proportion, node, output, type_glitch);
            output->max_depth = output->max_depth <= node->max_depth ? node->max_depth + 1 : output->max_depth;
            if (output->min_depth == 1)
                output->min_depth = node->min_depth + 1;
            else
                output->min_depth = output->min_depth >= node->min_depth ? node->min_depth + 1 : output->min_depth;
            topology_count[output->name]--;
            if (topology_count[output->name] == 0)
                queue.emplace(output);
        }
    }
}

// The size of feature vector is 9+8+8*8 = 81
std::vector<double> PASyn::get_feature(const std::string &filename) {
    clock_t t1, t2;
    std::vector<double> feature;
    std::vector<std::vector<double>> type_trans{0};
    std::vector<double> type_proportion;
    type_trans.reserve(8);
    type_trans.resize(8);
    type_proportion.reserve(8);
    type_proportion.resize(8);
    for (auto &entry: type_trans) {
        entry.reserve(8);
        entry.resize(8);
    }
    PASyn::Netlist netlist;
    t1=clock();
    PASyn::read_blif(filename, netlist);
    t2=clock();
    std::cout<<"read_blif time is:"<<double(t2-t1)/CLOCKS_PER_SEC*1000<<"ms"<<std::endl;

    t1=clock();
    cal_depth(netlist, type_trans, type_proportion);

    int max_depth_max = INT_MIN, max_depth_min = INT_MAX, min_depth_max = INT_MIN, min_depth_min = INT_MAX;
    double max_depth_avg = 0, min_depth_avg = 0;
    for(auto& output: netlist.outputs) {
        max_depth_max = max_depth_max < output->max_depth ? output->max_depth : max_depth_max;
        max_depth_min = max_depth_min > output->max_depth ? output->max_depth : max_depth_min;
        max_depth_avg += output->max_depth;
        min_depth_max = min_depth_max < output->min_depth ? output->min_depth : min_depth_max;
        min_depth_min = min_depth_min > output->min_depth ? output->min_depth : min_depth_min;
        min_depth_avg += output->min_depth;
    }
    max_depth_avg /= double(netlist.outputs.size());
    min_depth_avg /= double(netlist.outputs.size());

    feature.emplace_back(netlist.inputs.size());
    feature.emplace_back(netlist.outputs.size());
    feature.emplace_back(netlist.nodes.size());
    feature.emplace_back(max_depth_min);
    feature.emplace_back(max_depth_max);
    feature.emplace_back(max_depth_avg);
    feature.emplace_back(min_depth_min);
    feature.emplace_back(min_depth_max);
    feature.emplace_back(min_depth_avg);

    for(double & entry : type_proportion)
        entry /= double(netlist.nodes.size());
    for(auto& entry: type_trans) {
        double total_out = 0;
        for(double & output_num : entry)
            total_out += output_num;
        for(double & output_portion : entry) {
            if(total_out == 0)
                continue;
            output_portion /= total_out;
        }
    }

    feature.insert(feature.end(), type_proportion.begin(), type_proportion.end());
    for(auto& entry: type_trans) {
        feature.insert(feature.end(), entry.begin(), entry.end());
    }
    t2=clock();
    std::cout<<"feature time is:"<<double(t2-t1)/CLOCKS_PER_SEC*1000<<"ms"<<std::endl;

    return feature;
}

// The size of feature vector is 6+8 = 14
std::vector<double> PASyn::get_feature_basic(const std::string &filename) {
    std::vector<double> feature;
    std::vector<double> type_proportion;
    type_proportion.reserve(8);
    type_proportion.resize(8);
    PASyn::Netlist netlist;
    PASyn::read_blif(filename, netlist);
    cal_depth_basic(netlist, type_proportion);

    int max_depth_max = INT_MIN, max_depth_min = INT_MAX, min_depth_max = INT_MIN, min_depth_min = INT_MAX;
    double max_depth_avg = 0, min_depth_avg = 0;
    for(auto& output: netlist.outputs) {
        max_depth_max = max_depth_max < output->max_depth ? output->max_depth : max_depth_max;
        max_depth_min = max_depth_min > output->max_depth ? output->max_depth : max_depth_min;
        max_depth_avg += output->max_depth;
    }
    max_depth_avg /= double(netlist.outputs.size());

    feature.emplace_back(netlist.inputs.size());
    feature.emplace_back(netlist.outputs.size());
    feature.emplace_back(netlist.nodes.size());
    feature.emplace_back(max_depth_min);
    feature.emplace_back(max_depth_max);
    feature.emplace_back(max_depth_avg);

    for(double & entry : type_proportion)
        entry /= double(netlist.nodes.size());

    feature.insert(feature.end(), type_proportion.begin(), type_proportion.end());

    return feature;
}

// The size of feature vector is 9+8+8+8*8 = 89
std::vector<double> PASyn::get_feature_glitch(const std::string &filename) {
    std::vector<double> feature;
    std::vector<std::vector<double>> type_trans{0};
    std::vector<double> type_proportion;
    std::vector<double> type_glitch;
    type_trans.reserve(8);
    type_trans.resize(8);
    type_proportion.reserve(8);
    type_proportion.resize(8);
    type_glitch.reserve(8);
    type_glitch.resize(8);
    for (auto &entry: type_trans) {
        entry.reserve(8);
        entry.resize(8);
    }
    PASyn::Netlist netlist;
    PASyn::read_blif(filename, netlist);
    cal_depth_glitch(netlist, type_trans, type_proportion, type_glitch);

    int max_depth_max = INT_MIN, max_depth_min = INT_MAX, min_depth_max = INT_MIN, min_depth_min = INT_MAX;
    double max_depth_avg = 0, min_depth_avg = 0;
    for(auto& output: netlist.outputs) {
        max_depth_max = max_depth_max < output->max_depth ? output->max_depth : max_depth_max;
        max_depth_min = max_depth_min > output->max_depth ? output->max_depth : max_depth_min;
        max_depth_avg += output->max_depth;
        min_depth_max = min_depth_max < output->min_depth ? output->min_depth : min_depth_max;
        min_depth_min = min_depth_min > output->min_depth ? output->min_depth : min_depth_min;
        min_depth_avg += output->min_depth;
    }
    max_depth_avg /= double(netlist.outputs.size());
    min_depth_avg /= double(netlist.outputs.size());

    feature.emplace_back(netlist.inputs.size());
    feature.emplace_back(netlist.outputs.size());
    feature.emplace_back(netlist.nodes.size());
    feature.emplace_back(max_depth_min);
    feature.emplace_back(max_depth_max);
    feature.emplace_back(max_depth_avg);
    feature.emplace_back(min_depth_min);
    feature.emplace_back(min_depth_max);
    feature.emplace_back(min_depth_avg);

    for(int i=0; i<type_glitch.size(); i++) {
        if (type_proportion[i] == 0)
            assert(type_glitch[i] == 0);
        else
            type_glitch[i] /= type_proportion[i];
    }
    for(double & entry : type_proportion)
        entry /= double(netlist.nodes.size());
    for(auto& entry: type_trans) {
        double total_out = 0;
        for(double & output_num : entry)
            total_out += output_num;
        for(double & output_portion : entry) {
            if(total_out == 0)
                continue;
            output_portion /= total_out;
        }
    }

    feature.insert(feature.end(), type_proportion.begin(), type_proportion.end());
    feature.insert(feature.end(), type_glitch.begin(), type_glitch.end());
    for(auto& entry: type_trans) {
        feature.insert(feature.end(), entry.begin(), entry.end());
    }

    return feature;
}
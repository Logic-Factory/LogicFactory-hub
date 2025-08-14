//
// Created by zephyr on 2023/7/6.
//
#include "../exact_synthesis/exact.h"
#include "../utility/utility.h"

#ifndef EXACT_SYNTHESIS_POWER_H
#define EXACT_SYNTHESIS_POWER_H
namespace exact {

    class SSV_Power : public SSV {
    public:
        double target_switching_probability{};
        int num_classes{};
        SSV_Power(const std::vector<std::string> &functions);
        SSV_Power(const std::vector<Boolean> &functions);
        Encoding encode(bool mark_variable, std::vector<double>, bool average);
        std::map<std::string, int> generate_variable_index(int n, int r, int max_t, int m);
    };

    void generate_netlist_library_power(std::string const &, int num_inputs, int num_classes, bool average, int start_index, int partition_size);

    void generate_netlist_library_power_new(std::string const &, std::string const &, int num_inputs, int num_classes, bool average, int start_index, int partition_size);

    std::pair<bool, std::vector<int>> power_synthesis(exact::SSV_Power*, const std::string&, std::ostream& out, std::vector<double>, bool average = true);
}
#endif //EXACT_SYNTHESIS_POWER_H

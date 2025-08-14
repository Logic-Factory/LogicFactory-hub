//
// Created by zephyr on 2023/2/18.
//
#include <utility>
#include "exact.h"

exact::Encoding exact::Encoder::encode() {
    std::cerr << "Not Implemented Error";
    assert(false);
}

void exact::Encoder::add_non_trivial(std::map<std::string, int> &variable_index, Encoding &result, int n) {
    std::cerr << "Not Implemented Error";
    assert(false);
}

void exact::Encoder::add_all_steps(std::map<std::string, int> &variable_index, Encoding &result, int n) {
    std::cerr << "Not Implemented Error";
    assert(false);
}

void exact::Encoder::add_no_replication(std::map<std::string, int> &variable_index, Encoding &result, int n) {
    std::cerr << "Not Implemented Error";
    assert(false);
}

void exact::Encoder::add_lexicographical_step(std::map<std::string, int> &variable_index, Encoding &result, int n) {
    std::cerr << "Not Implemented Error";
    assert(false);
}

void exact::Encoder::add_lexicographical_op(std::map<std::string, int> &variable_index, Encoding &result, int n) {
    std::cerr << "Not Implemented Error";
    assert(false);
}

void exact::Encoder::add_ordered_symmetric(std::map<std::string, int> &variable_index, Encoding &result, int n) {
    std::cerr << "Not Implemented Error";
    assert(false);
}

std::map<std::string, int> exact::Encoder::generate_variable_index(int n, int _r, int max_t, int m) {
    std::cerr << "Not Implemented Error";
    assert(false);
}

exact::Encoder::Encoder(std::vector<Boolean> functions, const Technology &_technology, int _r, bool _non_trivial,
                        bool _all_steps,
                        bool _no_replication, bool _lexicographical_step, bool _lexicographical_op,
                        bool _ordered_symmetric)
        : technology(_technology), r(_r), non_trivial(_non_trivial), all_steps(_all_steps),
          no_replication(_no_replication), lexicographical_step(_lexicographical_step),
          lexicographical_op(_lexicographical_op), ordered_symmetric(_ordered_symmetric) {
    this->functions = std::move(functions);
    int num_inputs = this->functions[0].num_bits;
    pi_tt.emplace_back(std::vector<int>{-1});
    int length = 1 << num_inputs;
    for (int i = 1; i <= num_inputs; i++) {
        std::vector<int> temp;
        int var = 1, toggle = (1 << (num_inputs - i));
        temp.reserve(length);
        for (int j = 0; j < length; j++) {
            if (j % toggle == 0)
                var = var == 1 ? 0 : 1;
            temp.emplace_back(var);
        }
        pi_tt.emplace_back(temp);
    }
    initial_i = this->functions[0].num_bits + 1;
}

exact::Encoder::Encoder(const std::vector<std::string> &functions, const exact::Technology &_technology, int _r,
                        bool _non_trivial,
                        bool _all_steps,
                        bool _no_replication, bool _lexicographical_step, bool _lexicographical_op,
                        bool _ordered_symmetric)
        : technology(_technology), r(_r), non_trivial(_non_trivial), all_steps(_all_steps),
          no_replication(_no_replication), lexicographical_step(_lexicographical_step),
          lexicographical_op(_lexicographical_op), ordered_symmetric(_ordered_symmetric) {
    for (auto &function: functions) {
        this->functions.emplace_back(Boolean(function));
    }
    int num_inputs = this->functions[0].num_bits;
    pi_tt.emplace_back(std::vector<int>{-1});
    int length = 1 << num_inputs;
    for (int i = 1; i <= num_inputs; i++) {
        std::vector<int> temp;
        int var = 1, toggle = (1 << (num_inputs - i));
        temp.reserve(length);
        for (int j = 0; j < length; j++) {
            if (j % toggle == 0)
                var = var == 1 ? 0 : 1;
            temp.emplace_back(var);
        }
        pi_tt.emplace_back(temp);
    }
    initial_i = num_inputs;
}

exact::Encoding exact::Encoder::encode(bool) {
    std::cerr << "Not Implemented Error";
    assert(false);
}

void exact::Encoder::decode(std::vector<int>, std::string output_file) {
    std::cerr << "Not Implemented Error";
    assert(false);
}

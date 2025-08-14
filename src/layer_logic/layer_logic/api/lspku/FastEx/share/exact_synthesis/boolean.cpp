//
// Created by zephyr on 2023/2/18.
//
#include "exact.h"
#include "../utility/utility.h"

exact::Boolean::Boolean(std::string function) {
    this->function_str = function;
    for (auto &ch: function) {
        auto temp = hex_to_binary(ch);
        this->function.insert(this->function.end(), temp.begin(), temp.end());
    }
    this->num_bits = int(log(this->function.size()) / log(2));
}

exact::Boolean::Boolean(std::string name, std::string function) {
    this->name = std::move(name);
    this->function_str = function;
    for (auto &ch: function) {
        auto temp = hex_to_binary(ch);
        this->function.insert(this->function.end(), temp.begin(), temp.end());
    }
    this->num_bits = int(log(this->function.size()) / log(2));
}

void exact::Boolean::print(std::ostream &out) {
    for (auto ch: function) {
        out << (ch ? 1 : 0);
    }
    out << " " << this->num_bits << std::endl;
}

exact::Technology::Technology(const std::vector<std::string> &functions) {
    for (auto &function: functions) {
        gates.emplace_back(Boolean(function));
    }
}

exact::Technology::Technology() = default;

bool exact::is_symmetric(std::vector<exact::Boolean> &functions, int p, int q) {
    std::vector<std::vector<bool>> index_table;
    int max_index = 1 << functions[0].num_bits;
    index_table.reserve(max_index);
    for (int i = 0; i < max_index; i++) {
        index_table.emplace_back(int_to_binary(i, functions[0].num_bits));
        std::vector<bool>::swap(index_table[i][p], index_table[i][q]);
    }
    for (auto &function: functions) {
        for (int i = 0; i < max_index; i++)
            if (function.function[binary_to_int(index_table[i])] != function.function[i])
                return false;
    }
    return true;
}


//
// Created by zephyr on 2023/7/1.
//
#include "incremental.h"
#include <algorithm>
#include <utility>
#include <string>
#include "../utility/utility.h"

inline std::string random_sub(int sub_n) {
    return generate_random_tt(sub_n);
}

inline std::string trunc(const std::string &original, int sub_n) {
    assert(original.size() >= (1 << (sub_n-2)));
    if(original.substr(0, 1 << (sub_n-2)) != std::string(1 << (sub_n-2), '0'))
        return original.substr(0, 1 << (sub_n-2));
    else return original.substr(1 << (sub_n-2));
}

// WARNING: not support multiple mute yet
inline std::string mute(const std::string &original, std::vector<bool>& set_values, std::vector<int>& variable_indices, int sub_n, int num_decomposable = 0, const std::string& random_tt="") {
    std::string new_express;
    for(int i=0; i<original.size(); i++) {
        char ch = original[i];
        if (ch == input_names[variable_indices[0]]) {
            if(original[i-1] == '&') {
                new_express += '1';
            } else if (original[i-1] == '+') {
                new_express += '0';
            } else if (original[i-1] == '!') {
                if(original[i-1] == '&') {
                    new_express += '0';
                } else if (original[i-1] == '+') {
                    new_express += '1';
                } else
                    new_express += '0' + set_values[0];
            } else
            new_express += '0' + set_values[0];
        }
        else if (ch > 'A' + variable_indices[0] && ch < 'Z')
            new_express += ch - 1;
        else
            new_express += ch;
    }
    std::string result = exact::evaluate(new_express, sub_n, num_decomposable, random_tt);
    return binary_to_hex(result);
}

inline std::string mute_last(const std::string &original, std::vector<bool>& set_values, int sub_n, int num_decomposable = 0, const std::string& random_tt="") {
    std::string new_express;
    char mute_ch;
    for(auto& ch : original) {
        if(ch >= 'A' && ch <= 'Z') {
            mute_ch = ch;
            break;
        }
    }

    for(int i=0; i<original.size(); i++) {
        char ch = original[i];
        if (ch == mute_ch) {
            if(original[i-1] == '&') {
                new_express += '1';
            } else if (original[i-1] == '+') {
                new_express += '0';
            } else if (original[i-1] == '!') {
                if(original[i-2] == '&') {
                    new_express += '0';
                } else if (original[i-2] == '+') {
                    new_express += '1';
                } else
                    new_express += '0' + set_values[0];
            } else
                new_express += '0' + set_values[0];
        }
        else if (ch > mute_ch && ch < 'Z')
            new_express += ch - 1;
        else
            new_express += ch;
    }
    std::string result = exact::evaluate(new_express, sub_n, num_decomposable == 0 ? 0 : num_decomposable - 1, random_tt);
    return binary_to_hex(result);
}

std::pair<std::string, int>
exact::similar_sub_func(const std::string &original, const std::string &method, int sub_n, char *option = nullptr, int num_decomposable = 0, const std::string& random_tt = "") {
    if (method == "trunc") // truncate the truth table
        return std::make_pair(trunc(original, sub_n), 1);
    else if (method == "mute") { // set an input variable to 0/1
        int num_vars_mute = std::stoi(std::string(option, option+2));
        std::vector<bool> set_values;
        std::vector<int> var_indices;
        for(int i = 0; i<num_vars_mute; i++) {
            set_values.emplace_back(option[i*3+2] - '0');
            var_indices.emplace_back(std::stoi(std::string(option + num_vars_mute + 2 + (i*2), option + num_vars_mute + 4 + (i*2))));
        }
        std::string original_exp = std::string(option + num_vars_mute*3 + 2);
        return std::make_pair(mute(original, set_values, var_indices, sub_n), var_indices[0]);
        // Option: |number of vars to mute (2-char)|vector<set_value>(1-char per var)|
        // |vector<bit_index>(2-char per var)|original_string|\0|
    } else if (method == "mute_last") {
        int num_vars_mute = std::stoi(std::string(option, option+2));
        std::vector<bool> set_values;
        std::vector<int> var_indices;
        for(int i = 0; i<num_vars_mute; i++) {
            set_values.emplace_back(option[i+2] - '0');
        }
        return std::make_pair(mute_last(std::string(option + num_vars_mute + 2), set_values, sub_n, num_decomposable, random_tt), 1);
        // Option: |number of vars to mute (2-char)|vector<set_value>(1-char per var)|original_string|\0|
    } else if (method == "manual") { // set a similar function manually
        std::string result(option);
        return std::make_pair(result, 1);
    } else if (method == "random") {
        return std::make_pair(random_sub(sub_n), 1);
    }else {
        std::cerr << "Not Implemented\n";
        assert(false);
    }
}

void
deal_set(std::vector<std::string> &dels, std::vector<std::string> &adds, std::set<std::vector<int>> &clause_set_sub,
         std::set<std::vector<int>> &clause_set_cur) {
    std::set<std::vector<int>> del_set, add_set;
    set_difference(clause_set_cur.begin(), clause_set_cur.end(), clause_set_sub.begin(), clause_set_sub.end(),
                   inserter(add_set, add_set.begin()));
    set_difference(clause_set_sub.begin(), clause_set_sub.end(), clause_set_cur.begin(), clause_set_cur.end(),
                   inserter(del_set, del_set.begin()));

    for (auto &clause: del_set) {
        std::string _clause;
        for (auto &variable: clause) {
            _clause += std::to_string(variable) + " ";
        }
        dels.emplace_back(_clause);
    }
    for (auto &clause: add_set) {
        std::string _clause;
        for (auto &variable: clause) {
            _clause += std::to_string(variable) + " ";
        }
        adds.emplace_back(_clause);
    }
}

std::pair<std::vector<std::string>, std::vector<std::string>>
exact::SSV_Incremental::incremental_encode() {
    std::vector<std::string> dels;
    std::vector<std::string> adds;

    exact::Boolean sub_func = exact::Boolean(similar_function);
    SSV sub_ssv = SSV(std::vector<exact::Boolean>{sub_func});
    sub_ssv.r = sub_r;
    sub_ssv.initial_i = functions[0].num_bits + 1;

    std::set<std::vector<int>> clause_set_sub, clause_set_cur;
    auto encoding_sub = sub_ssv.encode(false);
    for (auto &clause: encoding_sub.clauses)
        clause_set_sub.insert(clause);

    /*for (auto &clause: clause_set_sub) {
        for (auto &variable: clause)
            std::cout << variable << " ";
        std::cout << "\n";
    }
    for (auto &variable: encoding_sub.comments)
        std::cout << variable;
    std::cout << "\n";
     */

    auto encoding_cur = encode(true);
    for (auto &clause: encoding_cur.clauses)
        clause_set_cur.insert(clause);

    /*for (auto &clause: clause_set_cur) {
        std::cout << "\n";
        for (auto &variable: clause)
            std::cout << variable << " ";
    }
    for (auto &variable: encoding_cur.comments)
        std::cout << variable;
        */
    deal_set(dels, adds, clause_set_sub, clause_set_cur);
    return std::make_pair(dels, adds);
}

exact::Encoding exact::SSV_Incremental::encode_for_increment(bool mark_variable) {
    int r = this->r, max_t =
            (1 << (functions[0].num_bits)) - 1, m = (int) functions.size(), n = functions[0].num_bits;
    for (auto &function: functions)
        assert(function.num_bits == n);

    std::map<std::string, int> variable_index = generate_variable_index(n, r, m);
    Encoding result = SSV::generate_clauses(variable_index, n, r, max_t, m);
    if (mark_variable) {
        for (auto &entry: variable_index)
            result.add_comment("c " + entry.first + " " + std::to_string(entry.second) + "\n");
    }
    assert(result.check());
    return result;
}

std::map<std::string, int>
exact::SSV_Incremental::generate_variable_index(int n, int r, int m) {
    int max_t = (1 << n) - 1, sub_max_t = (1 << sub_n) - 1;
    std::map<std::string, int> variable_index = SSV::generate_variable_index(sub_n, sub_r, sub_max_t, m);
    int index = int(variable_index.size());
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int t = 1; t <= max_t; t++)
            variable_index["x" + std::to_string(i) + std::to_string(t)] == 0 ? variable_index["x" + std::to_string(i) +
                                                                                              std::to_string(
                                                                                                      t)] = index++ : 0;
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int h = 1; h <= m; h++)
            variable_index["g" + std::to_string(i) + std::to_string(h)] == 0 ? variable_index["g" + std::to_string(i) +
                                                                                              std::to_string(
                                                                                                      h)] = index++ : 0;
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int k = 1; k < i; k++)
            for (int j = 1; j < k; j++)
                variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)] == 0 ? variable_index[
                                                                                                               "s" +
                                                                                                               std::to_string(
                                                                                                                       i) +
                                                                                                               std::to_string(
                                                                                                                       j) +
                                                                                                               std::to_string(
                                                                                                                       k)] = index++
                                                                                                     : 0;
    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        if (variable_index["f" + std::to_string(i) + "11"] == 0) {
            variable_index["f" + std::to_string(i) + "11"] = index++;
            variable_index["f" + std::to_string(i) + "10"] = index++;
            variable_index["f" + std::to_string(i) + "01"] = index++;
        }
    }
    return variable_index;
}

std::pair<exact::Encoding, std::vector<int>>
exact::SSV_Incremental::incremental_encode(bool mark_variable) {
    int m = (int) functions.size(), n = functions[0].num_bits, max_t = (1 << n) - 1;
    int num_used_sub_nodes = 1;
    initial_i += num_used_sub_nodes;
    std::map<std::string, int> variable_index = SSV::generate_variable_index(n, r, max_t, m);
    initial_i -= num_used_sub_nodes;

    std::string similar_func = similar_function;
    // NOTE: Index representing sub-circuit if n+1
    // Variables f/g/x/_(n+1)_... and s_...(n+1) is removed
    std::vector<int> sub_circuit_related_variables;
    int index = variable_index.size() + 1;
    for (unsigned int i = initial_i + 1; i < initial_i + r + 1; i++) {
        for (int k = 1; k < i; k++) {
            if (k > n && k < initial_i) continue;
            for (int j = 1; j < k; j++) {
                if (j > n && j < initial_i) continue;
                if (k == n + 1 || j == n + 1) {
                    variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)] = index++;
                    sub_circuit_related_variables.emplace_back(
                            variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)]);
                }
            }
        }
    }
    Encoding result = generate_clauses(variable_index, n, r, max_t, m);

    if (mark_variable) {
        for (auto &entry: variable_index)
            result.add_comment("c " + entry.first + " " + std::to_string(entry.second) + "\n");
    }

    return std::make_pair(result, sub_circuit_related_variables);
}

void exact::SSV_Incremental::set_similar_function(const std::string &similar_method, char *similar_option, int num_decomposable, const std::string& random_tt, int _sub_n) {
    if(_sub_n == -1)
        _sub_n = functions[0].num_bits - 1;
    auto similar_func_zip = similar_sub_func(functions[0].function_str, similar_method, _sub_n, similar_option, num_decomposable, random_tt);
    similar_function = similar_func_zip.first;
    non_sub_variable_index = similar_func_zip.second;
    similar_function_set = true;
}

std::string exact::SSV_Incremental::get_similar_function() {
    assert(similar_function_set);
    return similar_function;
}

exact::SSV_Incremental::SSV_Incremental(std::vector<Boolean> functions, int _sub_r, int _sub_n) : SSV(
        std::move(functions)), sub_r(_sub_r), sub_n(_sub_n), similar_function_set(false) {}

exact::SSV_Incremental::SSV_Incremental(std::vector<Boolean> functions) : SSV(
        std::move(functions)), sub_r(-1), sub_n(-1), similar_function_set(false) {}

std::map<std::string, int> exact::SSV_Incremental::generate_variable_index(int n, int r, int max_t, int m) {
    std::map<std::string, int> variable_index;
    int index = 1;
    for (unsigned int i = initial_i + 1; i < initial_i + r; i++)
        for (int t = 1; t <= max_t; t++)
            variable_index["x" + std::to_string(i) + std::to_string(t)] = index++;
    for (unsigned int i = initial_i + 1; i < initial_i + r; i++)
        for (int h = 1; h <= m; h++)
            variable_index["g" + std::to_string(i) + std::to_string(h)] = index++;
    for (unsigned int i = initial_i + 1; i < initial_i + r; i++) {
        for (int k = 1; k < i; k++) {
            if (k > n + 1 && k < initial_i) continue;
            for (int j = 1; j < k; j++) {
                if (j > n + 1 && j < initial_i) continue;
                variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)] = index++;
            }
        }
    }
    for (unsigned int i = initial_i + 1; i < initial_i + r; i++) {
        variable_index["f" + std::to_string(i) + "11"] = index++;
        variable_index["f" + std::to_string(i) + "10"] = index++;
        variable_index["f" + std::to_string(i) + "01"] = index++;
    }
    //for(auto& entry: variable_index) {
    //    std::cout<< entry.first<<" "<<entry.second<<"\n";
    //}
    return variable_index;
}

exact::Encoding
exact::SSV_Incremental::generate_clauses(std::map<std::string, int> &variable_index, int n, int r, int max_t, int m) {
    Encoding result;

    std::vector<std::vector<int>> pi_tt = Encoder::pi_tt;
    auto sub_func_zip = std::make_pair(similar_function, non_sub_variable_index);
    std::string sub_func_tt = hex_to_binary(sub_func_zip.first);
    int unused_variable = sub_func_zip.second;
    assert(sub_func_tt.size() == pi_tt[1].size() / 2);
    std::vector<int> insert_tt;

    for(int j = 0; j < pi_tt[1].size(); j++) {
        std::vector<int> bvector;
        for (int i=1; i < pi_tt.size(); i++) {
            if (i != unused_variable)
                bvector.emplace_back(pi_tt[i][j]);
        }
        insert_tt.emplace_back(sub_func_tt[bvector_to_int(bvector)] == '0' ? 0 : 1);
    }
    pi_tt.emplace_back(insert_tt);

    for (unsigned int i = initial_i + 1; i < initial_i + r + 1; i++) {
        int fi11 = variable_index["f" + std::to_string(i) + "11"];
        int fi10 = variable_index["f" + std::to_string(i) + "10"];
        int fi01 = variable_index["f" + std::to_string(i) + "01"];
        for (int k = 1; k < i; k++) {
            if (k > n + 1 && k < initial_i) continue;
            for (int j = 1; j < k; j++) {
                if (j > n + 1 && j < initial_i) continue;
                int sijk = variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)];
                for (int t = 1; t <= max_t; t++) {
                    int xit = variable_index["x" + std::to_string(i) + std::to_string(t)];
                    if (j <= n + 1 && k <= n + 1) {
                        int xjt = pi_tt[j][t], xkt = pi_tt[k][t];// 0 xit, -fi01 ^ 0 -xit fi01
                        if (xjt == 0 && xkt == 1) result.add_clause(std::vector<int>{-sijk, xit, -fi01}); //jk->i 01 0
                        if (xjt == 1 && xkt == 0) result.add_clause(std::vector<int>{-sijk, xit, -fi10}); //jk->i 10 0
                        if (xjt == 1 && xkt == 1) result.add_clause(std::vector<int>{-sijk, xit, -fi11}); //jk->i 11 0
                        if (xjt == 0 && xkt == 1) result.add_clause(std::vector<int>{-sijk, -xit, fi01}); //jk->i 01 1
                        if (xjt == 1 && xkt == 0) result.add_clause(std::vector<int>{-sijk, -xit, fi10}); //jk->i 10 1
                        if (xjt == 1 && xkt == 1) result.add_clause(std::vector<int>{-sijk, -xit, fi11}); //jk->i 11 1
                        if (xjt == 0 && xkt == 0) result.add_clause(std::vector<int>{-sijk, -xit}); //avoid 00 1
                        continue;
                    }
                    if (j <= n + 1) {
                        int xjt = pi_tt[j][t], xkt = variable_index["x" + std::to_string(k) + std::to_string(t)];
                        if (xjt == 0) result.add_clause(std::vector<int>{-sijk, xit, -xkt, -fi01}); //jk->i 01 0
                        if (xjt == 1) result.add_clause(std::vector<int>{-sijk, xit, xkt, -fi10}); //jk->i 10 0
                        if (xjt == 1) result.add_clause(std::vector<int>{-sijk, xit, -xkt, -fi11}); //jk->i 11 0
                        if (xjt == 0) result.add_clause(std::vector<int>{-sijk, -xit, -xkt, fi01}); //jk->i 01 1
                        if (xjt == 1) result.add_clause(std::vector<int>{-sijk, -xit, xkt, fi10}); //jk->i 10 1
                        if (xjt == 1) result.add_clause(std::vector<int>{-sijk, -xit, -xkt, fi11}); //jk->i 11 1
                        if (xjt == 0) result.add_clause(std::vector<int>{-sijk, -xit, xkt}); //avoid 00 1
                        continue;
                    } else {
                        int xjt = variable_index["x" + std::to_string(j) + std::to_string(t)];
                        int xkt = variable_index["x" + std::to_string(k) + std::to_string(t)];
                        result.add_clause(std::vector<int>{-sijk, xit, xjt, -xkt, -fi01}); //jk->i 01 0
                        result.add_clause(std::vector<int>{-sijk, xit, -xjt, xkt, -fi10}); //jk->i 10 0
                        result.add_clause(std::vector<int>{-sijk, xit, -xjt, -xkt, -fi11}); //jk->i 11 0
                        result.add_clause(std::vector<int>{-sijk, -xit, xjt, -xkt, fi01}); //jk->i 01 1
                        result.add_clause(std::vector<int>{-sijk, -xit, -xjt, xkt, fi10}); //jk->i 10 1
                        result.add_clause(std::vector<int>{-sijk, -xit, -xjt, -xkt, fi11}); //jk->i 11 1
                        result.add_clause(std::vector<int>{-sijk, -xit, xjt, xkt}); //avoid 00 1
                    }
                }
            }
        }
    }
    for (int h = 1; h <= m; h++) {
        for (int i = initial_i + 1; i < initial_i + r + 1; i++) {   //Assuming none output equals to any input
            int ghi = variable_index["g" + std::to_string(i) + std::to_string(h)];
            for (int t = 1; t <= max_t; t++) {
                int xit = variable_index["x" + std::to_string(i) + std::to_string(t)];
                result.add_clause(std::vector<int>{-ghi, functions[h - 1].function[t] ? xit : -xit});
            }
        }
    }
    for (int h = 1; h <= m; h++) {
        std::vector<int> temp = {};
        for (int i = initial_i + 1; i < initial_i + r + 1; i++) {
            int ghi = variable_index["g" + std::to_string(i) + std::to_string(h)];
            temp.emplace_back(ghi);
        }
        result.add_clause(temp);
    }

    for (unsigned int i = initial_i + 1; i < initial_i + r + 1; i++) {
        std::vector<int> temp = {};
        for (int k = 1; k < i; k++) {
            if (k > n + 1 && k < initial_i) continue;
            for (int j = 1; j < k; j++) {
                if (j > n + 1 && j < initial_i) continue;
                temp.emplace_back(variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)]);
            }
        }
        result.add_clause(temp);
    }

    return result;
}

exact::MSV_Incremental::MSV_Incremental(std::vector<Boolean> functions, int _sub_r, int _sub_n) : MSV(
        std::move(functions)), sub_r(_sub_r), sub_n(_sub_n) {}

std::pair<std::vector<std::string>, std::vector<std::string>>
exact::MSV_Incremental::incremental_encode(const std::string &similar_method) {
    std::vector<std::string> dels;
    std::vector<std::string> adds;

    exact::Boolean sub_func = exact::Boolean(similar_sub_func(functions[0].function_str, similar_method, sub_n).first);
    MSV sub_msv = MSV(std::vector<exact::Boolean>{sub_func});
    sub_msv.r = sub_r;
    sub_msv.initial_i = functions[0].num_bits + 1;

    std::set<std::vector<int>> clause_set_sub, clause_set_cur;
    auto encoding_sub = sub_msv.encode(false);
    for (auto &clause: encoding_sub.clauses)
        clause_set_sub.insert(clause);

    auto encoding_cur = encode(true);
    for (auto &clause: encoding_cur.clauses)
        clause_set_cur.insert(clause);

    deal_set(dels, adds, clause_set_sub, clause_set_cur);
    return std::make_pair(dels, adds);
}

exact::Encoding exact::MSV_Incremental::encode(bool mark_variable) {
    int r = this->r, max_t =
            (1 << (functions[0].num_bits)) - 1, m = (int) functions.size(), n = functions[0].num_bits;
    for (auto &function: functions)
        assert(function.num_bits == n);

    std::map<std::string, int> variable_index = generate_variable_index(n, r, m);
    Encoding result = generate_clauses(variable_index, n, r, max_t, m);
    if (mark_variable) {
        for (auto &entry: variable_index)
            result.add_comment("c " + entry.first + " " + std::to_string(entry.second) + "\n");
    }
    assert(result.check());
    return result;
}

std::map<std::string, int> exact::MSV_Incremental::generate_variable_index(int n, int r, int m) {
    int max_t = (1 << n) - 1, sub_max_t = (1 << sub_n) - 1;
    std::map<std::string, int> variable_index = MSV::generate_variable_index(sub_n, sub_r, sub_max_t, m);
    int index = int(variable_index.size());

    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int t = 1; t <= max_t; t++)
            variable_index["x" + std::to_string(i) + std::to_string(t)] = index++;
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int h = 1; h <= m; h++)
            variable_index["g" + std::to_string(i) + std::to_string(h)] = index++;
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int j = 1; j < i; j++)
            variable_index["s" + std::to_string(i) + std::to_string(j)] = index++;
    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        variable_index["f" + std::to_string(i) + "11"] = index++;
        variable_index["f" + std::to_string(i) + "10"] = index++;
        variable_index["f" + std::to_string(i) + "01"] = index++;
    }
    return variable_index;
}

//exact::DITT_Incremental::DITT_Incremental(std::vector<Boolean> functions, int _sub_r, int _sub_n) : DITT(
//        std::move(functions)), sub_r(_sub_r), sub_n(_sub_n) {}

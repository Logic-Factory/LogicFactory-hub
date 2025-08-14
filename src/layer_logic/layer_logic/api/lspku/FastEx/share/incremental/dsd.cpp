//
// Created by zephyr on 2023/10/22.
//
#include "incremental.h"
#include <sstream>
#include <random>
#include <stack>
#include <algorithm>
#include "../utility/utility.h"

// reindex a prefix expression to make sure indices are continuous in alphabetical order
std::string re_index(const std::string& exp) {
    std::map<char, bool> index_map;
    char bar;
    for(auto& ch :exp)
        index_map[ch] = true;
    for(auto& entry: input_names) {
        if(!index_map[entry]) {
            bar = char(entry - 1);
            break;
        }
    }
    std::string result;
    for(auto& ch: exp) {
        if(ch == bar)
            result += RAND;
        else
            result += ch;
    }
    return result;
}


std::string exact::evaluate(std::string prefix, int n, int num_decomposable, const std::string& random_tt) {
    //For test
    //prefix = "+!&A&!!B!C!D";

    //WARNING: quite a INEFFICIENT way to calculate truth table.
    std::string result;
    std::map<char, bool> variable_value;

    std::reverse(prefix.begin(), prefix.end());
    unsigned int exp_length = prefix.length();

    for(int j=0; j<1<<n; j++) {
        std::vector<int> input = int_to_bvector(j, n);
        for(int index = 0; index < (num_decomposable == 0 ? n : num_decomposable); index ++)
            variable_value[input_names[index]] = bool(input[index]);

        std::stack <bool> q;
        for(int i = 0; i<exp_length; i++) {
            char ch = prefix[i];
            if(ch == '&') {
                bool op1 = q.top(); q.pop();
                bool op2 = q.top(); q.pop();
                q.push(op1 & op2);
            }else if(ch == '^') {
                bool op1 = q.top(); q.pop();
                bool op2 = q.top(); q.pop();
                q.push(op1 ^ op2);
            } else if(ch == '+') {
                bool op1 = q.top(); q.pop();
                bool op2 = q.top(); q.pop();
                q.push(op1 | op2);
            } else if(ch == '!') {
                bool op1 = q.top(); q.pop();
                q.push(!op1);
            } else if (ch == '0' || ch == '1') {
                q.push(ch - '0');
            } else if (ch == RAND) {
                std::vector<int> input_tt = std::vector<int>(input.begin()+num_decomposable, input.end());
                q.push(random_tt[bvector_to_int(input_tt)] - '0');
            } else {
                q.push(variable_value[ch]);
            }
        }
        result += q.top() ? '1' : '0';
    }
    return result;
}

std::string generate_exp(int &input_index, int n, std::random_device& random_engine) {
    std::string prefix;
    std::uniform_int_distribution<int> random_01(0, 1);
    std::uniform_int_distribution<int> random_op(0, 2);
    if (input_index == n - 1) {
        return random_01(random_engine) ? std::string(1, input_names[input_index++]) : std::string("!") + input_names[input_index++];
    }

    while (input_index < n) {
        char op = bi_ops[random_op(random_engine)];
        prefix += op;
        std::string operand1, operand2;
        std::uniform_int_distribution<int> random_disturb((input_index-n)/2, (n-input_index)/2);
        std::uniform_int_distribution<int> random_operand(0, n-input_index + random_disturb(random_engine));
        if (random_operand(random_engine) % 2 == 0) {
            operand1 = input_names[input_index++];
            operand2 = generate_exp(input_index, n, random_engine);
        }
        else {
            operand1 = generate_exp(input_index, n - 1, random_engine);
            operand2 = generate_exp(input_index, n, random_engine);
        }
        prefix += operand1;
        prefix += operand2;
    }

    if (random_01(random_engine) == 0)
        prefix = "!" + prefix;

    return prefix;
}

void exact::generate_full_dsd(const std::string &output, int n, int number) {
    std::ofstream fout(output, std::ios::out);
    assert(fout.is_open());
    std::map<std::string, std::string> result;

    std::random_device random_engine;
    //std::default_random_engine random_engine(2);

    //std::string prefix = "& & ! A B + C D";
    //evaluate(prefix, 4);
    while (result.size() < number) {
        int input_index = 0;
        std::string prefix = generate_exp(input_index, n, random_engine);

        std::string truth_table = evaluate(prefix, n);
        //Make sure generated prefix is normal function
        if(truth_table[0] == '1')
            prefix = prefix[0] == '!' ? prefix.substr(1, prefix.length()) : '!' + prefix;

        std::cout<<prefix<<" ";
        result[evaluate(prefix, n)] = prefix;
        std::cout<<result.size()<<std::endl;
    }

    for (auto &entry: result) {
        fout << binary_to_hex(entry.first) << " " << entry.first<< " " << entry.second << " default"<< std::endl;
    }
    fout.close();
}

void exact::generate_partial_dsd(const std::string &output, int n, int num_decomposable, int number) {
    std::ofstream fout(output, std::ios::out);
    assert(fout.is_open());

    std::map<std::string, std::string> result;

    std::random_device random_engine;
    std::map<std::string, std::string> random_tt_map;
    while (result.size() < number) {
        int input_index = 0;
        std::string prefix = re_index(generate_exp(input_index, num_decomposable + 1, random_engine));
        std::string random_truth_table = hex_to_binary(generate_random_tt(n - num_decomposable));
        std::string truth_table = evaluate(prefix, n, num_decomposable, random_truth_table);
        //Make sure generated prefix is normal function
        if(truth_table[0] == '1')
            prefix = prefix[0] == '!' ? prefix.substr(1, prefix.length()) : '!' + prefix;

        std::cout<<prefix<<" "<<hex_to_binary(random_truth_table)<<" ";
        std::string final_tt = evaluate(prefix, n, num_decomposable, random_truth_table);
        result[final_tt] = prefix;
        random_tt_map[final_tt] = random_truth_table;
        std::cout<<result.size()<<std::endl;
    }

    for (auto &entry: result) {
        fout << binary_to_hex(entry.first) << " " << entry.first<< " " << entry.second << " " << random_tt_map[entry.first] << std::endl;
    }

    fout.close();
}
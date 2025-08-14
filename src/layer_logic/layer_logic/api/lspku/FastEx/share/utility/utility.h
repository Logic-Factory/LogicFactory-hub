//
// Created by zephyr on 10/28/2023.
//
#ifndef EXACT_UTILITY_H
#define EXACT_UTILITY_H

#include <vector>
#include <string>
#include <array>
#include <cstdint>
#include "../exact_synthesis/exact.h"
std::vector<std::string> split(const std::string &str, char terminal = ' ');
std::vector<std::string> split(const std::string &str, std::vector<char> terminals);
std::vector<int> int_to_bvector(int n, unsigned int fix_length = 0);
int bvector_to_int(const std::vector<int> &b_vector);
int bvector_to_int(const std::string &b_vector);
std::vector<int> bvector_to_int(const std::vector<int> &b_vector, bool ignorant_item);
std::vector<char> bvector_to_hvector(const std::vector<int> &b_vector);
std::string hex_to_binary(const std::string &);
std::string binary_to_hex(const std::string &);
std::vector<bool> hex_to_binary(char hex);
int binary_to_int(const std::vector<bool> &bits);
std::vector<bool> int_to_binary(int i, int vector_size);
std::string generate_random_tt(int num_inputs);
std::pair<bool, std::vector<int>>
call_solver(const std::string &cnf_file, const std::string &solver, long double *runtime = nullptr,
            int num_threads = 10, const std::string& time_limit = "3h");
// SPECIAL designed for fast Boolean Function feature extraction
// Worse readability better performance
#define D_VARS 4
#define D_BITS 16
#define D_BLOCKS 1
#define D_INFLUENCE 4
#define D_SENSITIVITY 6
#define D_COFACTOR 8
#define D_COFACTOR2 24
#define D_HAMMING_DIS 16
//#define D_VARS 3
//#define D_BITS 8
//#define D_BLOCKS 1
//#define D_INFLUENCE 3
//#define D_SENSITIVITY 5
//#define D_COFACTOR 6
//#define D_COFACTOR2 12
//#define D_HAMMING_DIS 9
#define GET_BIT(p, i) (int)( ((p)[(i)>>6] >> ((i) & 63)) & 1 )
#define SET_BIT(p, i) ((p)[(i)>>6] |= ( 1ul<<((i) & 63) ))
#define CLR_BIT(p, i) ((p)[(i)>>6] &= ~( 1ul<<((i) & 63) ))
#define NEGATE(p, i) ((p)[i] ^= 0xffffffffffffffff )
// the storeger of truthtables uint64_t version
struct Truthtable_Manager_t {
    uint64_t **pFuncs = nullptr;
    uint32_t nFuncs{};
};
// Signatures structure
struct Signature_Manager_t {
    bool operator<(const Signature_Manager_t &other) const;
    void reset();
    uint32_t index{};                // the index at truth tables
    uint16_t minterm{};
    std::array<uint16_t, D_VARS> influence{0u};
    std::array<uint16_t, D_COFACTOR> cofactor{0u};
    std::array<uint16_t, D_COFACTOR2> cofactor2{0u};
    std::array<uint16_t, D_SENSITIVITY> sensitivity_one{0u};      // [0, nvars-1]
    std::array<uint16_t, D_SENSITIVITY> sensitivity_zero{0u};
};
Truthtable_Manager_t *Truthtable_Manager_Alloc(int size);
void Truthtable_Manager_Free(Truthtable_Manager_t *store);
void print_truthtables(Truthtable_Manager_t *store);
void print_signature(Signature_Manager_t sig);
void output_signature(Signature_Manager_t sig, std::ostream &out);
void calculate_feature(const std::string &input, const std::string &output_file); // Calculate a batch of features
void calculate_feature(std::string function, int *feature = nullptr); // Calculate feature of a given function
void calculate_feature(exact::Boolean &boolean, int *feature = nullptr); // Calculate feature of a given function
#endif //EXACT_UTILITY_H

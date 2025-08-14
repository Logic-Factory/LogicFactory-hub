//
// Created by zephyr on 2023/7/1.
//

#ifndef EXACT_SYNTHESIS_INCREMENTAL_H
#define EXACT_SYNTHESIS_INCREMENTAL_H

#include "../utility/utility.h"
#include "../exact_synthesis/exact.h"

#define RAND '[' // A random truth table
static char input_names[30] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R','S','T', 'U', 'V', 'W', 'X', 'Y', 'Z', RAND};
static char bi_ops[4] = {'+', '&', '^'};

namespace exact {
    std::pair<std::string, int>
    similar_sub_func(const std::string &original, const std::string &method, int sub_n, char *option, int num_decomposable, const std::string& random_tt);
    // return the sub_function truth_table and unused variable index (default is 1 if not applicable)

    class SSV_Incremental : public exact::SSV {
    public:
        int sub_r, sub_n;

        SSV_Incremental(std::vector<Boolean> functions, int sub_r, int sub_n);

        explicit SSV_Incremental(std::vector<Boolean> functions);

        std::pair<exact::Encoding, std::vector<int>> incremental_encode(bool mark_variable);
//Method1: Generate incremental exact synthesis encoding via path1 (change encoding)

        std::pair<std::vector<std::string>, std::vector<std::string>> incremental_encode();

//Method2: Generate incremental exact synthesis encoding via path2 (delete and add clauses)
        void set_similar_function(const std::string &similar_method = "trunc", char *similar_option = nullptr,
                                  int num_decomposable = 0, const std::string& random_tt = "", int sub_n = -1);

        std::string get_similar_function();

    private:
        Encoding encode_for_increment(bool mark_variable);

        bool similar_function_set;
        std::string similar_function;
        int non_sub_variable_index; // will be expanded to vector

        std::map<std::string, int> generate_variable_index(int n, int r, int m);

        //Above functions are for Method2
        std::map<std::string, int> generate_variable_index(int n, int r, int max_t, int m) override;

        exact::Encoding generate_clauses(std::map<std::string, int> &variable_index, int n, int r, int max_t, int m);
        //Above functions are for Method1
    };

    class MSV_Incremental : public exact::MSV {
        int sub_r, sub_n;

        MSV_Incremental(std::vector<Boolean> functions, int sub_r, int sub_n);

        //exact::Encoding incremental_encode();
//Method1: Generate incremental exact synthesis encoding via path1 (change encoding)

        std::pair<std::vector<std::string>, std::vector<std::string>>
        incremental_encode(const std::string &similar_method);
//Method2: Generate incremental exact synthesis encoding via path2 (delete and add clauses)
    private:
        Encoding encode(bool mark_variable) override;

        std::map<std::string, int> generate_variable_index(int n, int r, int m);
        //Above functions are for Method2
    };

    class DITT_Incremental : public exact::DITT {
        int sub_r, sub_n;

        DITT_Incremental(std::vector<Boolean> functions, int sub_r, int sub_n);

        //::Encoding incremental_encode();
//Method1: Generate incremental exact synthesis encoding via path1 (change encoding)

        std::pair<std::vector<std::string>, std::vector<std::string>>
        incremental_encode(const std::string &similar_method);
//Method2: Generate incremental exact synthesis encoding via path2 (delete and add clauses)
    private:
        Encoding encode(bool mark_variable) override;

        std::map<std::string, int> generate_variable_index(int n, int r, int m);
        //Above functions are for Method2
    };

    std::string evaluate(std::string prefix, int n, int num_decomposable = 0,
                         const std::string &random_tt = ""); //evaluate the truth table of a prefix Boolean expression

    void generate_full_dsd(const std::string &output, int n, int number = 1000);

    void generate_partial_dsd(const std::string &output, int n, int num_decomposable, int number = 1000);

    std::pair<bool, std::vector<int>>
    incremental_synthesis(exact::SSV_Incremental *, const std::string &, std::ostream &out, int num_threads = 1);
}
#endif //EXACT_SYNTHESIS_INCREMENTAL_H

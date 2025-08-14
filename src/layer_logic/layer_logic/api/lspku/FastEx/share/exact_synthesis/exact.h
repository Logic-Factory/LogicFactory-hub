//
// Created by zephyr on 2023/2/18.
//

#ifndef EXACT_SYNTHESIS_EXACT_H
#define EXACT_SYNTHESIS_EXACT_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <fstream>

namespace exact {
    class Boolean {
    public:
        std::vector<bool> function;
        std::string name, function_str;
        //function[i] is the ith bit of minimal item
        int num_bits;

        Boolean(std::string name, std::string function); // input: Hex format
        explicit Boolean(std::string function); // input: Hex format
        void print(std::ostream &out);
    };

    class Encoding {
    public:
        int num_variables;
        int num_clauses;
        int num_clauses_in_real;
        int num_variables_in_real;
        std::vector<std::vector<int>> clauses;
        std::vector<std::string> comments;
        std::vector<std::string> clauses_in_real;

        Encoding(int _num_variables, int _num_clauses) : num_variables(_num_variables), num_clauses(_num_clauses),
                                                         num_variables_in_real(0), num_clauses_in_real(0) {}

        Encoding(int _num_variables, int _num_clauses, int _num_variables_in_real, int _num_clauses_in_real)
                : num_variables(_num_variables), num_clauses(_num_clauses),
                  num_variables_in_real(_num_variables_in_real), num_clauses_in_real(_num_clauses_in_real) {}

        Encoding() : num_clauses(0), num_variables(0), num_variables_in_real(0), num_clauses_in_real(0) {}

        Encoding(const std::string &file_name);

        bool check();

        void add_clause(const std::vector<int> &, bool no_check = true);

        void add_comment(const std::string &comment);

        void write_dimacs(std::ostream &out);

        void write_smt2(std::ostream &out, bool keep_result);

        bool verify(std::vector<bool>);
        // Only for SAT
    };

    class Technology {
    public:
        Technology();

        std::vector<Boolean> gates;

        explicit Technology(const std::vector<std::string> &functions);

        Technology(Technology const &_technology) = default;
    };

    class Encoder {
    public:
        std::vector<Boolean> functions;
        Technology technology;
        int r{}; //num of steps/gates
        int initial_i{}; // index of initial i, default set to n+1
        bool non_trivial{}, all_steps{}, no_replication{}, lexicographical_step{}, lexicographical_op{}, ordered_symmetric{};
        std::vector<std::vector<int>> pi_tt;

        Encoder(std::vector<Boolean> functions, const Technology &_technology, int r, bool non_trivial,
                bool all_steps, bool no_replication, bool lexicographical_step, bool lexicographical_op,
                bool ordered_symmetric);

        Encoder(const std::vector<std::string> &, const Technology &, int r, bool non_trivial,
                bool all_steps, bool no_replication, bool lexicographical_step, bool lexicographical_op,
                bool ordered_symmetric);

        Encoder() = default;

        virtual Encoding encode();

        virtual Encoding encode(bool mark_variable);

        std::pair<exact::Encoding, std::vector<int>>
        incremental_encode(bool mark_variable);
//Method1: Generate incremental exact synthesis encoding via path1 (change encoding)

        std::pair<std::vector<std::string>, std::vector<std::string>>
        incremental_encode();
//Method2: Generate incremental exact synthesis encoding via path2 (delete and add clauses)

        virtual void decode(std::vector<int>, std::string output_file);

        virtual std::map<std::string, int> generate_variable_index(int n, int r, int max_t, int m);

    private:
        virtual void add_all_steps(std::map<std::string, int> &variable_index, exact::Encoding &result, int n);

        virtual void add_non_trivial(std::map<std::string, int> &variable_index, exact::Encoding &result, int n);

        virtual void add_no_replication(std::map<std::string, int> &variable_index, exact::Encoding &result, int n);

        virtual void
        add_lexicographical_step(std::map<std::string, int> &variable_index, exact::Encoding &result, int n);

        virtual void add_lexicographical_op(std::map<std::string, int> &variable_index, exact::Encoding &result, int n);

        virtual void add_ordered_symmetric(std::map<std::string, int> &variable_index, exact::Encoding &result, int n);
    };

    class MSV : public Encoder {
    public:
        MSV(std::vector<Boolean> functions, const Technology &_technology, int r, bool non_trivial, bool all_steps,
            bool no_replication, bool lexicographical_step, bool lexicographical_op, bool ordered_symmetric);

        MSV(const std::vector<std::string> &functions, const Technology &_technology, int r, bool non_trivial,
            bool all_steps,
            bool no_replication, bool lexicographical_step, bool lexicographical_op, bool ordered_symmetric);

        explicit MSV(const std::vector<std::string> &functions);

        explicit MSV(std::vector<Boolean> functions);

        Encoding encode(bool mark_variable) override;

        void decode(std::vector<int>, std::string output_file) override;

    private:
        void add_all_steps(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void add_non_trivial(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void add_no_replication(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void
        add_lexicographical_step(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void
        add_lexicographical_op(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void add_ordered_symmetric(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

    protected:
        std::map<std::string, int> generate_variable_index(int n, int r, int max_t, int m) override;

        Encoding generate_clauses(std::map<std::string, int> &, int n, int r, int max_t, int m);
    };

    class SSV : public Encoder {
    public:
        SSV(std::vector<Boolean> functions, const Technology &_technology, int r, bool non_trivial, bool all_steps,
            bool no_replication, bool lexicographical_step, bool lexicographical_op, bool ordered_symmetric);

        SSV(const std::vector<std::string> &functions, const Technology &_technology, int r, bool non_trivial,
            bool all_steps,
            bool no_replication, bool lexicographical_step, bool lexicographical_op, bool ordered_symmetric);

        explicit SSV(const std::vector<std::string> &functions);

        explicit SSV(std::vector<Boolean> functions);

        Encoding encode(bool mark_variable) override;

        void decode(std::vector<int>, std::string output_file) override;

    private:
        void add_all_steps(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void add_non_trivial(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void add_no_replication(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void
        add_lexicographical_step(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void
        add_lexicographical_op(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void add_ordered_symmetric(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

    protected:
        std::map<std::string, int> generate_variable_index(int n, int r, int max_t, int m) override;

        Encoding generate_clauses(std::map<std::string, int> &, int n, int r, int max_t, int m);
    };

    class DITT : public Encoder {
    public:
        DITT(std::vector<Boolean> functions, const Technology &_technology, int r, bool non_trivial, bool all_steps,
             bool no_replication, bool lexicographical_step, bool lexicographical_op, bool ordered_symmetric);

        DITT(const std::vector<std::string> &functions, const Technology &_technology, int r, bool non_trivial,
             bool all_steps, bool no_replication, bool lexicographical_step, bool lexicographical_op,
             bool ordered_symmetric);

        explicit DITT(const std::vector<std::string> &functions);

        explicit DITT(std::vector<Boolean> functions);

        Encoding encode(bool mark_variable) override;

        void decode(std::vector<int>, std::string output_file) override;

    private:
        void add_all_steps(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void add_non_trivial(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void add_no_replication(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void
        add_lexicographical_step(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void
        add_lexicographical_op(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

        void add_ordered_symmetric(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) override;

    protected:
        std::map<std::string, int> generate_variable_index(int n, int r, int max_t, int m) override;

        Encoding generate_clauses(std::map<std::string, int> &, int n, int r, int max_t, int m);
    };

    bool is_symmetric(std::vector<exact::Boolean> &functions, int p, int q);

    void generate_netlist_library(std::string const &, int);

    std::pair<bool, std::vector<int>>
    synthesis(exact::Encoder *, const std::string &, std::ostream &out, int num_threads = 10);
}

void generate_tt(const std::string &output, int num_inputs, int num_outputs);

#endif //EXACT_SYNTHESIS_EXACT_H

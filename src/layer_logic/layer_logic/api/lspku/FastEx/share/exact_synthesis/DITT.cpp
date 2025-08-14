//
// Created by zephyr on 2023/2/18.
//
#include "exact.h"

void exact::DITT::add_non_trivial(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int i = initial_i; i < initial_i + r; i++) {
        int fi01 = variable_index["f" + std::to_string(i) + "01"];
        int fi10 = variable_index["f" + std::to_string(i) + "10"];
        int fi11 = variable_index["f" + std::to_string(i) + "11"];
        result.add_clause(std::vector<int>{fi01, fi10, fi11});
        result.add_clause(std::vector<int>{fi01, -fi10, -fi11});
        result.add_clause(std::vector<int>{-fi01, fi10, -fi11});
    }
}

void exact::DITT::add_all_steps(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    int m = int(functions.size());
    for (int i = initial_i; i < initial_i + r; i++) {
        std::vector<int> temp{};
        for (int k = 1; k <= m; k++) {
            temp.emplace_back(variable_index["g" + std::to_string(i) + std::to_string(k)]);
        }
        for (int _i = i + 1; _i < initial_i + r; _i++) {
            temp.emplace_back(variable_index["s1_" + std::to_string(_i) + std::to_string(i)]);
            temp.emplace_back(variable_index["s2_" + std::to_string(_i) + std::to_string(i)]);
        }
        result.add_clause(temp);
    }
}

void exact::DITT::add_no_replication(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    std::set<std::vector<int>> clauses;
    for (int i = initial_i; i < initial_i + r; i++) {
        for (int _i = i + 1; _i < initial_i + r; _i++) {
            for (int k = 1; k < i; k++) {
                if (k > n && k < initial_i) continue;
                for (int j = 1; j < i; j++) {
                    if (j > n && j < initial_i) continue;
                    int s1_ij = variable_index["s1_" + std::to_string(i) + std::to_string(j)];
                    int s2_ik = variable_index["s2_" + std::to_string(i) + std::to_string(k)];
                    int s2__ij = variable_index["s2_" + std::to_string(_i) + std::to_string(j)];
                    int s2__ik = variable_index["s2_" + std::to_string(_i) + std::to_string(k)];
                    int s1__ii = variable_index["s1_" + std::to_string(_i) + std::to_string(i)];
                    int s1__ij = variable_index["s2_" + std::to_string(_i) + std::to_string(j)];
                    int s1__ik = variable_index["s2_" + std::to_string(_i) + std::to_string(k)];
                    int s2__ii = variable_index["s1_" + std::to_string(_i) + std::to_string(i)];
                    clauses.insert(std::vector<int>{-s1_ij, -s2_ik, -s1__ii, -s2__ij});
                    clauses.insert(std::vector<int>{-s1_ij, -s2_ik, -s1__ii, -s2__ik});
                    clauses.insert(std::vector<int>{-s1_ij, -s2_ik, -s2__ii, -s1__ij});
                    clauses.insert(std::vector<int>{-s1_ij, -s2_ik, -s2__ii, -s1__ik});
                }
            }
        }
    }
    for (auto &clause: clauses) {
        result.add_clause(clause);
    }
}

void exact::DITT::add_lexicographical_step(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int i = initial_i; i < initial_i + r - 1; i++) {
        int _i = i + 1;
        for (int k = 1; k < i; k++) {
            if (k > n && k < initial_i) continue;
            for (int _k = 1; _k < _i; _k++) {
                if (_k > n && _k < initial_i) continue;
                for (int j = 1; j < i; j++) {
                    if (j > n && j < initial_i) continue;
                    for (int _j = 1; _j < _i; _j++) {
                        if (_j > n && _j < initial_i) continue;
                        int s1_ij = variable_index["s1_" + std::to_string(i) + std::to_string(j)];
                        int s2_ik = variable_index["s2_" + std::to_string(i) + std::to_string(k)];
                        int s1__i_j = variable_index["s1_" + std::to_string(_i) + std::to_string(_j)];
                        int s2__i_k = variable_index["s2_" + std::to_string(_i) + std::to_string(_k)];
                        if (k <= j) {// Add constraint that input index of s1_ is smaller than s2_
                            result.add_clause(std::vector<int>{-s1_ij, -s2_ik});
                        }
                        if (_k <= _j) {// Add constraint that input index of s1_ is smaller than s2_
                            result.add_clause(std::vector<int>{-s1__i_j, -s2__i_k});
                        }
                        if ((_j < j && k == _k) || _k < k) {
                            result.add_clause(std::vector<int>{-s1_ij, -s2_ik, -s1__i_j, -s2__i_k});
                        }
                    }
                }
            }
        }
    }
}

void exact::DITT::add_lexicographical_op(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    //If fi+1 < fi, then sij, sik, si+1j, and si+1k will not appear at the same time
    for (int i = initial_i; i < initial_i + r - 1; i++) {
        int _i = i + 1;
        int fi11 = variable_index["f" + std::to_string(i) + "11"];
        int fi10 = variable_index["f" + std::to_string(i) + "10"];
        int fi01 = variable_index["f" + std::to_string(i) + "01"];
        int f_i11 = variable_index["f" + std::to_string(_i) + "11"];
        int f_i10 = variable_index["f" + std::to_string(_i) + "10"];
        int f_i01 = variable_index["f" + std::to_string(_i) + "01"];
        for (int k = 1; k < i; k++) {
            if (k > n && k < initial_i) continue;
            for (int j = 1; j < k; j++) {
                if (j > n && j < initial_i) continue;
                // ASSERT input index of s1_ is smaller than s2_
                int s1_ij = variable_index["s1_" + std::to_string(i) + std::to_string(j)];
                int s1__ij = variable_index["s1_" + std::to_string(_i) + std::to_string(j)];
                int s2_ik = variable_index["s2_" + std::to_string(i) + std::to_string(k)];
                int s2__ik = variable_index["s2_" + std::to_string(_i) + std::to_string(k)];
                result.add_clause(std::vector<int>{fi01, fi10, fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                //000 < everything
                //result.add_clause(std::vector<int>{f_i01, f_i10, f_i11, fi01, fi10, -fi11, -sijk, -s_ijk});
                //001 only > 000, is contained by clause1
                //result.add_clause(std::vector<int>{f_i01, f_i10, f_i11, fi01, -fi10, fi11, -sijk, -s_ijk});
                result.add_clause(
                        std::vector<int>{f_i01, f_i10, -f_i11, fi01, -fi10, fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                //010 > 000(contained by clause1) && 010 > 001
                //result.add_clause(std::vector<int>{f_i01, f_i10, f_i11, fi01, -fi10, -fi11, -sijk, -s_ijk});
                result.add_clause(
                        std::vector<int>{f_i01, f_i10, -f_i11, fi01, -fi10, -fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                result.add_clause(
                        std::vector<int>{f_i01, -f_i10, f_i11, fi01, -fi10, -fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                //011 > 000(contained by clause 1) && 011 > 001 && 011 > 010
                result.add_clause(
                        std::vector<int>{f_i01, f_i10, -f_i11, -fi01, fi10, fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                result.add_clause(
                        std::vector<int>{f_i01, -f_i10, f_i11, -fi01, fi10, fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                result.add_clause(
                        std::vector<int>{f_i01, -f_i10, -f_i11, -fi01, fi10, fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                //100 > 000(contained by clause1)/001/010/011
                result.add_clause(
                        std::vector<int>{f_i01, f_i10, -f_i11, -fi01, fi10, -fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                result.add_clause(
                        std::vector<int>{f_i01, -f_i10, f_i11, -fi01, fi10, -fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                result.add_clause(
                        std::vector<int>{f_i01, -f_i10, -f_i11, -fi01, fi10, -fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                result.add_clause(
                        std::vector<int>{-f_i01, f_i10, f_i11, -fi01, fi10, -fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                //101 > 000/001/010/011/100
                result.add_clause(
                        std::vector<int>{f_i01, f_i10, -f_i11, -fi01, -fi10, fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                result.add_clause(
                        std::vector<int>{f_i01, -f_i10, f_i11, -fi01, -fi10, fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                result.add_clause(
                        std::vector<int>{f_i01, -f_i10, -f_i11, -fi01, -fi10, fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                result.add_clause(
                        std::vector<int>{-f_i01, f_i10, f_i11, -fi01, -fi10, fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                result.add_clause(
                        std::vector<int>{-f_i01, f_i10, -f_i11, -fi01, -fi10, fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                //110 > 000/001/010/011/100/101
                result.add_clause(std::vector<int>{-fi01, -fi10, -fi11, -s1_ij, -s1__ij, -s2_ik, -s2__ik});
                //111 > everything
            }
        }
    }
}

void exact::DITT::add_ordered_symmetric(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int q = 0; q < functions[0].num_bits; q++) {
        for (int p = 0; p < q; p++) {
            if (!is_symmetric(functions, p, q))
                continue;
            int index_p = p + 1, index_q = q + 1;
            for (int i = initial_i; i < initial_i + r; i++) {
                std::vector<int> temp1{
                        -variable_index["s1_" + std::to_string(i) + std::to_string(index_q)]};
                std::vector<int> temp2{
                        -variable_index["s2_" + std::to_string(i) + std::to_string(index_q)]};
                for (int _i = initial_i; _i < i; _i++) {
                    for (int _j = 1; _j < _i; _j++) {
                        if (_j > n && _j < initial_i) continue;
                        if (_j == index_p) {
                            int s1__i_j = variable_index["s1_" + std::to_string(_i) + std::to_string(_j)];
                            int s2__i_j = variable_index["s2_" + std::to_string(_i) + std::to_string(_j)];
                            temp1.emplace_back(s1__i_j);
                            temp1.emplace_back(s2__i_j);
                            temp2.emplace_back(s1__i_j);
                            temp2.emplace_back(s2__i_j);
                        }
                    }
                }
                if (temp1.size() > 1)
                    result.add_clause(temp1);
                if (temp2.size() > 1)
                    result.add_clause(temp2);
            }
        }
    }
}

std::map<std::string, int> exact::DITT::generate_variable_index(int n, int r, int max_t, int m) {
    int index = 1;
    std::map<std::string, int> variable_index;
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int t = 1; t <= max_t; t++) {
            variable_index["x" + std::to_string(i) + std::to_string(t)] = index++;
            variable_index["x1_" + std::to_string(i) + std::to_string(t)] = index++;
            variable_index["x2_" + std::to_string(i) + std::to_string(t)] = index++;
        }
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int h = 1; h <= m; h++)
            variable_index["g" + std::to_string(i) + std::to_string(h)] = index++;
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int j = 1; j < i; j++) {
            if (j > n && j < initial_i) continue;
            variable_index["s1_" + std::to_string(i) + std::to_string(j)] = index++;
            variable_index["s2_" + std::to_string(i) + std::to_string(j)] = index++;
        }
    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        variable_index["f" + std::to_string(i) + "11"] = index++;
        variable_index["f" + std::to_string(i) + "10"] = index++;
        variable_index["f" + std::to_string(i) + "01"] = index++;
    }
    return variable_index;
}

exact::Encoding exact::DITT::encode(bool mark_variable) {
    int r = this->r, max_t =
            (1 << (functions[0].num_bits)) - 1, m = (int) functions.size(), n = functions[0].num_bits, index = 1;
    for (auto &function: functions)
        assert(function.num_bits == n);

    std::map<std::string, int> variable_index = generate_variable_index(n, r, max_t, m);

    Encoding result = generate_clauses(variable_index, n, r, max_t, m);
    if (mark_variable) {
        for (auto &entry: variable_index)
            result.add_comment("c " + entry.first + " " + std::to_string(entry.second) + "\n");
    }

    assert(result.check());

    return result;
}

exact::DITT::DITT(std::vector<Boolean> functions, const exact::Technology &_technology, int _r, bool _non_trivial,
                  bool _all_steps,
                  bool _no_replication, bool _lexicographical_step, bool _lexicographical_op, bool _ordered_symmetric)
        : Encoder(std::move(functions), _technology, _r, _non_trivial, _all_steps, _no_replication,
                  _lexicographical_step, _lexicographical_op, _ordered_symmetric) {}

exact::DITT::DITT(const std::vector<std::string> &functions, const exact::Technology &_technology, int _r,
                  bool _non_trivial, bool _all_steps,
                  bool _no_replication, bool _lexicographical_step, bool _lexicographical_op, bool _ordered_symmetric)
        : Encoder(functions, _technology, _r, _non_trivial, _all_steps, _no_replication,
                  _lexicographical_step, _lexicographical_op, _ordered_symmetric) {}

exact::DITT::DITT(const std::vector<std::string> &functions)
        : Encoder(functions, exact::Technology(), 0, false, false, false, false, false, false) {}

exact::DITT::DITT(std::vector<Boolean> functions)
        : Encoder(std::move(functions), exact::Technology(), 0, false, false, false, false, false, false) {}

void exact::DITT::decode(std::vector<int> input, std::string output_file) {
    int r = this->r, max_t =
            (1 << (functions[0].num_bits)) - 1, m = (int) functions.size(), n = functions[0].num_bits;
    std::map<std::string, int> variable_index = generate_variable_index(n, r, max_t, m);
    std::ofstream fout(output_file);
    assert(fout.is_open());

    std::map<int, bool> variable_assignment;
    for (auto& temp: input){
        int index = abs(temp);
        variable_assignment[index] = index == temp;
    }

    fout << "## Benchmark written by FastEx\n"
            ".model top\n";
    fout << ".inputs ";
    for (int i = 0; i < functions[0].num_bits; i++) {
        fout << "x" << i << " ";
    }
    fout << "\n.outputs ";
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int h = 1; h <= m; h++) {
            if (variable_assignment[variable_index["g" + std::to_string(i) + std::to_string(h)]]) {
                fout << "x" << i << " ";
            }
        }
    fout << "\n";

    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        fout << ".names ";
        for (int j = 1; j < i; j++) {
            if (variable_assignment[variable_index["s1_" + std::to_string(i) + std::to_string(j)]]) {
                fout << "x" << j << " ";
            }
            if (variable_assignment[variable_index["s2_" + std::to_string(i) + std::to_string(j)]]) {
                fout << "x" << j << " ";
            }
        }
        fout << "x" << i << "\n";
        if (variable_assignment[variable_index["f" + std::to_string(i) + "01"]])
            fout << ".01 1\n";
        if (variable_assignment[variable_index["f" + std::to_string(i) + "10"]])
            fout << ".10 1\n";
        if (variable_assignment[variable_index["f" + std::to_string(i) + "11"]])
            fout << ".11 1\n";
    }
    fout << ".end\n";
}

exact::Encoding
exact::DITT::generate_clauses(std::map<std::string, int> &variable_index, int n, int r, int max_t, int m) {
    Encoding result;

    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        int fi11 = variable_index["f" + std::to_string(i) + "11"];
        int fi10 = variable_index["f" + std::to_string(i) + "10"];
        int fi01 = variable_index["f" + std::to_string(i) + "01"];
        for (int t = 1; t <= max_t; t++) {
            int xit = variable_index["x" + std::to_string(i) + std::to_string(t)];
            int x1_it = variable_index["x1_" + std::to_string(i) + std::to_string(t)];
            int x2_it = variable_index["x2_" + std::to_string(i) + std::to_string(t)];
            result.add_clause(std::vector<int>{xit, x1_it, -x2_it, -fi01}); //x1_it op x2_it -> xit 01 0
            result.add_clause(std::vector<int>{xit, -x1_it, x2_it, -fi10}); //x1_it op x2_it -> xit 10 0
            result.add_clause(std::vector<int>{xit, -x1_it, -x2_it, -fi11}); //x1_it op x2_it -> xit 11 0
            result.add_clause(std::vector<int>{-xit, x1_it, -x2_it, fi01}); //x1_it op x2_it -> xit 01 1
            result.add_clause(std::vector<int>{-xit, -x1_it, x2_it, fi10}); //x1_it op x2_it -> xit 10 1
            result.add_clause(std::vector<int>{-xit, -x1_it, -x2_it, fi11}); //x1_it op x2_it -> xit 11 1
            result.add_clause(std::vector<int>{-xit, x1_it, x2_it}); //avoid 00 1
            std::vector<int> temp1{}, temp2{};
            for (int j = 1; j < i; j++) {
                if (j > n && j < initial_i) continue;
                int s1_ij = variable_index["s1_" + std::to_string(i) + std::to_string(j)];
                int s2_ij = variable_index["s2_" + std::to_string(i) + std::to_string(j)];
                if (j <= n) {
                    int xjt = pi_tt[j][t];
                    if (xjt == 0) {
                        result.add_clause(std::vector<int>{-s1_ij, -x1_it});
                        result.add_clause(std::vector<int>{-s2_ij, -x2_it});
                    } else {
                        result.add_clause(std::vector<int>{-s1_ij, x1_it});
                        result.add_clause(std::vector<int>{-s2_ij, x2_it});
                    }
                } else {
                    int xjt = variable_index["x" + std::to_string(j) + std::to_string(t)];
                    result.add_clause(std::vector<int>{-s1_ij, -x1_it, xjt});
                    result.add_clause(std::vector<int>{-s1_ij, x1_it, -xjt});
                    result.add_clause(std::vector<int>{-s2_ij, -x2_it, xjt});
                    result.add_clause(std::vector<int>{-s2_ij, x2_it, -xjt});
                }
                temp1.emplace_back(s1_ij);
                temp2.emplace_back(s2_ij);
            }
            result.add_clause(temp1);
            result.add_clause(temp2);
        }
    }
    for (int h = 1; h <= m; h++) {
        for (int i = initial_i; i < initial_i + r; i++) {   //Assuming none output equals to any input
            int ghi = variable_index["g" + std::to_string(i) + std::to_string(h)];
            for (int t = 1; t <= max_t; t++) {
                int xit = variable_index["x" + std::to_string(i) + std::to_string(t)];
                result.add_clause(std::vector<int>{-ghi, functions[h - 1].function[t] ? xit : -xit});
            }
        }
    }
    for (int h = 1; h <= m; h++) {
        std::vector<int> temp = {};
        for (int i = initial_i; i < initial_i + r; i++) {
            int ghi = variable_index["g" + std::to_string(i) + std::to_string(h)];
            temp.emplace_back(ghi);
        }
        result.add_clause(temp);
    }

    if (non_trivial)
        add_non_trivial(variable_index, result, n);
    if (all_steps)
        add_all_steps(variable_index, result, n);
    if (no_replication)
        add_no_replication(variable_index, result, n);
    if (lexicographical_step)
        add_lexicographical_step(variable_index, result, n);
    if (lexicographical_op)
        add_lexicographical_op(variable_index, result, n);
    if (ordered_symmetric)
        add_ordered_symmetric(variable_index, result, n);

    return result;
}

//
// Created by zephyr on 2023/2/18.
//

#include <utility>

#include "exact.h"

void exact::SSV::add_non_trivial(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int i = initial_i; i < initial_i + r; i++) {
        int fi01 = variable_index["f" + std::to_string(i) + "01"];
        int fi10 = variable_index["f" + std::to_string(i) + "10"];
        int fi11 = variable_index["f" + std::to_string(i) + "11"];
        result.add_clause(std::vector<int>{fi01, fi10, fi11});
        result.add_clause(std::vector<int>{fi01, -fi10, -fi11});
        result.add_clause(std::vector<int>{-fi01, fi10, -fi11});
    }
}

void exact::SSV::add_all_steps(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    int m = int(functions.size());
    for (int i = initial_i; i < initial_i + r; i++) {
        std::vector<int> temp{};
        for (int k = 1; k <= m; k++) {
            temp.emplace_back(variable_index["g" + std::to_string(i) + std::to_string(k)]);
        }
        for (int _i = i + 1; _i < initial_i + r; _i++) {
            for (int j = 1; j < i; j++) {
                if (j > n && j < initial_i) continue;
                temp.emplace_back(variable_index["s" + std::to_string(_i) + std::to_string(j) + std::to_string(i)]);
            }
            for (int j = i + 1; j < _i; j++) {
                temp.emplace_back(variable_index["s" + std::to_string(_i) + std::to_string(i) + std::to_string(j)]);
            }
        }
        result.add_clause(temp);
    }
}

void exact::SSV::add_no_replication(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int i = initial_i; i < initial_i + r; i++) {
        for (int _i = i + 1; _i < initial_i + r; _i++) {
            for (int k = 1; k < i; k++) {
                if (k > n && k < initial_i) continue;
                for (int j = 1; j < k; j++) {
                    if (j > n && j < initial_i) continue;
                    int sijk = variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)];
                    int s_iji = variable_index["s" + std::to_string(_i) + std::to_string(j) + std::to_string(i)];
                    int s_iki = variable_index["s" + std::to_string(_i) + std::to_string(k) + std::to_string(i)];
                    result.add_clause(std::vector<int>{-sijk, -s_iji});
                    result.add_clause(std::vector<int>{-sijk, -s_iki});
                }
            }
        }
    }
}

void exact::SSV::add_lexicographical_step(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int i = initial_i; i < initial_i + r - 1; i++) {
        int _i = i + 1;
        for (int k = 1; k < i; k++) {
            if (k > n && k < initial_i) continue;
            for (int _k = 1; _k < _i; _k++) {
                if (_k > n && _k < initial_i) continue;
                for (int j = 1; j < k; j++) {
                    if (j > n && j < initial_i) continue;
                    for (int _j = 1; _j < _k; _j++) {
                        if (_k > n && _k < initial_i) continue;
                        int sijk = variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)];
                        int s_i_j_k = variable_index["s" + std::to_string(_i) + std::to_string(_j) +
                                                     std::to_string(_k)];
                        if ((_j < j && k == _k) || _k < k) {
                            result.add_clause(std::vector<int>{-sijk, -s_i_j_k});
                        }
                    }
                }
            }
        }
    }
}

void exact::SSV::add_lexicographical_op(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    //fi01<fi10<fi11; If fi+1 < fi, then sijk and si+1jk will not appear at the same time
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
                int sijk = variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)];
                int s_ijk = variable_index["s" + std::to_string(_i) + std::to_string(j) + std::to_string(k)];
                result.add_clause(std::vector<int>{fi01, fi10, fi11, -sijk, -s_ijk});
                //000 < everything
                //result.add_clause(std::vector<int>{f_i01, f_i10, f_i11, fi01, fi10, -fi11, -sijk, -s_ijk});
                //001 only > 000, is contained by clause1
                //result.add_clause(std::vector<int>{f_i01, f_i10, f_i11, fi01, -fi10, fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, f_i10, -f_i11, fi01, -fi10, fi11, -sijk, -s_ijk});
                //010 > 000(contained by clause1) && 010 > 001
                //result.add_clause(std::vector<int>{f_i01, f_i10, f_i11, fi01, -fi10, -fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, f_i10, -f_i11, fi01, -fi10, -fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, -f_i10, f_i11, fi01, -fi10, -fi11, -sijk, -s_ijk});
                //011 > 000(contained by clause 1) && 011 > 001 && 011 > 010
                result.add_clause(std::vector<int>{f_i01, f_i10, -f_i11, -fi01, fi10, fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, -f_i10, f_i11, -fi01, fi10, fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, -f_i10, -f_i11, -fi01, fi10, fi11, -sijk, -s_ijk});
                //100 > 000(contained by clause1)/001/010/011
                result.add_clause(std::vector<int>{f_i01, f_i10, -f_i11, -fi01, fi10, -fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, -f_i10, f_i11, -fi01, fi10, -fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, -f_i10, -f_i11, -fi01, fi10, -fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{-f_i01, f_i10, f_i11, -fi01, fi10, -fi11, -sijk, -s_ijk});
                //101 > 000/001/010/011/100
                result.add_clause(std::vector<int>{f_i01, f_i10, -f_i11, -fi01, -fi10, fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, -f_i10, f_i11, -fi01, -fi10, fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, -f_i10, -f_i11, -fi01, -fi10, fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{-f_i01, f_i10, f_i11, -fi01, -fi10, fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{-f_i01, f_i10, -f_i11, -fi01, -fi10, fi11, -sijk, -s_ijk});
                //110 > 000/001/010/011/100/101
                result.add_clause(std::vector<int>{-fi01, -fi10, -fi11, -sijk, -s_ijk});
                //111 > everything
            }
        }
    }
}

void exact::SSV::add_ordered_symmetric(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int q = 0; q < functions[0].num_bits; q++) {
        for (int p = 0; p < q; p++) {
            if (!is_symmetric(functions, p, q))
                continue;

            int index_p = p + 1, index_q = q + 1;
            for (int i = initial_i; i < initial_i + r; i++) {
                for (int j = 1; j < index_q; j++) {
                    if (j == index_p) continue;
                    if (j > n && j < initial_i) continue;
                    std::vector<int> temp{
                            -variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(index_q)]};
                    for (int _i = initial_i; _i < i; _i++) {
                        for (int _k = 1; _k < _i; _k++) {
                            if (_k > n && _k < initial_i) continue;
                            for (int _j = 1; _j < _k; _j++) {
                                if (_j > n && _j < initial_i) continue;
                                if (_j == index_p || _k == index_p) {
                                    int s_i_j_k = variable_index["s" + std::to_string(_i) + std::to_string(_j) +
                                                                 std::to_string(_k)];
                                    temp.emplace_back(s_i_j_k);
                                }
                            }
                        }
                    }
                    if (temp.size() > 1)
                        result.add_clause(temp);
                }
            }
        }
    }
}

std::map<std::string, int> exact::SSV::generate_variable_index(int n, int r, int max_t, int m) {
    std::map<std::string, int> variable_index;
    int index = 1;
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int t = 1; t <= max_t; t++)
            variable_index["x" + std::to_string(i) + std::to_string(t)] = index++;
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int h = 1; h <= m; h++)
            variable_index["g" + std::to_string(i) + std::to_string(h)] = index++;
    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        for (int k = 1; k < i; k++) {
            if (k > n && k < initial_i) continue;
            for (int j = 1; j < k; j++) {
                if (j > n && j < initial_i) continue;
                variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)] = index++;
            }
        }
    }
    for (unsigned int i = initial_i; i < initial_i + r; i++) {
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
exact::SSV::generate_clauses(std::map<std::string, int> &variable_index, int n, int r, int max_t, int m) {
    Encoding result;
    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        int fi11 = variable_index["f" + std::to_string(i) + "11"];
        int fi10 = variable_index["f" + std::to_string(i) + "10"];
        int fi01 = variable_index["f" + std::to_string(i) + "01"];
        for (int k = 1; k < i; k++) {
            if (k > n && k < initial_i) continue;
            for (int j = 1; j < k; j++) {
                if (j > n && j < initial_i) continue;
                int sijk = variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)];
                for (int t = 1; t <= max_t; t++) {
                    int xit = variable_index["x" + std::to_string(i) + std::to_string(t)];
                    if (j <= n && k <= n) {
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
                    if (j <= n) {
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

    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        std::vector<int> temp = {};
        for (int k = 1; k < i; k++) {
            if (k > n && k < initial_i) continue;
            for (int j = 1; j < k; j++) {
                if (j > n && j < initial_i) continue;
                temp.emplace_back(variable_index["s" + std::to_string(i) + std::to_string(j) + std::to_string(k)]);
            }
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

exact::Encoding exact::SSV::encode(bool mark_variable) {
    int r = this->r, max_t =
            (1 << (functions[0].num_bits)) - 1, m = (int) functions.size(), n = functions[0].num_bits;
    for (auto &function: functions)
        assert(function.num_bits == n);

    std::map<std::string, int> variable_index = SSV::generate_variable_index(n, r, max_t, m);
    Encoding result = generate_clauses(variable_index, n, r, max_t, m);
    if (mark_variable) {
        for (auto &entry: variable_index)
            result.add_comment("c " + entry.first + " " + std::to_string(entry.second) + "\n");
    }

    assert(result.check());
    return result;
}

exact::SSV::SSV(std::vector<Boolean> functions, const exact::Technology &_technology, int _r, bool _non_trivial,
                bool _all_steps,
                bool _no_replication, bool _lexicographical_step, bool _lexicographical_op, bool _ordered_symmetric)
        : Encoder(std::move(functions), _technology, _r, _non_trivial, _all_steps, _no_replication,
                  _lexicographical_step, _lexicographical_op, _ordered_symmetric) {}

exact::SSV::SSV(const std::vector<std::string> &functions, const exact::Technology &_technology, int _r,
                bool _non_trivial, bool _all_steps,
                bool _no_replication, bool _lexicographical_step, bool _lexicographical_op, bool _ordered_symmetric)
        : Encoder(functions, _technology, _r, _non_trivial, _all_steps, _no_replication,
                  _lexicographical_step, _lexicographical_op, _ordered_symmetric) {}

exact::SSV::SSV(const std::vector<std::string> &functions)
        : Encoder(functions, exact::Technology(), 0, false, false, false, false, false, false) {}

exact::SSV::SSV(std::vector<Boolean> functions)
        : Encoder(std::move(functions), exact::Technology(), 0, false, false, false, false, false, false) {}

void exact::SSV::decode(std::vector<int> input, std::string output_file) {
    int r = this->r, max_t =
            (1 << (functions[0].num_bits)) - 1, m = (int) functions.size(), n = functions[0].num_bits;
    std::map<std::string, int> variable_index = generate_variable_index(n, r, max_t, m);
    std::ofstream fout(output_file);
    assert(fout.is_open());

    std::map<int, bool> variable_assignment;
    for(auto& temp: input) {
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
        for (int k = 1; k < i; k++) {
            for (int j = 1; j < k; j++) {
                if (variable_assignment[variable_index["s" + std::to_string(i) + std::to_string(j) +
                                                       std::to_string(k)]]) {
                    fout << ".names x" << j << " x" << k << " x" << i << "\n";
                    // output xx 1 format, can be modified to xx 0 format
                    if (variable_assignment[variable_index["f" + std::to_string(i) + "01"]])
                        fout << ".01 1\n";
                    if (variable_assignment[variable_index["f" + std::to_string(i) + "10"]])
                        fout << ".10 1\n";
                    if (variable_assignment[variable_index["f" + std::to_string(i) + "11"]])
                        fout << ".11 1\n";
                }
            }
        }
    }
    fout << ".end\n";
}


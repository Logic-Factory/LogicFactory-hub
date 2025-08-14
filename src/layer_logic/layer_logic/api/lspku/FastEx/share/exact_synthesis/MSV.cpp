//
// Created by zephyr on 2023/2/18.
//

#include <utility>

#include "exact.h"

void exact::MSV::add_non_trivial(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int i = initial_i; i < initial_i + r; i++) {
        int fi01 = variable_index["f" + std::to_string(i) + "01"];
        int fi10 = variable_index["f" + std::to_string(i) + "10"];
        int fi11 = variable_index["f" + std::to_string(i) + "11"];
        result.add_clause(std::vector<int>{fi01, fi10, fi11});
        result.add_clause(std::vector<int>{fi01, -fi10, -fi11});
        result.add_clause(std::vector<int>{-fi01, fi10, -fi11});
    }
}

void exact::MSV::add_all_steps(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    int m = int(functions.size());
    for (int i = initial_i; i < initial_i + r; i++) {
        std::vector<int> temp{};
        for (int k = 1; k <= m; k++) {
            temp.emplace_back(variable_index["g" + std::to_string(i) + std::to_string(k)]);
        }
        for (int _i = i + 1; _i < initial_i + r; _i++) {
            if (_i > n && _i < initial_i) continue;
            temp.emplace_back(variable_index["s" + std::to_string(_i) + std::to_string(i)]);
        }
        result.add_clause(temp);
    }
}

void exact::MSV::add_no_replication(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int i = initial_i; i < initial_i + r; i++) {
        for (int _i = i + 1; _i < initial_i + r; _i++) {
            for (int k = 1; k < i; k++) {
                if (k > n && k < initial_i) continue;
                for (int j = 1; j < k; j++) {
                    if (j > n && j < initial_i) continue;
                    int sij = variable_index["s" + std::to_string(i) + std::to_string(j)];
                    int sik = variable_index["s" + std::to_string(i) + std::to_string(k)];
                    int s_ij = variable_index["s" + std::to_string(_i) + std::to_string(j)];
                    int s_ik = variable_index["s" + std::to_string(_i) + std::to_string(k)];
                    int s_ii = variable_index["s" + std::to_string(_i) + std::to_string(i)];
                    result.add_clause(std::vector<int>{-sij, -sik, -s_ii, -s_ij});
                    result.add_clause(std::vector<int>{-sij, -sik, -s_ii, -s_ik});
                }
            }
        }
    }
}

void exact::MSV::add_lexicographical_step(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int i = initial_i; i < initial_i + r - 1; i++) {
        int _i = i + 1;
        for (int k = 1; k < i; k++) {
            if (k > n && k < initial_i) continue;
            for (int _k = 1; _k < _i; _k++) {
                if (_k > n && _k < initial_i) continue;
                for (int j = 1; j < k; j++) {
                    if (j > n && j < initial_i) continue;
                    for (int _j = 1; _j < _k; _j++) {
                        if (_j > n && _j < initial_i) continue;
                        int sij = variable_index["s" + std::to_string(i) + std::to_string(j)];
                        int sik = variable_index["s" + std::to_string(i) + std::to_string(k)];
                        int s_i_j = variable_index["s" + std::to_string(_i) + std::to_string(_j)];
                        int s_i_k = variable_index["s" + std::to_string(_i) + std::to_string(_k)];
                        if ((_j < j && k == _k) || _k < k) {
                            result.add_clause(std::vector<int>{-sij, -sik, -s_i_j, -s_i_k});
                        }
                    }
                }
            }
        }
    }
}

void exact::MSV::add_lexicographical_op(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
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
                int sij = variable_index["s" + std::to_string(i) + std::to_string(j)];
                int s_ij = variable_index["s" + std::to_string(_i) + std::to_string(j)];
                int sik = variable_index["s" + std::to_string(i) + std::to_string(k)];
                int s_ik = variable_index["s" + std::to_string(_i) + std::to_string(k)];
                result.add_clause(std::vector<int>{fi01, fi10, fi11, -sij, -s_ij, -sik, -s_ik});
                //000 < everything
                //result.add_clause(std::vector<int>{f_i01, f_i10, f_i11, fi01, fi10, -fi11, -sijk, -s_ijk});
                //001 only > 000, is contained by clause1
                //result.add_clause(std::vector<int>{f_i01, f_i10, f_i11, fi01, -fi10, fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, f_i10, -f_i11, fi01, -fi10, fi11, -sij, -s_ij, -sik, -s_ik});
                //010 > 000(contained by clause1) && 010 > 001
                //result.add_clause(std::vector<int>{f_i01, f_i10, f_i11, fi01, -fi10, -fi11, -sijk, -s_ijk});
                result.add_clause(std::vector<int>{f_i01, f_i10, -f_i11, fi01, -fi10, -fi11, -sij, -s_ij, -sik, -s_ik});
                result.add_clause(std::vector<int>{f_i01, -f_i10, f_i11, fi01, -fi10, -fi11, -sij, -s_ij, -sik, -s_ik});
                //011 > 000(contained by clause 1) && 011 > 001 && 011 > 010
                result.add_clause(std::vector<int>{f_i01, f_i10, -f_i11, -fi01, fi10, fi11, -sij, -s_ij, -sik, -s_ik});
                result.add_clause(std::vector<int>{f_i01, -f_i10, f_i11, -fi01, fi10, fi11, -sij, -s_ij, -sik, -s_ik});
                result.add_clause(std::vector<int>{f_i01, -f_i10, -f_i11, -fi01, fi10, fi11, -sij, -s_ij, -sik, -s_ik});
                //100 > 000(contained by clause1)/001/010/011
                result.add_clause(std::vector<int>{f_i01, f_i10, -f_i11, -fi01, fi10, -fi11, -sij, -s_ij, -sik, -s_ik});
                result.add_clause(std::vector<int>{f_i01, -f_i10, f_i11, -fi01, fi10, -fi11, -sij, -s_ij, -sik, -s_ik});
                result.add_clause(
                        std::vector<int>{f_i01, -f_i10, -f_i11, -fi01, fi10, -fi11, -sij, -s_ij, -sik, -s_ik});
                result.add_clause(std::vector<int>{-f_i01, f_i10, f_i11, -fi01, fi10, -fi11, -sij, -s_ij, -sik, -s_ik});
                //101 > 000/001/010/011/100
                result.add_clause(std::vector<int>{f_i01, f_i10, -f_i11, -fi01, -fi10, fi11, -sij, -s_ij, -sik, -s_ik});
                result.add_clause(std::vector<int>{f_i01, -f_i10, f_i11, -fi01, -fi10, fi11, -sij, -s_ij, -sik, -s_ik});
                result.add_clause(
                        std::vector<int>{f_i01, -f_i10, -f_i11, -fi01, -fi10, fi11, -sij, -s_ij, -sik, -s_ik});
                result.add_clause(std::vector<int>{-f_i01, f_i10, f_i11, -fi01, -fi10, fi11, -sij, -s_ij, -sik, -s_ik});
                result.add_clause(
                        std::vector<int>{-f_i01, f_i10, -f_i11, -fi01, -fi10, fi11, -sij, -s_ij, -sik, -s_ik});
                //110 > 000/001/010/011/100/101
                result.add_clause(std::vector<int>{-fi01, -fi10, -fi11, -sij, -s_ij, -sik, -s_ik});
                //111 > everything
            }
        }
    }
}

void exact::MSV::add_ordered_symmetric(std::map<std::string, int> &variable_index, exact::Encoding &result, int n) {
    for (int q = 0; q < functions[0].num_bits; q++) {
        for (int p = 0; p < q; p++) {
            if (!is_symmetric(functions, p, q))
                continue;
            int index_p = p + 1, index_q = q + 1;
            for (int i = initial_i; i < initial_i + r; i++) {
                std::vector<int> temp{
                        -variable_index["s" + std::to_string(i) + std::to_string(index_q)]};
                for (int _i = initial_i; _i < i; _i++) {
                    for (int _j = 1; _j < _i; _j++) {
                        if (_j > n && _j < initial_i) continue;
                        if (_j == index_p) {
                            int s_i_j = variable_index["s" + std::to_string(_i) + std::to_string(_j)];
                            temp.emplace_back(s_i_j);
                        }
                    }
                }
                if (temp.size() > 1)
                    result.add_clause(temp);
            }
        }
    }
}

std::map<std::string, int> exact::MSV::generate_variable_index(int n, int r, int max_t, int m) {
    int index = 1;
    std::map<std::string, int> variable_index;
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int t = 1; t <= max_t; t++)
            variable_index["x" + std::to_string(i) + std::to_string(t)] = index++;
    for (unsigned int i = initial_i; i < initial_i + r; i++)
        for (int h = 1; h <= m; h++)
            variable_index["g" + std::to_string(i) + std::to_string(h)] = index++;
    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        for (int j = 1; j < i; j++) {
            if (j > n && j < initial_i) continue;
            variable_index["s" + std::to_string(i) + std::to_string(j)] = index++;
        }
    }
    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        variable_index["f" + std::to_string(i) + "11"] = index++;
        variable_index["f" + std::to_string(i) + "10"] = index++;
        variable_index["f" + std::to_string(i) + "01"] = index++;
    }
    return variable_index;
}

exact::Encoding exact::MSV::encode(bool mark_variable) {
    int r = this->r, max_t =
            (1 << (functions[0].num_bits)) - 1, m = (int) functions.size(), n = functions[0].num_bits;
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

exact::MSV::MSV(std::vector<Boolean> functions, const exact::Technology &_technology, int _r, bool _non_trivial,
                bool _all_steps,
                bool _no_replication, bool _lexicographical_step, bool _lexicographical_op, bool _ordered_symmetric)
        : Encoder(std::move(functions), _technology, _r, _non_trivial, _all_steps, _no_replication,
                  _lexicographical_step, _lexicographical_op, _ordered_symmetric) {}

exact::MSV::MSV(const std::vector<std::string> &functions, const exact::Technology &_technology, int _r,
                bool _non_trivial, bool _all_steps,
                bool _no_replication, bool _lexicographical_step, bool _lexicographical_op, bool _ordered_symmetric)
        : Encoder(functions, _technology, _r, _non_trivial, _all_steps, _no_replication, _lexicographical_step,
                  _lexicographical_op, _ordered_symmetric) {}

exact::MSV::MSV(const std::vector<std::string> &functions)
        : Encoder(functions, exact::Technology(), 0, false, false, false, false, false, false) {}

exact::MSV::MSV(std::vector<Boolean> functions)
        : Encoder(std::move(functions), exact::Technology(), 0, false, false, false, false, false, false) {}

void exact::MSV::decode(std::vector<int> input, std::string output_file) {
    int r = this->r, max_t =
            (1 << (functions[0].num_bits)) - 1, m = (int) functions.size(), n = functions[0].num_bits;
    std::map<std::string, int> variable_index = generate_variable_index(n, r, max_t, m);
    std::ofstream fout(output_file);
    assert(fout.is_open());

    std::map<int, bool> variable_assignment;
    for(auto& temp: input){
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
        int count = 0;
        for (int j = 1; j < i; j++) {
            if (j > n && j < initial_i) continue;
            if (variable_assignment[variable_index["s" + std::to_string(i) + std::to_string(j)]]) {
                fout << "x" << j;
                count++;
                if (count <= 2)
                    fout << " ";
                else
                    assert(false);
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
exact::MSV::generate_clauses(std::map<std::string, int> &variable_index, int n, int r, int max_t, int m) {
    Encoding result;

    for (unsigned int i = initial_i; i < initial_i + r; i++) {
        int fi11 = variable_index["f" + std::to_string(i) + "11"];
        int fi10 = variable_index["f" + std::to_string(i) + "10"];
        int fi01 = variable_index["f" + std::to_string(i) + "01"];
        for (int k = 1; k < i; k++) {
            if (k > n && k < initial_i) continue;
            for (int j = 1; j < k; j++) {
                if (j > n && j < initial_i) continue;
                int sij = variable_index["s" + std::to_string(i) + std::to_string(j)];
                int sik = variable_index["s" + std::to_string(i) + std::to_string(k)];
                for (int t = 1; t <= max_t; t++) {
                    int xit = variable_index["x" + std::to_string(i) + std::to_string(t)];
                    if (j <= n && k <= n) {
                        int xjt = pi_tt[j][t], xkt = pi_tt[k][t];// 0 xit, -fi01 ^ 0 -xit fi01
                        if (xjt == 0 && xkt == 1)
                            result.add_clause(std::vector<int>{-sij, -sik, xit, -fi01}); //jk->i 01 0
                        if (xjt == 1 && xkt == 0)
                            result.add_clause(std::vector<int>{-sij, -sik, xit, -fi10}); //jk->i 10 0
                        if (xjt == 1 && xkt == 1)
                            result.add_clause(std::vector<int>{-sij, -sik, xit, -fi11}); //jk->i 11 0
                        if (xjt == 0 && xkt == 1)
                            result.add_clause(std::vector<int>{-sij, -sik, -xit, fi01}); //jk->i 01 1
                        if (xjt == 1 && xkt == 0)
                            result.add_clause(std::vector<int>{-sij, -sik, -xit, fi10}); //jk->i 10 1
                        if (xjt == 1 && xkt == 1)
                            result.add_clause(std::vector<int>{-sij, -sik, -xit, fi11}); //jk->i 11 1
                        if (xjt == 0 && xkt == 0) result.add_clause(std::vector<int>{-sij, -sik, -xit}); //avoid 00 1
                        continue;
                    }
                    if (j <= n) {
                        int xjt = pi_tt[j][t], xkt = variable_index["x" + std::to_string(k) + std::to_string(t)];
                        if (xjt == 0) result.add_clause(std::vector<int>{-sij, -sik, xit, -xkt, -fi01}); //jk->i 01 0
                        if (xjt == 1) result.add_clause(std::vector<int>{-sij, -sik, xit, xkt, -fi10}); //jk->i 10 0
                        if (xjt == 1) result.add_clause(std::vector<int>{-sij, -sik, xit, -xkt, -fi11}); //jk->i 11 0
                        if (xjt == 0) result.add_clause(std::vector<int>{-sij, -sik, -xit, -xkt, fi01}); //jk->i 01 1
                        if (xjt == 1) result.add_clause(std::vector<int>{-sij, -sik, -xit, xkt, fi10}); //jk->i 10 1
                        if (xjt == 1) result.add_clause(std::vector<int>{-sij, -sik, -xit, -xkt, fi11}); //jk->i 11 1
                        if (xjt == 0) result.add_clause(std::vector<int>{-sij, -sik, -xit, xkt}); //avoid 00 1
                        continue;
                    } else {
                        int xjt = variable_index["x" + std::to_string(j) + std::to_string(t)];
                        int xkt = variable_index["x" + std::to_string(k) + std::to_string(t)];
                        result.add_clause(std::vector<int>{-sij, -sik, xit, xjt, -xkt, -fi01}); //jk->i 01 0
                        result.add_clause(std::vector<int>{-sij, -sik, xit, -xjt, xkt, -fi10}); //jk->i 10 0
                        result.add_clause(std::vector<int>{-sij, -sik, xit, -xjt, -xkt, -fi11}); //jk->i 11 0
                        result.add_clause(std::vector<int>{-sij, -sik, -xit, xjt, -xkt, fi01}); //jk->i 01 1
                        result.add_clause(std::vector<int>{-sij, -sik, -xit, -xjt, xkt, fi10}); //jk->i 10 1
                        result.add_clause(std::vector<int>{-sij, -sik, -xit, -xjt, -xkt, fi11}); //jk->i 11 1
                        result.add_clause(std::vector<int>{-sij, -sik, -xit, xjt, xkt}); //avoid 00 1
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

    // TODO: add enhanced cardinality constraints
    for (int i = initial_i; i < initial_i + r; i++) {
        for (int l = 1; l < i; l++) {
            if (l > n && l < initial_i) continue;
            int sil = variable_index["s" + std::to_string(i) + std::to_string(l)];
            for (int k = 1; k < l; k++) {
                if (k > n && k < initial_i) continue;
                int sik = variable_index["s" + std::to_string(i) + std::to_string(k)];
                for (int j = 1; j < k; j++) {
                    if (j > n && j < initial_i) continue;
                    int sij = variable_index["s" + std::to_string(i) + std::to_string(j)];
                    result.add_clause(std::vector<int>{-sij, -sik, -sil});
                }
            }
            std::vector<int> temp;
            for (int k = 1; k < l; k++) {
                if (k > n && k < initial_i) continue;
                temp.emplace_back(variable_index["s" + std::to_string(i) + std::to_string(k)]);
            }
            for (int k = l + 1; k < i; k++) {
                if (k > n && k < initial_i) continue;
                temp.emplace_back(variable_index["s" + std::to_string(i) + std::to_string(k)]);
            }
            result.add_clause(temp);
        }
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

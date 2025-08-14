//
// Created by Jiaxi Zhang on 2022/5/18.
// Modified by zephyr on 2023/3/30.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <tuple>
#include <cassert>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>
#include "utility.h"

using namespace std;

////////////////////////////////////////////////////  memory manager

Truthtable_Manager_t *Truthtable_Manager_Alloc(int size) {
    uint32_t i = 0;
    Truthtable_Manager_t *p = (Truthtable_Manager_t *) malloc(sizeof(Truthtable_Manager_t));
    p->nFuncs = size;
    p->pFuncs = (uint64_t **) malloc(sizeof(uint64_t *) * size);
    for (i = 0; i < p->nFuncs; ++i) {
        p->pFuncs[i] = (uint64_t *) malloc(sizeof(uint64_t) * D_BLOCKS);
        memset(p->pFuncs[i], 0u, sizeof(uint64_t) * D_BLOCKS);
    }
    return p;
}

void Truthtable_Manager_Free(Truthtable_Manager_t *store) {
    uint32_t i = 0;
    for (i = 0; i < store->nFuncs; ++i) {
        free(store->pFuncs[i]);
    }
    free(store->pFuncs);
}

void print_truthtables(Truthtable_Manager_t *store) {
    uint32_t i = 0, j = 0;
    printf("Print truthtable store:\n");
    printf("\tnVars       :   %d\n", D_VARS);
    printf("\tnBits       :   %d\n", D_BITS);
    printf("\tnBlocks     :   %d\n", D_BLOCKS);
    printf("\tnInfluence  :   %d\n", D_INFLUENCE);
    printf("\tnCofactor   :   %d\n", D_COFACTOR);
    printf("\tnCofactor2  :   %d\n", D_COFACTOR2);
    printf("\tnSensitivity:   %d\n", D_SENSITIVITY);
    printf("\tnFuncs      :   %d\n", store->nFuncs);
    printf("\tpartial truth tables:\n");
    for (i = store->nFuncs - 1; i > store->nFuncs - 7; --i) {
        printf("\t\t");
        for (j = 0; j < D_BITS; ++j) {
            printf("%d", GET_BIT(store->pFuncs[i], j));
        }
        printf("\n");
    }
}

void print_signature(Signature_Manager_t sig) {
    uint32_t i = 0;
    printf("Sinatures of a truth table:\n");
    printf("\tindex           :%d\n", sig.index);
    printf("\tminterm         :%d\n", sig.minterm);
    printf("\tinfluence       :");
    for (i = 0; i < D_VARS; ++i) {
        printf("\t\t%d,", sig.influence[i]);
    }
    printf("\n");
    printf("\tsensiticity_1   :");
    for (i = 0; i < D_SENSITIVITY; ++i) {
        printf("\t\t%d,", sig.sensitivity_one[i]);
    }
    printf("\n");
    printf("\tsensiticity_0   :");
    for (i = 0; i < D_SENSITIVITY; ++i) {
        printf("\t\t%d,", sig.sensitivity_zero[i]);
    }
    printf("\n");
    printf("\tcofactor        :");
    for (i = 0; i < D_COFACTOR; ++i) {
        printf("\t\t%d,", sig.cofactor[i]);
    }
    printf("\n");
    printf("\tcofactor2       :");
    for (i = 0; i < D_COFACTOR2; ++i) {
        printf("\t\t%d,", sig.cofactor2[i]);
    }
    printf("\n");
}

void output_signature(Signature_Manager_t sig, std::ostream &out) {
    uint32_t i = 0;
    //out<<sig.index<<" ";
    for (i = 0; i < D_VARS; ++i) {
        out << sig.influence[i] << " ";
    }
    for (i = 0; i < D_SENSITIVITY; ++i) {
        out << sig.sensitivity_one[i] << " ";
    }
    for (i = 0; i < D_SENSITIVITY; ++i) {
        out << sig.sensitivity_zero[i] << " ";
    }
    for (i = 0; i < D_COFACTOR; ++i) {
        out << sig.cofactor[i] << " ";
    }
    for (i = 0; i < D_COFACTOR2; ++i) {
        out << sig.cofactor2[i] << " ";
    }
    out << std::endl;
}

bool Signature_Manager_t::operator<(const Signature_Manager_t &other) const {
    if (minterm < other.minterm) return 1;
    if (minterm > other.minterm) return 0;
    uint32_t i = 0;
    for (i = 0; i < D_VARS; ++i) {
        if (influence[i] > other.influence[i]) return 1;
        if (influence[i] < other.influence[i]) return 0;
    }
    for (i = 0; i < D_COFACTOR; ++i) {
        if (cofactor[i] > other.cofactor[i]) return 1;
        if (cofactor[i] < other.cofactor[i]) return 0;
    }
    for (i = 0; i < D_SENSITIVITY; ++i) {
        if (sensitivity_one[i] > other.sensitivity_one[i]) return 1;
        if (sensitivity_one[i] < other.sensitivity_one[i]) return 0;
    }
    for (i = 0; i < D_SENSITIVITY; ++i) {
        if (sensitivity_zero[i] > other.sensitivity_zero[i]) return 1;
        if (sensitivity_zero[i] < other.sensitivity_zero[i]) return 0;
    }
    for (i = 0; i < D_COFACTOR2; ++i) {
        if (cofactor2[i] > other.cofactor2[i]) return 1;
        if (cofactor2[i] < other.cofactor2[i]) return 0;
    }
    return 0;
}

void Signature_Manager_t::reset() {
    minterm = 0;
    std::fill(influence.begin(), influence.end(), 0u);
    std::fill(cofactor.begin(), cofactor.end(), 0u);
    std::fill(cofactor2.begin(), cofactor2.end(), 0u);
    std::fill(sensitivity_one.begin(), sensitivity_one.end(), 0u);
    std::fill(sensitivity_zero.begin(), sensitivity_zero.end(), 0u);
}

////  2^p = x, return p
int log2(unsigned int x) {
    static const unsigned char log_2[256] = {
            0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
    };
    int l = -1;
    while (x >= 256) {
        l += 8;
        x >>= 8;
    }
    return l + log_2[x];
}

// bit operations
static inline int get_bit(uint64_t *p, int i) {
    return (int) (p[i >> 6] >> (i & 63)) & 1;
}


static void set_bit(uint64_t *p, int i) {
    p[i >> 6] |= (1ul << (i & 63));
}

static void clear_bit(uint64_t *p, int i) {
    p[i >> 6] &= ~(1ul << (i & 63));
}

static void xor_bit(uint64_t *p, int i) {
    p[i >> 6] ^= (1ul << (i & 63));
}

static inline int count_ones(uint64_t x) {
    x = x - ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    x = x + (x >> 32);
    return (int) (x & 0xFF);
}

static inline int count_ones_2(uint64_t p) {
    return p ? count_ones(p) : 0;
}

static inline int count_ones_vec(uint64_t *p, int block) {
    int b = 0, count = 0;
    for (b = 0; b < block; ++b) {
        count += count_ones_2(p[b]);
    }
    return count;
}


static inline void negate_ones(uint64_t &p) {
    p ^= 0xffffffffffffffff;
}

static void negate_vec(uint64_t *p, int block) {
    for (int i = 0; i < block; ++i) {
        negate_ones(p[i]);
    }
}

static uint64_t bitmask[6] = {
        0x5555555555555555,
        0x3333333333333333,
        0x0F0F0F0F0F0F0F0F,
        0x00FF00FF00FF00FF,
        0x0000FFFF0000FFFF,
        0x00000000FFFFFFFF
};

static constexpr uint64_t bitmask_influence[6] = {
        0x5555555555555555,
        0x3333333333333333,
        0x0f0f0f0f0f0f0f0f,
        0x00ff00ff00ff00ff,
        0x0000ffff0000ffff,
        0x00000000ffffffff
};

auto compute_mask_influence(uint64_t numVar) {
    uint64_t block_size = 1u;
    if (numVar >= 6) {
        block_size = 1 << (numVar - 6);
    }

    uint64_t truth_table_size = 1 << numVar;
    vector<vector<uint64_t>> mask_influ(numVar, vector<uint64_t>(block_size, 0u));

    uint64_t block = 0u;
    uint64_t offset = 0u;
    for (uint64_t i = 0u; i < numVar; ++i) {
        for (uint64_t j = 0u; j < truth_table_size; ++j) {
            if ((j >> i & 1) == 0) {
                block = j / 64;
                offset = j % 64;
                mask_influ[i][block_size - 1 - block] |= (1ul << offset); // 使用1ul解决64移位溢出的问题
            }
        }
    }

    return mask_influ;
}


auto compute_mask_cofactor(uint64_t numVar) {
    uint64_t block_size = 1u;
    if (numVar >= 6) {
        block_size = 1 << (numVar - 6);
    }
    uint64_t truth_table_size = 1 << numVar;
    vector<vector<uint64_t>> mask_cofa(2 * numVar, vector<uint64_t>(block_size, 0u));

    uint64_t block = 0u;
    uint64_t offset = 0u;
    for (uint64_t i = 0u; i < numVar; ++i) {
        for (uint64_t j = 0u; j < truth_table_size; ++j) {
            block = j / 64;
            offset = j % 64;
            if ((j >> i & 1) == 0) {
                mask_cofa[i][block_size - 1 - block] |= (1ul << offset);
            } else {
                mask_cofa[i + numVar][block] |= (1ul << offset);
            }
        }
    }
    for (uint64_t i = numVar + 6; i < 2 * numVar; ++i) {
        for (uint64_t j = 0; j < block_size; ++j) {
            mask_cofa[i][j] = ~mask_cofa[i][j];
        }
    }

    return mask_cofa;
}


auto compute_mask_cofactor2(uint64_t numVar) {
    uint64_t block_size = 1u;
    if (numVar >= 6) {
        block_size = 1 << (numVar - 6);
    }
    uint64_t truth_table_size = 1 << numVar;
    vector<vector<uint64_t>> mask_cofa_pairwise(2 * numVar * (numVar - 1), vector<uint64_t>(block_size, 0u));

    uint64_t base = numVar * (numVar - 1) / 2;
    uint64_t value = 0u;
    uint64_t new_pos = 0u;
    uint64_t block = 0u;
    uint64_t offset = 0u;

    uint64_t i = 0u;
    uint64_t j = 0u;
    for (i = 0u; i < truth_table_size; ++i) {
        for (j = 0u; j < numVar; ++j) {
            for (uint64_t k = j + 1; k < numVar; ++k) {
                block = i / 64;
                offset = i % 64;

                value = i >> j & 1;           // first pos
                value += (i >> k & 1) << 1;   // second pos
                new_pos = (2 * numVar - 1 - j) * j / 2 + k - j - 1;

                mask_cofa_pairwise[value * base + new_pos][block] |= (1ul << offset);
            }
        }
    }

    vector<vector<uint64_t>> mask_cofa_pairwise_res(2 * numVar * (numVar - 1), vector<uint64_t>(block_size, 0u));

    int gap = numVar * (numVar - 1) / 2;
    int tmp_index = 0;
    vector<uint64_t> vec_base(4);
    for (i = 0; i < 4; ++i) {
        vec_base[i] = i * gap;
    }
    for (i = 0; i < gap; ++i) {
        for (j = 0; j < 4; ++j) {
            for (int k = 0; k < block_size; ++k) {
                mask_cofa_pairwise_res[tmp_index][k] = mask_cofa_pairwise[vec_base[j] + i][k];
            }
            tmp_index++;
        }
    }

    return mask_cofa_pairwise;
}

auto compute_mask_sensitivity(uint64_t numVar) {
    uint64_t block_size = 1u;
    if (numVar >= 6) {
        block_size = 1 << (numVar - 6);
    }
    uint64_t truth_table_size = 1 << numVar;
    vector<vector<uint64_t>> mask_sensitivity(truth_table_size, vector<uint64_t>(block_size, 0u));

    uint64_t block = 0u;
    uint64_t offset = 0u;
    for (uint64_t i = 0u; i < truth_table_size; ++i) {
        for (uint64_t j = 0u; j < truth_table_size; ++j) {
            if (count_ones_2(i ^ j) == 1)    // distance is one
            {
                block = j / 64;
                offset = j % 64;
                // mask_sensitivity[i][block_size-1-block] |= (1ul << offset);
                mask_sensitivity[i][block] |= (1ul << offset);
            }
        }
    }

    return mask_sensitivity;
}

const map<char, string> db_hex_2_binary = {
        {'0', "0000"},
        {'1', "0001"},
        {'2', "0010"},
        {'3', "0011"},
        {'4', "0100"},
        {'5', "0101"},
        {'6', "0110"},
        {'7', "0111"},
        {'8', "1000"},
        {'9', "1001"},
        {'a', "1010"},
        {'b', "1011"},
        {'c', "1100"},
        {'d', "1101"},
        {'e', "1110"},
        {'f', "1111"},
        {'A', "1010"},
        {'B', "1011"},
        {'C', "1100"},
        {'D', "1101"},
        {'E', "1110"},
        {'F', "1111"}
};

const map<char, int> db_hex_ones = {
        {'0', 0},
        {'1', 1},
        {'2', 1},
        {'3', 2},
        {'4', 1},
        {'5', 2},
        {'6', 2},
        {'7', 3},
        {'8', 1},
        {'9', 2},
        {'a', 2},
        {'b', 3},
        {'c', 2},
        {'d', 3},
        {'e', 3},
        {'f', 4},
        {'A', 2},
        {'B', 3},
        {'C', 2},
        {'D', 3},
        {'E', 3},
        {'F', 4}
};

const map<char, string> db_hex_2_binary_negation = {
        {'0', "1111"},
        {'1', "1110"},
        {'2', "1101"},
        {'3', "1100"},
        {'4', "1011"},
        {'5', "1010"},
        {'6', "1001"},
        {'7', "1000"},
        {'8', "0111"},
        {'9', "0110"},
        {'a', "0101"},
        {'b', "0100"},
        {'c', "0011"},
        {'d', "0010"},
        {'e', "0001"},
        {'f', "0000"},
        {'A', "0101"},
        {'B', "0100"},
        {'C', "0011"},
        {'D', "0010"},
        {'E', "0001"},
        {'F', "0000"}
};
const map<char, char> db_hex_2_hex_negation = {
        {'0', 'f'},
        {'1', 'e'},
        {'2', 'd'},
        {'3', 'c'},
        {'4', 'b'},
        {'5', 'a'},
        {'6', '9'},
        {'7', '8'},
        {'8', '7'},
        {'9', '6'},
        {'a', '5'},
        {'b', '4'},
        {'c', '3'},
        {'d', '2'},
        {'e', '1'},
        {'f', '0'},
        {'A', '5'},
        {'B', '4'},
        {'C', '3'},
        {'D', '2'},
        {'E', '1'},
        {'F', '0'}
};

int count_oens_hex(const string &str) {
    int count = 0;
    uint32_t i = 0;
    for (i = 0; i < str.size(); ++i) {
        count += db_hex_ones.at(str[i]);
    }
    return count;
}

/**
 * @brief filter the data , then get the length of a line ,and all the unique tts
 *
 * @param file
 * @return tuple<uint32_t, set<string>> length of a line, tts
 */
tuple<uint32_t, set<string>> filter_data_hex(const string &file) {
    uint32_t i = 0;
    uint32_t length = 0;
    set<string> se;

    std::ifstream infile;
    infile.open(file, ios::in);
    if (infile.fail()) {
        std::cerr << "Open file error at " << file << endl;
        return make_tuple(length, se);
    }

    int count_ones = 0;

    string tmp_line;
    string tmp_line2;
    while (getline(infile, tmp_line)) {
        /// compute length of a line
        if (length != 0) {
            if (length != tmp_line.size()) {
                printf("%d, %ld\t", length, tmp_line.size());
                cout << "\n" << tmp_line << endl;
            }
            assert(length == tmp_line.size());
        } else {
            length = tmp_line.size();
            assert((length & (length - 1)) == 0); //检查其是2的幂次方
        }

        /// compute_if negate a line ,then insert into set
        count_ones = count_oens_hex(tmp_line);

        if (count_ones > tmp_line.size() * 2) {
            tmp_line2 = tmp_line;
            for (i = 0; i < tmp_line.size(); ++i) {
                tmp_line2[i] = db_hex_2_hex_negation.at(tmp_line[i]);
            }
            se.insert(tmp_line2);
        } else {
            se.insert(tmp_line);
        }
    }
    infile.close();

    return make_tuple(length, se);
}

/**
 * @brief load hex files to truthtable
 *
 * @param file
 * @return true
 * @return false
 */
bool load_truthtables_hex(Truthtable_Manager_t *store, const set<string> &set_tts) {
    uint32_t i = 0, j = 0;
    uint32_t index = 0;

    for (auto tt: set_tts) {
        assert((4 * tt.size()) == D_BITS);
        for (i = 0; i < tt.size(); ++i) {
            for (j = 0; j < 4; ++j) {
                if (db_hex_2_binary.at(tt[i])[j] == '1') {
                    SET_BIT(store->pFuncs[index], 4 * i + j);
                }
            }
        }
        index++;
    }

    return true;
}

void calculate_feature(const string &input, const string &output) {
    uint32_t i, j, k;
    uint8_t nvars;
    uint32_t nfuncs;

    /*
    double time_load_file = 0;
    double time_mask      = 0;
    double time_total_signature = 0;
    double time_influence = 0;
    double time_cofactor = 0;
    double time_sensitivity = 0;
    double time_cofactor2 = 0;
    double time_hash = 0;
     */
    std::ofstream out;
    out.open(output, ios::out | ios::app);
    if (out.fail()) {
        std::cerr << "Open file error at " << output << endl;
        assert(false);
    }

    //printf("Load truth tables from hex input!\n");
    Truthtable_Manager_t *store = nullptr;
    {
        auto length_tts = filter_data_hex(input);
        auto length = get<0>(length_tts);
        auto set_tts = get<1>(length_tts);

        nvars = log2(length) + 2;
        assert(nvars == (uint8_t) D_VARS);
        nfuncs = set_tts.size();
        store = Truthtable_Manager_Alloc(nfuncs);
        load_truthtables_hex(store, set_tts);
    }

    //printf("Compute mask for fast signature computation!\n");
    auto mask_influence = compute_mask_influence(D_VARS);
    auto mask_cofactor = compute_mask_cofactor(D_VARS);
    auto mask_cofactor2 = compute_mask_cofactor2(D_VARS);
    auto mask_sensitivity = compute_mask_sensitivity(D_VARS);

    //printf("Compute signatures from truthtable!\n");
    uint32_t sum = 0;
    /// set the dumys for reusing and alloc memory
    Signature_Manager_t dumy_sig;

    array<uint16_t, D_BITS> dumy_sensitivity_one{0u};
    array<uint16_t, D_BITS> dumy_sensitivity_zero{0u};
    array<uint16_t, D_COFACTOR2> dumy_cofactor2_1{0u};          // signatures中的cofactor2是 cofactor2_0

    array<uint16_t, 2 * D_SENSITIVITY> dumy_arr_sensi;

    array<uint16_t, D_INFLUENCE + D_COFACTOR> dumy_arr_inf_cof;
    array<uint16_t, D_INFLUENCE + D_COFACTOR + 2 * D_SENSITIVITY> dumy_arr_inf_cof_sensi;
    array<uint16_t, D_INFLUENCE + 2 * D_SENSITIVITY> dumy_arr_inf_sensi;
    array<uint16_t, D_COFACTOR + 2 * D_SENSITIVITY> dumy_arr_cof_sensi;
    array<uint16_t, D_COFACTOR + 2 * D_SENSITIVITY + D_COFACTOR2> dumy_arr_cof_sensi_cof2;

    // compute signatures of each truth table
    for (k = 0; k < store->nFuncs; ++k) {
        //printf("index: %d\n", k);
        string tts_str;
        for (i = 0; i < D_BITS; ++i) {
            (GET_BIT(store->pFuncs[k], i) == 1) ? tts_str.push_back('1') : tts_str.push_back('0');
        }
        //cout << "tts: " << tts_str << endl;

        fill(dumy_sensitivity_one.begin(), dumy_sensitivity_one.end(), 0u);
        fill(dumy_sensitivity_zero.begin(), dumy_sensitivity_zero.end(), 0u);
        fill(dumy_cofactor2_1.begin(), dumy_cofactor2_1.end(), 0u);

        dumy_sig.reset();

        dumy_sig.index = k;
        /// compute minterm
        dumy_sig.minterm = count_ones_vec(store->pFuncs[k], D_BLOCKS);
        /// compute sensitivity
        for (i = 0; i < D_BITS; ++i) {
            sum = 0;
            for (j = 0; j < D_BLOCKS; ++j) {
                sum += count_ones_2(mask_sensitivity[i][j] & store->pFuncs[k][j]);
            }
            (GET_BIT(store->pFuncs[k], i) == 1) ? (dumy_sensitivity_one[i] = D_VARS - sum, ++dumy_sig.sensitivity_one[
                    dumy_sensitivity_one[i] + 1], ++dumy_sig.sensitivity_zero[0]) :
            (dumy_sensitivity_zero[i] = sum, ++dumy_sig.sensitivity_zero[dumy_sensitivity_zero[i] +
                                                                         1], ++dumy_sig.sensitivity_one[0]);
        }
        /// compute influence, cofactor, cofactor2
        for (j = 0; j < D_BLOCKS; ++j) {
            for (i = 0; i < D_VARS; ++i) {
                dumy_sig.influence[i] += count_ones_2((mask_influence[i][j] & store->pFuncs[k][j]) ^
                                                      ((~mask_influence[i][j] & store->pFuncs[k][j]) >> (1 << i)));
                dumy_sig.cofactor[i] += count_ones_2(mask_cofactor[i][j] & store->pFuncs[k][j]);
                dumy_sig.cofactor[i + nvars] += count_ones_2(mask_cofactor[i + nvars][j] & store->pFuncs[k][j]);
            }
            for (i = 0; i < D_COFACTOR2; ++i) {
                dumy_sig.cofactor2[i] += count_ones_2(mask_cofactor2[i][j] & store->pFuncs[k][j]);
            }
        }

        //for (i = 0; i < D_BITS; ++i) {
        //    dumy_sig.sensitivity_one[i] = dumy_sensitivity_one[i];
        //    dumy_sig.sensitivity_zero[i] = dumy_sensitivity_zero[i];
        //}
        //sort(dumy_sig.sensitivity_zero.begin(), dumy_sig.sensitivity_zero.end());
        //sort(dumy_sig.sensitivity_one.begin(), dumy_sig.sensitivity_one.end());
        sort(dumy_sig.influence.begin(), dumy_sig.influence.end());
        sort(dumy_sig.cofactor.begin(), dumy_sig.cofactor.end());
        sort(dumy_sig.cofactor2.begin(), dumy_sig.cofactor2.end());


        int max_cof_2_boundry = D_BITS / 4;
        if (dumy_sig.minterm == D_BITS / 2) {
            /// xxx_one hold the min value
            if (dumy_sig.sensitivity_zero < dumy_sig.sensitivity_one) {
                cout << "minterm case: " << tts_str << endl;
                swap(dumy_sig.sensitivity_one, dumy_sig.sensitivity_zero);
            }

            for (i = 0; i < D_COFACTOR2; ++i) {
                dumy_cofactor2_1[i] = max_cof_2_boundry - dumy_sig.cofactor2[D_COFACTOR2 - i - 1];
            }
            sort(dumy_cofactor2_1.begin(), dumy_cofactor2_1.end());
            if (dumy_sig.cofactor2 < dumy_cofactor2_1) {
                swap(dumy_sig.cofactor2, dumy_cofactor2_1);
            }
        }

        //print_signature(dumy_sig);
        uint32_t _i = 0;
        //out<<dumy_sig.index<<" ";

        for (_i = 0; _i < D_VARS; ++_i) {
            out << dumy_sig.influence[_i] << " ";
        }
        for (auto s: dumy_sensitivity_one) {
            out << s << " ";
        }
        //for (auto s: dumy_sensitivity_zero)
        //{
        //    out<<s<<" ";
        //}
        for (_i = 0; _i < D_COFACTOR; ++_i) {
            out << dumy_sig.cofactor[_i] << " ";
        }
        //for(_i = 0 ; _i < D_COFACTOR2; ++_i)
        //{
        //    out<<dumy_sig.cofactor2[_i]<<" ";
        //}
        out << std::endl;
    }

    // free the truth tables
    Truthtable_Manager_Free(store);
    free(store);
}

void calculate_feature(std::string function, int *feature) {
    if (feature == nullptr) {
        std::cout << "No feature vector provided.\n";
        return;
    }

    uint32_t i, j;
    uint8_t nvars;
    uint32_t nfuncs;

    auto length = function.size();
    nvars = log2(length) + 2;
    assert(nvars == (uint8_t) D_VARS);
    auto pFunc = (uint64_t *) malloc(sizeof(uint64_t) * D_BLOCKS);
    {
        uint32_t _i = 0, _j = 0;
        uint32_t index = 0;
        assert((4 * function.size()) == D_BITS);
        for (_i = 0; _i < function.size(); ++_i) {
            for (_j = 0; _j < 4; ++_j) {
                if (db_hex_2_binary.at(function[_i])[_j] == '1') {
                    SET_BIT(pFunc, 4 * _i + _j);
                }
            }
        }
    }

    //printf("Compute mask for fast signature computation!\n");
    auto mask_influence = compute_mask_influence(D_VARS);
    auto mask_cofactor = compute_mask_cofactor(D_VARS);
    auto mask_cofactor2 = compute_mask_cofactor2(D_VARS);
    auto mask_sensitivity = compute_mask_sensitivity(D_VARS);
    uint32_t sum = 0;
    Signature_Manager_t dumy_sig;

    array<uint16_t, D_BITS> dumy_sensitivity_one{0u};
    array<uint16_t, D_BITS> dumy_sensitivity_zero{0u};
    array<uint16_t, D_COFACTOR2> dumy_cofactor2_1{0u};          // signatures中的cofactor2是 cofactor2_0

    array<uint16_t, 2 * D_SENSITIVITY> dumy_arr_sensi;

    array<uint16_t, D_INFLUENCE + D_COFACTOR> dumy_arr_inf_cof;
    array<uint16_t, D_INFLUENCE + D_COFACTOR + 2 * D_SENSITIVITY> dumy_arr_inf_cof_sensi;
    array<uint16_t, D_INFLUENCE + 2 * D_SENSITIVITY> dumy_arr_inf_sensi;
    array<uint16_t, D_COFACTOR + 2 * D_SENSITIVITY> dumy_arr_cof_sensi;
    array<uint16_t, D_COFACTOR + 2 * D_SENSITIVITY + D_COFACTOR2> dumy_arr_cof_sensi_cof2;

    // compute signatures of each truth table

    string tts_str;
    for (i = 0; i < D_BITS; ++i) {
        (GET_BIT(pFunc, i) == 1) ? tts_str.push_back('1') : tts_str.push_back('0');
    }

    fill(dumy_sensitivity_one.begin(), dumy_sensitivity_one.end(), 0u);
    fill(dumy_sensitivity_zero.begin(), dumy_sensitivity_zero.end(), 0u);
    fill(dumy_cofactor2_1.begin(), dumy_cofactor2_1.end(), 0u);

    dumy_sig.reset();

    dumy_sig.index = 0;
    /// compute minterm
    dumy_sig.minterm = count_ones_vec(pFunc, D_BLOCKS);
    /// compute sensitivity
    for (i = 0; i < D_BITS; ++i) {
        sum = 0;
        for (j = 0; j < D_BLOCKS; ++j) {
            sum += count_ones_2(mask_sensitivity[i][j] & pFunc[j]);
        }
        (GET_BIT(pFunc, i) == 1) ? (dumy_sensitivity_one[i] = D_VARS - sum, ++dumy_sig.sensitivity_one[
                dumy_sensitivity_one[i] + 1], ++dumy_sig.sensitivity_zero[0]) :
        (dumy_sensitivity_zero[i] = sum, ++dumy_sig.sensitivity_zero[dumy_sensitivity_zero[i] +
                                                                     1], ++dumy_sig.sensitivity_one[0]);
    }
    /// compute influence, cofactor, cofactor2
    for (j = 0; j < D_BLOCKS; ++j) {
        for (i = 0; i < D_VARS; ++i) {
            dumy_sig.influence[i] += count_ones_2((mask_influence[i][j] & pFunc[j]) ^
                                                  ((~mask_influence[i][j] & pFunc[j]) >> (1 << i)));
            dumy_sig.cofactor[i] += count_ones_2(mask_cofactor[i][j] & pFunc[j]);
            dumy_sig.cofactor[i + nvars] += count_ones_2(mask_cofactor[i + nvars][j] & pFunc[j]);
        }
        for (i = 0; i < D_COFACTOR2; ++i) {
            dumy_sig.cofactor2[i] += count_ones_2(mask_cofactor2[i][j] & pFunc[j]);
        }
    }

    sort(dumy_sig.influence.begin(), dumy_sig.influence.end());
    sort(dumy_sig.cofactor.begin(), dumy_sig.cofactor.end());
    sort(dumy_sig.cofactor2.begin(), dumy_sig.cofactor2.end());


    int max_cof_2_boundry = D_BITS / 4;
    if (dumy_sig.minterm == D_BITS / 2) {
        /// xxx_one hold the min value
        if (dumy_sig.sensitivity_zero < dumy_sig.sensitivity_one) {
            swap(dumy_sig.sensitivity_one, dumy_sig.sensitivity_zero);
        }

        for (i = 0; i < D_COFACTOR2; ++i) {
            dumy_cofactor2_1[i] = max_cof_2_boundry - dumy_sig.cofactor2[D_COFACTOR2 - i - 1];
        }
        sort(dumy_cofactor2_1.begin(), dumy_cofactor2_1.end());
        if (dumy_sig.cofactor2 < dumy_cofactor2_1) {
            swap(dumy_sig.cofactor2, dumy_cofactor2_1);
        }
    }

    int feature_index = 0;
    for (i = 0; i < D_VARS; ++i) {
        feature[feature_index++] = dumy_sig.influence[i];
    }
    for (auto s: dumy_sensitivity_one) {
        feature[feature_index++] = s;
    }
    for (auto s: dumy_sensitivity_zero) {
        feature[feature_index++] = s;
    }
    for (i = 0; i < D_COFACTOR; ++i) {
        feature[feature_index++] = dumy_sig.cofactor[i];
    }
    for (i = 0; i < D_COFACTOR2; ++i) {
        feature[feature_index++] = dumy_sig.cofactor2[i];
    }

    // free the truth table
    free(pFunc);
}

void calculate_feature(exact::Boolean &boolean, int *feature) {
    if (feature == nullptr) {
        std::cout << "No feature vector provided.\n";
        return;
    }

    uint32_t i, j;
    uint8_t nvars;
    uint32_t nfuncs;

    auto length = boolean.function.size();
    nvars = log2(length);
    assert(nvars == (uint8_t) D_VARS);
    auto pFunc = (uint64_t *) malloc(sizeof(uint64_t) * D_BLOCKS);
    {
        uint32_t _i = 0, _j = 0;
        uint32_t index = 0;
        assert((boolean.function.size()) == D_BITS);
        for (_i = 0; _i < boolean.function.size(); ++_i) {
            if (boolean.function[_i])
                SET_BIT(pFunc, _i);
        }
    }

    //printf("Compute mask for fast signature computation!\n");
    auto mask_influence = compute_mask_influence(D_VARS);
    auto mask_cofactor = compute_mask_cofactor(D_VARS);
    auto mask_cofactor2 = compute_mask_cofactor2(D_VARS);
    auto mask_sensitivity = compute_mask_sensitivity(D_VARS);
    uint32_t sum = 0;
    Signature_Manager_t dumy_sig;

    array<uint16_t, D_BITS> dumy_sensitivity_one{0u};
    array<uint16_t, D_BITS> dumy_sensitivity_zero{0u};
    array<uint16_t, D_COFACTOR2> dumy_cofactor2_1{0u};          // signatures中的cofactor2是 cofactor2_0

    array<uint16_t, 2 * D_SENSITIVITY> dumy_arr_sensi;

    array<uint16_t, D_INFLUENCE + D_COFACTOR> dumy_arr_inf_cof;
    array<uint16_t, D_INFLUENCE + D_COFACTOR + 2 * D_SENSITIVITY> dumy_arr_inf_cof_sensi;
    array<uint16_t, D_INFLUENCE + 2 * D_SENSITIVITY> dumy_arr_inf_sensi;
    array<uint16_t, D_COFACTOR + 2 * D_SENSITIVITY> dumy_arr_cof_sensi;
    array<uint16_t, D_COFACTOR + 2 * D_SENSITIVITY + D_COFACTOR2> dumy_arr_cof_sensi_cof2;

    // compute signatures of each truth table

    string tts_str;
    for (i = 0; i < D_BITS; ++i) {
        (GET_BIT(pFunc, i) == 1) ? tts_str.push_back('1') : tts_str.push_back('0');
    }

    fill(dumy_sensitivity_one.begin(), dumy_sensitivity_one.end(), 0u);
    fill(dumy_sensitivity_zero.begin(), dumy_sensitivity_zero.end(), 0u);
    fill(dumy_cofactor2_1.begin(), dumy_cofactor2_1.end(), 0u);

    dumy_sig.reset();

    dumy_sig.index = 0;
    /// compute minterm
    dumy_sig.minterm = count_ones_vec(pFunc, D_BLOCKS);
    /// compute sensitivity
    for (i = 0; i < D_BITS; ++i) {
        sum = 0;
        for (j = 0; j < D_BLOCKS; ++j) {
            sum += count_ones_2(mask_sensitivity[i][j] & pFunc[j]);
        }
        (GET_BIT(pFunc, i) == 1) ? (dumy_sensitivity_one[i] = D_VARS - sum, ++dumy_sig.sensitivity_one[
                dumy_sensitivity_one[i] + 1], ++dumy_sig.sensitivity_zero[0]) :
        (dumy_sensitivity_zero[i] = sum, ++dumy_sig.sensitivity_zero[dumy_sensitivity_zero[i] +
                                                                     1], ++dumy_sig.sensitivity_one[0]);
    }
    /// compute influence, cofactor, cofactor2
    for (j = 0; j < D_BLOCKS; ++j) {
        for (i = 0; i < D_VARS; ++i) {
            dumy_sig.influence[i] += count_ones_2((mask_influence[i][j] & pFunc[j]) ^
                                                  ((~mask_influence[i][j] & pFunc[j]) >> (1 << i)));
            dumy_sig.cofactor[i] += count_ones_2(mask_cofactor[i][j] & pFunc[j]);
            dumy_sig.cofactor[i + nvars] += count_ones_2(mask_cofactor[i + nvars][j] & pFunc[j]);
        }
        for (i = 0; i < D_COFACTOR2; ++i) {
            dumy_sig.cofactor2[i] += count_ones_2(mask_cofactor2[i][j] & pFunc[j]);
        }
    }

    sort(dumy_sig.influence.begin(), dumy_sig.influence.end());
    sort(dumy_sig.cofactor.begin(), dumy_sig.cofactor.end());
    sort(dumy_sig.cofactor2.begin(), dumy_sig.cofactor2.end());


    int max_cof_2_boundry = D_BITS / 4;
    if (dumy_sig.minterm == D_BITS / 2) {
        /// xxx_one hold the min value
        if (dumy_sig.sensitivity_zero < dumy_sig.sensitivity_one) {
            swap(dumy_sig.sensitivity_one, dumy_sig.sensitivity_zero);
        }

        for (i = 0; i < D_COFACTOR2; ++i) {
            dumy_cofactor2_1[i] = max_cof_2_boundry - dumy_sig.cofactor2[D_COFACTOR2 - i - 1];
        }
        sort(dumy_cofactor2_1.begin(), dumy_cofactor2_1.end());
        if (dumy_sig.cofactor2 < dumy_cofactor2_1) {
            swap(dumy_sig.cofactor2, dumy_cofactor2_1);
        }
    }

    int feature_index = 0;
    for (i = 0; i < D_VARS; ++i) {
        feature[feature_index++] = dumy_sig.influence[i];
    }
    for (auto s: dumy_sensitivity_one) {
        feature[feature_index++] = s;
    }
    for (auto s: dumy_sensitivity_zero) {
        feature[feature_index++] = s;
    }
    for (i = 0; i < D_COFACTOR; ++i) {
        feature[feature_index++] = dumy_sig.cofactor[i];
    }
    for (i = 0; i < D_COFACTOR2; ++i) {
        feature[feature_index++] = dumy_sig.cofactor2[i];
    }

    // free the truth table
    free(pFunc);
}

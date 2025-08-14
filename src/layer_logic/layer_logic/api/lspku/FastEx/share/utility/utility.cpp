//
// Created by zephyr on 2023/3/6.
//
#include "../exact_synthesis/exact.h"
#include "../power/power.h"
#include "utility.h"
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <random>

void increment(std::vector<int> &count) {
    unsigned int i = count.size();
    count[i - 1]++;
    while (i != 0) {
        if (count[i] == 16) {
            count[i - 1]++;
            count[i] = 0;
        }
        i--;
    }
}

//Generate random truth table represented in hex
std::string generate_random_tt(int num_inputs) {
    std::random_device random_engine;
    std::array<char, 16> ch{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    std::string temp;
    int needed_length = (1 << (num_inputs - 2));
    temp.reserve(needed_length);
    temp.resize(needed_length);
    std::uniform_int_distribution<int> random_ch(0, 15);
    temp[0] = ch[random_ch(random_engine)];
    for (int i = 1; i < needed_length; i++)
        temp[i] = ch[random_ch(random_engine)];
    return temp;
}

//Generate truth table represented in hex for experiment
void generate_tt(const std::string &output, int num_inputs, int num_outputs) {
    std::vector<char> dic{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    assert(num_outputs == 1);
    std::ofstream fout(output);
    assert(fout.is_open());
    if (num_inputs < 5) {
        int tt_length = 1 << (num_inputs - 2);
        std::vector<int> count(tt_length, 0);
        while (count[0] != 8) {
            std::string str;
            for (int i = 0; i < tt_length; i++) {
                str += dic[count[i]];
            }
            increment(count);
            fout << str << std::endl;
        }
    } else {
        std::set<std::string> tt;
        int needed_number = 100000;
        std::array<char, 16> ch{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        while (tt.size() <= needed_number) {
            std::string temp = generate_random_tt(num_inputs);
            tt.insert(temp);
            if (tt.size() % 100 == 0)
                std::cout << tt.size() << std::endl;
        }
        for (auto &entry: tt)
            fout << entry << std::endl;
    }
    fout.close();
}

std::pair<bool, std::vector<int>>
call_solver(const std::string &cnf_or_smt_file, const std::string &solver, long double *exe_time, int num_threads, const std::string& timi_limit) {
    FILE *fp;
    bool result = false;
    char buf[500];
    std::vector<int> assignment{};

    std::string command = "timeout "+timi_limit+" ";
    if (solver == "minisat") {
        command += "minisat " + cnf_or_smt_file;
    } else if (solver == "kissat") {
        command += "kissat " + cnf_or_smt_file;
    } else if (solver == "parkissat") {
        command += "parkissat " + cnf_or_smt_file + " -c=" + std::to_string(num_threads);
    } else if (solver == "crypto") {
        command += "cryptominisat5 " + cnf_or_smt_file + " -t " + std::to_string(num_threads);
    } else if (solver == "z3") {
        command += "z3 " + cnf_or_smt_file;
    } else {
        std::cout << "Solver Not Found\n";
        assert(false);
    }

    command +=";echo Finish: $?";
    //std::cout << command<<"\n";

    fp = popen(command.c_str(), "r");
    if (!fp) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    if (solver == "minisat") {
        while (memset(buf, 0, sizeof(buf)), fgets(buf, sizeof(buf) - 1, fp) != nullptr) {
            //std::cout<<buf;
            if (strcmp(buf, "SATISFIABLE") == 0) {
                result = true;
                break;
            } if(strcmp(buf, "Finish: 124") == 0) {
                return std::make_pair(false, std::vector<int>{0, -1, 0, -1, 0, -1});
                // Code for TIMEOUT;
            }
        }
    } else if (solver == "kissat" || solver == "parkissat") {
        while (memset(buf, 0, sizeof(buf)), fgets(buf, sizeof(buf) - 1, fp) != nullptr) {
            //std::cout<<buf;
            if (strcmp(buf, "s SATISFIABLE\n") == 0) {
                result = true;
            }
            if (strstr(buf, "process-time:") != nullptr) {
                std::stringstream sin(buf);
                std::string temp;
                sin >> temp >> *exe_time;
            }
            if (buf[0] == 'v') {
                std::stringstream sin(buf);
                std::string _temp;
                int temp;
                sin >> _temp;
                while (sin >> temp)
                    assignment.emplace_back(temp);
            }
            if(strcmp(buf, "Finish: 124") == 0) {
                return std::make_pair(false, std::vector<int>{0, -1, 0, -1, 0, -1});
                // Code for TIMEOUT;
            }
        }
    } else if (solver == "crypto") {
        while (memset(buf, 0, sizeof(buf)), fgets(buf, sizeof(buf) - 1, fp) != nullptr) {
            //std::cout<<buf;
            if (strcmp(buf, "s SATISFIABLE\n") == 0) {
                result = true;
            }
            if (strstr(buf, "Total time (this thread)") != nullptr) {
                std::stringstream sin(buf);
                std::string temp;
                sin >> temp >> temp >> temp >> temp >> temp >> temp >> *exe_time;
            }
            if (buf[0] == 'v') {
                std::stringstream sin(buf);
                std::string _temp;
                int temp;
                sin >> _temp;
                while (sin >> temp)
                    assignment.emplace_back(temp);
            }
            if(strcmp(buf, "Finish: 124") == 0) {
                return std::make_pair(false, std::vector<int>{0, -1, 0, -1, 0, -1});
                // Code for TIMEOUT;
            }
        }
    } else if (solver == "z3") {
        while (memset(buf, 0, sizeof(buf)), fgets(buf, sizeof(buf) - 1, fp) != nullptr) {
            //std::cout<<buf;
            if (strcmp(buf, "sat\n") == 0) {
                result = true;
                continue;
            } else if (strcmp(buf, "unsat\n") == 0) {
                result = false;
                break;
            }
            if(strcmp(buf, "Finish: 124\n") == 0) {
                return std::make_pair(false, std::vector<int>{0, -1, 0, -1, 0, -1});
                // Code for TIMEOUT;
            } else if (strcmp(buf, "Finish: 0\n") == 0) {
                continue;
            } else {
                std::vector<std::string> split_strings = split(std::string(buf),
                                                               std::vector<char>{'(', 'v', ')', ' ', '\n'});
                assert(split_strings.size() == 2);
                //std::cout << split_strings[0] << " " << split_strings[1] << "\n";
                assignment.emplace_back(std::stoi(split_strings[0]) * (split_strings[1] == "true" ? 1 : -1));
            }
        }
    } else {
        std::cout << "Solver Not Found\n";
        assert(false);
    }

    pclose(fp);
    return std::make_pair(result, assignment);
}

// Transform an integer to a binary vector representation
// 5 -> 1 0 1
std::vector<int> int_to_bvector(int n, unsigned int fix_length) {
    std::vector<int> result;
    while (n != 0) {
        result.emplace_back(n % 2);
        n /= 2;
    }
    unsigned int padding = fix_length - result.size();
    for (int i = 0; i < padding; i++)
        result.emplace_back(0);
    std::reverse(result.begin(), result.end());
    return result;
}

int bvector_to_int(const std::vector<int> &b_vector) {
    int result = 0;
    for (auto &entry: b_vector) {
        result = result << 1;
        result += entry;
    }
    return result;
}

int bvector_to_int(const std::string &b_vector) {
    int result = 0;
    for (auto &ch: b_vector) {
        result = result << 1;
        result += ch - '0';
    }
    return result;
}

std::vector<char> bvector_to_hvector(const std::vector<int> &b_vector) {
    std::vector<char> dic{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    std::vector<char> result;
    for (int i = 0; i < b_vector.size(); i += 4) {
        int _result = 0;
        for (int j = 0; j < 4; j++) {
            _result = _result << 1;
            _result += b_vector[i + j];
        }
        result.emplace_back(dic[_result]);
    }
    return result;
}

std::string hex_to_binary(const std::string &hex) {
    std::string result;
    for (auto &ch: hex) {
        switch (ch) {
            case '0':
                result += "0000";
                break;
            case '1':
                result += "0001";
                break;
            case '2':
                result += "0010";
                break;
            case '3':
                result += "0011";
                break;
            case '4':
                result += "0100";
                break;
            case '5':
                result += "0101";
                break;
            case '6':
                result += "0110";
                break;
            case '7':
                result += "0111";
                break;
            case '8':
                result += "1000";
                break;
            case '9':
                result += "1001";
                break;
            case 'A':
                result += "1010";
                break;
            case 'B':
                result += "1011";
                break;
            case 'C':
                result += "1100";
                break;
            case 'D':
                result += "1101";
                break;
            case 'E':
                result += "1110";
                break;
            case 'F':
                result += "1111";
                break;
            case 'a':
                result += "1010";
                break;
            case 'b':
                result += "1011";
                break;
            case 'c':
                result += "1100";
                break;
            case 'd':
                result += "1101";
                break;
            case 'e':
                result += "1110";
                break;
            case 'f':
                result += "1111";
                break;
            default:
                assert(false);
        }
    }
    return result;
}

std::string binary_to_hex(const std::string &binary) {
    std::string result = "";

    for (int i = 0; i < binary.length(); i += 4) {
        std::string temp = binary.substr(i, 4);
        if (temp == "0000") result += '0';
        else if (temp == "0001") result += '1';
        else if (temp == "0010") result += '2';
        else if (temp == "0011") result += '3';
        else if (temp == "0100") result += '4';
        else if (temp == "0101") result += '5';
        else if (temp == "0110") result += '6';
        else if (temp == "0111") result += '7';
        else if (temp == "1000") result += '8';
        else if (temp == "1001") result += '9';
        else if (temp == "1010") result += 'a';
        else if (temp == "1011") result += 'b';
        else if (temp == "1100") result += 'c';
        else if (temp == "1101") result += 'd';
        else if (temp == "1110") result += 'e';
        else if (temp == "1111") result += 'f';
        else
            assert(false);
    }

    return result;
}

std::vector<bool> int_to_binary(int i, int vector_size) {
    i = i % (1 << vector_size);
    int abs = i > 0 ? i : -i;
    std::vector<bool> _result;
    std::vector<bool> result;
    while (abs != 0) {
        _result.emplace_back(abs % 2);
        abs /= 2;
    }

    while (_result.size() < vector_size)
        _result.emplace_back(false);

    if (i < 0) {
        for (auto &&it: _result) {
            it = !it;
        }
        for (auto &&it: _result) {
            it = !it;
            if (it)
                break;
        }
    } else {
        for (auto it = _result.rbegin(); it != _result.rend(); it++) {
            result.emplace_back(*it ? 1 : 0);
        }
    }
    return result;
}

int binary_to_int(const std::vector<bool> &bits) {
    int result = 0;
    for (auto bit: bits) {
        result <<= 1;
        result += bit ? 1 : 0;
    }
    return result;
}

std::vector<bool> hex_to_binary(char hex) {
    switch (hex) {
        case '0':
            return std::vector<bool>{false, false, false, false};
        case '1':
            return std::vector<bool>{false, false, false, true};
        case '2':
            return std::vector<bool>{false, false, true, false};
        case '3':
            return std::vector<bool>{false, false, true, true};
        case '4':
            return std::vector<bool>{false, true, false, false};
        case '5':
            return std::vector<bool>{false, true, false, true};
        case '6':
            return std::vector<bool>{false, true, true, false};
        case '7':
            return std::vector<bool>{false, true, true, true};
        case '8':
            return std::vector<bool>{true, false, false, false};
        case '9':
            return std::vector<bool>{true, false, false, true};
        case 'a':
            return std::vector<bool>{true, false, true, false};
        case 'b':
            return std::vector<bool>{true, false, true, true};
        case 'c':
            return std::vector<bool>{true, true, false, false};
        case 'd':
            return std::vector<bool>{true, true, false, true};
        case 'e':
            return std::vector<bool>{true, true, true, false};
        case 'f':
            return std::vector<bool>{true, true, true, true};
        case 'A':
            return std::vector<bool>{true, false, true, false};
        case 'B':
            return std::vector<bool>{true, false, true, true};
        case 'C':
            return std::vector<bool>{true, true, false, false};
        case 'D':
            return std::vector<bool>{true, true, false, true};
        case 'E':
            return std::vector<bool>{true, true, true, false};
        case 'F':
            return std::vector<bool>{true, true, true, true};
        default:
            std::cout << "Hexadecimal character not recognized: " << hex << "\n";
            return std::vector<bool>{};
    }
}

std::vector<int> bvector_to_int(const std::vector<int> &b_vector, bool ignorant_item) {
    bool flag = true;
    if (!ignorant_item)
        return std::vector<int>{bvector_to_int(b_vector)};
    for (auto &bit: b_vector)
        if (bit == -1)
            flag = false;
    if (flag)
        return std::vector<int>{bvector_to_int(b_vector)};
    std::vector<int> result;
    std::vector<std::vector<int>> b_vector_expansion = {std::vector<int>{}};
    for (auto &bit: b_vector) {
        if (bit != -1) {
            for (auto &entry: b_vector_expansion)
                entry.emplace_back(bit);
        } else {
            for (auto &entry: b_vector_expansion)
                entry.emplace_back(0);
            b_vector_expansion.insert(b_vector_expansion.begin(), b_vector_expansion.begin(), b_vector_expansion.end());
            for (auto it = b_vector_expansion.begin() + b_vector_expansion.size() / 2;
                 it != b_vector_expansion.end(); it++)
                *(it->end() - 1) = 1;
        }
    }
    for (auto &entry: b_vector_expansion) {
        result.emplace_back(bvector_to_int(entry));
    }
    return result;

}

std::vector<std::string> split(const std::string &str, char terminal) {
    std::vector<std::string> split_str;
    std::string::size_type end_pos, start_pos;
    start_pos = str.find(terminal);
    end_pos = 0;
    while (std::string::npos != start_pos) {
        split_str.push_back(str.substr(end_pos, start_pos - end_pos));

        end_pos = start_pos + 1;
        while (str[end_pos] == terminal)
            end_pos++;
        start_pos = str.find(terminal, end_pos);
    }
    if (end_pos != str.length())
        split_str.push_back(str.substr(end_pos));

    std::remove(split_str.begin(), split_str.end(), "");

    return split_str;
}

std::vector<std::string> split(const std::string &str, std::vector<char> terminals) {
    std::vector<std::string> split_str;
    std::string::size_type end_pos, start_pos = std::string::npos;
    for (auto &ch: terminals) {
        std::string::size_type _temp = str.find(ch);
        start_pos = _temp < start_pos ? _temp : start_pos;
    }

    end_pos = 0;
    while (std::string::npos != start_pos) {
        if (start_pos != end_pos)
            split_str.push_back(str.substr(end_pos, start_pos - end_pos));

        end_pos = start_pos + 1;
        while (std::find(terminals.begin(), terminals.end(), str[end_pos]) != terminals.end())
            end_pos++;
        start_pos = std::string::npos;
        for (auto &ch: terminals) {
            std::string::size_type _temp = str.find(ch, end_pos);
            start_pos = _temp < start_pos ? _temp : start_pos;
        }
    }
    if (end_pos != str.length())
        split_str.push_back(str.substr(end_pos));

    return split_str;
}

void exact::generate_netlist_library(std::string const &filename, int num_inputs = 4) {
    std::string solver = "parkissat";
    std::string encoding_method = "SSV";
    std::string symmetry = "";
    std::ifstream fin("./test_case/documents/" + std::to_string(num_inputs) + "input.txt");
    assert(fin.is_open());
    std::string temp;
    std::vector<std::string> functions;
    while (fin >> temp)
        functions.emplace_back(temp);

    std::ofstream fout(filename, std::ios::out);
    assert(fout.is_open());
    fout << "T 1\nA 0\nS " << functions.size() << " " << num_inputs << "\n";
    fout.close();

    for (auto &line: functions) {
        //std::string line = "0001";
        fout = std::ofstream(filename, std::ios::app | std::ios::out);
        assert(fout.is_open());

        fout << "0x" << line;
        std::cout << "0x" << line << "\n";
        exact::Boolean func(line);
        std::vector<exact::Boolean> funcs = {func};

        exact::Encoder *encoder = nullptr;
        if (encoding_method == "DITT") {
            encoder = new exact::DITT(funcs);
        } else if (encoding_method == "SSV") {
            encoder = new exact::SSV(funcs);
        } else if (encoding_method == "MSV") {
            encoder = new exact::MSV(funcs);
        }

        if (symmetry.find('N') != std::string::npos) encoder->non_trivial = true;
        if (symmetry.find('A') != std::string::npos) encoder->all_steps = true;
        if (symmetry.find('R') != std::string::npos) encoder->no_replication = true;
        if (symmetry.find('C') != std::string::npos) encoder->lexicographical_step = true;
        if (symmetry.find('O') != std::string::npos) encoder->lexicographical_op = true;
        if (symmetry.find('S') != std::string::npos) encoder->ordered_symmetric = true;

        encoder->r = 1;
        std::pair<bool, std::vector<int>> result = synthesis(encoder, solver, std::cout);

        int r = encoder->r, max_t =
                (1 << (func.num_bits)) - 1, m = (int) funcs.size(), n = func.num_bits;

        std::map<std::string, int> variable_index = encoder->generate_variable_index(n, r, max_t, m);
        std::map<int, bool> variable_assignment;
        for (auto &entry: result.second) {
            int index = abs(entry);
            variable_assignment[index] = index == entry;
        }

        fout << " None " << encoder->r << " ";
        //std::cout << line << encoder->r << "\n";
        if (encoding_method == "SSV") {
            for (unsigned int i = encoder->initial_i; i < encoder->initial_i + r; i++) {
                for (int k = 1; k < i; k++) {
                    for (int j = 1; j < k; j++) {
                        if (variable_assignment[variable_index["s" + std::to_string(i) + std::to_string(j) +
                                                               std::to_string(k)]]) {
                            fout << j << " " << k << " ";
                            //std::cout << "here"<<j << " " << k << " \n";
                            bool f01 = variable_assignment[variable_index["f" + std::to_string(i) + "01"]],
                                    f10 = variable_assignment[variable_index["f" + std::to_string(i) + "10"]],
                                    f11 = variable_assignment[variable_index["f" + std::to_string(i) + "11"]];
                            //std::cout<<"f" + std::to_string(i) + "01"<<" "<<variable_index["f" + std::to_string(i) + "01"]<<" "<<variable_assignment[variable_index["f" + std::to_string(i) + "01"]]<<"\n";
                            //std::cout<<"f" + std::to_string(i) + "10"<<" "<<variable_index["f" + std::to_string(i) + "10"]<<" "<<variable_assignment[variable_index["f" + std::to_string(i) + "10"]]<<"\n";
                            //std::cout<<"f" + std::to_string(i) + "11"<<" "<<variable_index["f" + std::to_string(i) + "11"]<<" "<<variable_assignment[variable_index["f" + std::to_string(i) + "11"]]<<"\n";
                            //std::cout<<"here"<<f01<<" "<<f10<<" "<<f11<<"\n";
                            int function_one_hot = (f11 << 2) | (f10 << 1) | f01, function_type;
                            switch (function_one_hot) {
                                case 0:
                                    assert(false);
                                case 1:
                                case 2:
                                    function_type = 7;
                                    break;
                                case 3:
                                    function_type = 14;
                                    break;
                                case 4:
                                    function_type = 9;
                                    break;
                                case 5:
                                    function_type = 13;
                                    break;
                                case 6:
                                    function_type = 12;
                                    break;
                                case 7:
                                    function_type = 4;
                                    break;
                                default:
                                    assert(false);
                            }
                            fout << function_type << " ";
                            //std::cout<< function_type<<" ";
                        }
                    }
                }
            }
            fout << r << "\n";
            //std::cout<<"\n";
            fout.close();
            delete encoder;
        } else {
            std::cerr << "Not Implemented Error";
            assert(false);
        }
    }
    fin.close();

    fout = std::ofstream(filename, std::ios::app | std::ios::out);
    assert(fout.is_open());
    fout << "E\n";
    fout.close();
}

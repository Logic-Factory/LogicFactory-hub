//
// Created by zephyr on 11/3/2023.
//

#include "../exact_synthesis/exact.h"
#include "../power/power.h"
#include "../incremental/incremental.h"
#include "../netlist/netlist.h"
#include <chrono>
#include <unistd.h>
#include "utility.h"

std::pair<bool, std::vector<int>>
exact::synthesis(exact::Encoder *encoder, const std::string &solver, std::ostream &out = std::cout, int num_threads) {
    double total_time = 0;
    while (true) {
        long double exe_time = 0;
        exact::Encoding encoding = encoder->encode(true);
        std::string cnf = "./test_case/share/" + std::to_string(encoder->r) + "_" +
                          std::to_string(getpid()) + ".cnf";
        std::ofstream fout(cnf);
        encoding.write_dimacs(fout);
        fout.close();
        auto start = std::chrono::high_resolution_clock::now();
        std::pair<bool, std::vector<int>> result = call_solver(cnf, solver, &exe_time, num_threads);
        if (!result.first && result.second == std::vector<int>{0, -1, 0, -1, 0, -1}) {
            out<<"Timeout\n";
            break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        total_time += duration.count();
        if (result.first) {
            //out<<encoder.r<<" "<<exe_time<<"\n";
            out << encoder->r << " " << duration.count() << "\n";
            std::cout<<total_time<<"\n";
            return result;
        }
        if (encoder->r == 15) {
            out << encoder->r << " " << duration.count() << "\n";
            out << "Time Out\n";
            break;
        }
        //out<<encoder.r<<" "<<exe_time<<" ";
        //std::cout << encoder->r << "\n";
        out << encoder->r << " " << duration.count() << " ";
        encoder->r++;
        remove(cnf.c_str());
    }
    std::cout<<total_time<<"\n";
    return std::make_pair(false, std::vector<int>{});
}

std::pair<bool, std::vector<int>> exact::power_synthesis(exact::SSV_Power* encoder, const std::string& solver, std::ostream& out, std::vector<double> input_probability, bool average) {
    //while (true) {
    long double exe_time = 0;
    exact::Encoding encoding = encoder->encode(true, input_probability, true);
    std::string smt = "./test_case/share/" + std::to_string(encoder->r) + "_" +
                      std::to_string(getpid()) + ".smt2";
    //std::ofstream fout(smt);
    //encoding.write_smt2(fout, true);
    //fout.close();
    auto start = std::chrono::high_resolution_clock::now();
    //std::pair<bool, std::vector<int>> result = call_solver(smt, solver, &exe_time);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::pair<bool, std::vector<int>> last_result;

    //if (result.first) {
    //out<<encoder.r<<" "<<exe_time<<"\n";
    out << encoder->r << "\n";
    //for(encoder->target_switching_probability = 1.0/encoder->num_classes; encoder->target_switching_probability < 1.0;encoder->target_switching_probability += 1.0/encoder->num_classes) {
    for(encoder->target_switching_probability = 1.0; encoder->target_switching_probability > 0.0; encoder->target_switching_probability -= 1.0/encoder->num_classes) {
        exact::Encoding _encoding = encoder->encode(true, input_probability, true);
        std::string _smt = "./test_case/share/" + std::to_string(encoder->r) + "_" +
                           std::to_string(getpid()) + ".smt2";
        std::ofstream _fout(_smt);
        _encoding.write_smt2(_fout, true);
        _fout.close();
        auto _start = std::chrono::high_resolution_clock::now();
        std::pair<bool, std::vector<int>> _result = call_solver(_smt, solver, &exe_time);
        if (!_result.first && _result.second == std::vector<int>{0, -1, 0, -1, 0, -1}) {
            out<<"Timeout\n";
            break;
        }
        auto _end = std::chrono::high_resolution_clock::now();
        auto _duration = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start);
        out << encoder->target_switching_probability << " " << _duration.count() << "\n";
        if(!_result.first) {
            //for(auto& entry: _result.second)
            //    std::cout<<entry<<" ";
            //out<<"UNSAT\n";
            return last_result;
        }
        /*
        for(auto& entry: _result.second)
            out<<entry<<" ";
        out<<"\n";
         */
        last_result = _result;
    }
    //assert(false);
    return std::make_pair(false, std::vector<int>{});
    //}
    if (encoder->r == 15) {
        out << encoder->r << " " << duration.count() << "\n";
        out << "Time Out\n";
        //break;
    }
    //out<<encoder.r<<" "<<exe_time<<" ";
    //std::cout << encoder->r << "\n";
    out << encoder->r << " " << duration.count() << " ";
    encoder->r++;
    remove(smt.c_str());
    //}
}

int find_or_generate_circuit(const std::string& library, const std::string & function) {
    std::map<std::pair<std::string, std::string>, NET::Netlist *> optimal_library;
    read_netlist_library(library, optimal_library);
    std::string label = "None";
    auto netlist = optimal_library[std::make_pair(function, label)];
    if(netlist)
        return netlist->nodes.size() - netlist->inputs.size();
    else {
        std::vector<exact::Boolean> funcs = {exact::Boolean(function)};
        exact::SSV ssv(funcs);
        if(exact::synthesis(&ssv, "kissat").first)
            return ssv.r;
        else
            return -1;
    }
}

std::pair<bool, std::vector<int>> exact::incremental_synthesis(exact::SSV_Incremental *encoder, const std::string & solver, std::ostream &out, int num_threads) {
    //int sub_r = find_or_generate_circuit("library_path", encoder->get_similar_function());
    int sub_r = encoder->functions[0].num_bits - 2;
    //Start trying using sub-circuits in a zigzag way.
    int added_r = 1;
    bool increment_direct = true, initial_stage = true;
    int round_count = 0;
    while(true) {
        round_count++;
        long double exe_time = 0;
        exact::Encoding encoding;
        if(encoder->r <= sub_r && initial_stage) {
            encoding = encoder->incremental_encode(true).first;
            encoder->r++;
        }
        else if(increment_direct) {
            encoder->r = added_r;
            encoding = encoder->incremental_encode(true).first;
            increment_direct = initial_stage = false;
        } else {
            encoder->r = added_r + sub_r;
            encoding = encoder->SSV::encode(true);
            increment_direct = true;
            added_r++;
        }
        std::string cnf = "./test_case/share/" + std::to_string(round_count) + "_" +
                          std::to_string(getpid()) + ".cnf";
        std::ofstream fout(cnf);
        encoding.write_dimacs(fout);
        fout.close();
        auto start = std::chrono::high_resolution_clock::now();
        std::pair<bool, std::vector<int>> result = call_solver(cnf, solver, &exe_time, num_threads);
        if (!result.first && result.second == std::vector<int>{0, -1, 0, -1, 0, -1}) {
            out<<"Timeout\n";
            break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        //remove(cnf.c_str());
        if (result.first) {
            //out<<encoder.r<<" "<<exe_time<<"\n";
            out << round_count << " " << duration.count() << "\n";
            return result;
        }
        if (added_r == 5) {
            out << round_count << " " << duration.count() << "\n";
            out << "Time Out\n";
            break;
        }
        //out<<encoder.r<<" "<<exe_time<<" ";
        std::cout << round_count << "\n";
        out << round_count << " " << duration.count() << " ";
    }
    return std::make_pair(false, std::vector<int>{});
}
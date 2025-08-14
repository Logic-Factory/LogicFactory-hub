//
// Created by zephyr on 2021/12/9.
//
#include "abc_api.h"
#include <map>
#include <string>

namespace PAS {
    std::map <std::string, std::string> alias = {
            {"b",      "balance;"},
            {"rw",     "rewrite;"},
            {"rwz",    "rewrite -z;"},
            {"rf",     "refactor;"},
            {"rfz",    "refactor -z;"},
            {"resyn",  "balance;rewrite;rewrite -z;balance;rewrite -z;balance;"},
            {"resyn2", "balance; rewrite; refactor; balance; rewrite; rewrite -z;balance;refactor -z;rewrite -z;balance"},
            {"choice", "fraig_store; resyn; fraig_store; resyn2; fraig_store;fraig_restore"}
    };

    void *abc_initialize() {
        void *pAbc;

        Abc_Start();
        pAbc = Abc_FrameGetGlobalFrame();

        return pAbc;
    }

    void execute_command(void *pAbc, const std::string &s) {
        char command[10000];

        Abc_Start();
        pAbc = Abc_FrameGetGlobalFrame();

        sprintf(command, "%s", s.c_str());
        if (Cmd_CommandExecute(pAbc, command)) {
            fprintf(stdout, "Cannot execute command \"%s\".\n", command);
        }
    }

    void abc_end() {
        Abc_Stop();
    }

    void abc_check_equivalence(void *pAbc, const std::string &netlist_1, const std::string &netlist_2) {
        std::string command = "cec " + netlist_1 + " " + netlist_2 + ";";
        execute_command(pAbc, command);
    }

    void abc_synthesize(void *pAbc, const std::string &in_file, const std::string &cmd = "resyn") {
        std::string command = "read " + in_file + ";";
        command += alias[cmd];
        execute_command(pAbc, command);
    }

    void abc_read(void *pAbc, const std::string &in_file) {
        std::string command = "read " + in_file + ";";
        execute_command(pAbc, command);
    }

    void abc_write(void *pAbc, const std::string &format, const std::string &out_file) {
        std::string command = "write_" + format + " " + out_file + ";";
        execute_command(pAbc, command);
    }

    void abc_read_lib(void *pAbc, const std::string &lib) {
        std::string command = "read_library abclib/" + lib + ";";
        execute_command(pAbc, command);
    }

    void abc_read_lut_lib(void *pAbc, const std::string &lib) {
        std::string command = "read_lut abclib/" + lib + ";";
        execute_command(pAbc, command);
    }

    void abc_map(void *pAbc) {
        std::string command = "map;";
        execute_command(pAbc, command);
    }

    void abc_lutpack(void *pAbc) {
        std::string command = "if;";
        execute_command(pAbc, command);
    }

    void print_state(void *pAbc) {
        std::string command = "print_stats;";
        execute_command(pAbc, command);
    }
}

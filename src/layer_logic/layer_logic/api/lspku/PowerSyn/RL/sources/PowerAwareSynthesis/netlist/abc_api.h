//
// Created by zephyr on 2021/12/9.
//

#ifndef NETLIST_ABC_API_H
#define NETLIST_ABC_API_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>

extern "C" void Abc_Start();
extern "C" void Abc_Stop();
extern "C" void *Abc_FrameGetGlobalFrame();
extern "C" int Cmd_CommandExecute(void *pAbc, char *sCommand);

namespace PAS {

// abc tool initialization
    void *abc_initialize();

// abc tool stop
    void abc_end();

// equivalence check
    void abc_check_equivalence(void *pAbc, const std::string &netlist_1, const std::string &netlist_2);

// logic synthesis
    void abc_synthesize(void *pAbc, std::string in_file, std::string write_cmd);

// read a file(for all formats)
    void abc_read(void *pAbc, const std::string &in_file);

// read a technology library (not liberty file)
    void abc_read_lib(void *pAbc, const std::string &lib);

// read a lut technology library (not liberty file)
    void abc_read_lut_lib(void *pAbc, const std::string &lib);

// write the netlist with chosen format
    void abc_write(void *pAbc, const std::string &format, const std::string &out_file);

// standard cell mapping
    void abc_map(void *pAbc);

// LUT mapping
    void abc_lutpack(void *pAbc);

    void print_state(void *pAbc);
}

#endif //NETLIST_ABC_API_H

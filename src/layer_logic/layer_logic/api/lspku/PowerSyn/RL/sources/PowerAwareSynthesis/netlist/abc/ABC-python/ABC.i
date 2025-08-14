%module ABC
%{
    #define ABC_USE_STDINT_H = 1
    #include <stdio.h>
    #include <time.h>
    //#include "misc/util/abc_global.h"
    //#include "base/main/main.h"
    //#include "base/cmd/cmd.h"
    typedef struct Abc_Frame_t_ Abc_Frame_t;
    extern void            Abc_Start();
    extern void            Abc_Stop();
    extern Abc_Frame_t *   Abc_FrameGetGlobalFrame();
    extern int Cmd_CommandExecute( Abc_Frame_t * pAbc, const char * sCommand );
%}

extern void            Abc_Start();
extern void            Abc_Stop();
extern Abc_Frame_t *   Abc_FrameGetGlobalFrame();
extern int Cmd_CommandExecute( Abc_Frame_t * pAbc, const char * sCommand );


%pythoncode %{

import os
import sys
from ctypes import CDLL
libc = CDLL('libc.so.6')
import tempfile

alias = {"b":"balance", "rw":"rewrite", "rwz":"rewrite -z", "rf":"refactor", "rfz":"refactor -z",\
        "resyn":"balance;rewrite;rewrite -z;balance;rewrite -z;balance;",\
        "resyn2": "balance; rewrite; refactor; balance; rewrite; rewrite -z;balance;refactor -z;rewrite -z;balance",\
        "choice": "fraig_store; resyn; fraig_store; resyn2; fraig_store;fraig_restore"}


def abc_start():
    Abc_Start()
    pAbc = Abc_FrameGetGlobalFrame()
    
    return pAbc

def abc_end(pAbc):
    Abc_Stop()
    pAbc = -1
    return 0

def execute_command(pAbc, cmd, verbose = True):
    assert(pAbc != -1)
    old_fno = os.dup(sys.stdout.fileno())
    fd = tempfile.TemporaryFile()
    os.dup2(fd.fileno(), 1)
    status = Cmd_CommandExecute(pAbc, cmd)
    if verbose:
        libc.fflush(None)
        os.dup2(old_fno, 1)
        fd.seek(0)
        msg = fd.read().decode()
        fd.close()
    else:
        msg = ""
    if status != 0:
        print("Cannot execute command" + cmd)
    return status, msg

def abc_check_equivalence(pAbc, netlist_1, netlist_2):
    cmd = "cec " + netlist_1 + " " + netlist_2 + ";"
    return execute_command(pAbc, cmd)

def abc_synthesis(pAbc, op="resyn"):
    cmd = alias.get(op)
    cmd = cmd if cmd is not None else op
    return execute_command(pAbc, cmd)

def abc_read(pAbc, in_file):
    cmd = "read " + in_file + ";"
    return execute_command(pAbc, cmd)

def abc_write(pAbc, format, out_file):
    cmd="write_" + format + " " + out_file + ";"
    return execute_command(pAbc, cmd)

def read_lib(pAbc, lib):
    cmd = "read_library abclib/" + lib + ";"
    return execute_command(pAbc, cmd)

def read_lut_lib(pAbc, lib):
    cmd = "read_lut abclib/" + lib + ";"
    return execute_command(pAbc, cmd)

def abc_map(pAbc):
    cmd = "map;"
    return execute_command(pAbc, cmd)

def abc_lutpack(pAbc):
    cmd = "if;"
    return execute_command(pAbc, cmd)

def print_state(pAbc):
    cmd = "print_stats;"
    return execute_command(pAbc, cmd)
%}    

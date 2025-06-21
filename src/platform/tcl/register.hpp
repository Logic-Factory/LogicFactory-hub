#pragma once

#include "tcl/engine/tcl_macro.hpp"
#include "tcl/cmds/tcl_cmds_misc.hpp"
#include "tcl/cmds/tcl_cmds_flow.hpp"
#include "tcl/cmds/tcl_cmds_io.hpp"
#include "tcl/cmds/tcl_cmds_pass_arch.hpp"
#include "tcl/cmds/tcl_cmds_pass_logic.hpp"
#include "tcl/cmds/tcl_cmds_pass_netlist.hpp"

namespace lf
{

namespace tcl
{

int registerCmds()
{
  //////////////////////////////////////////////////////////
  // misc
  //////////////////////////////////////////////////////////
  LF_MACOR_REGISTER_TCL_CMD( CmdLfHelp, "help" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfPrintStat, "print_stats" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfRename, "rename" );
  //////////////////////////////////////////////////////////
  // flow
  //////////////////////////////////////////////////////////
  LF_MACOR_REGISTER_TCL_CMD( CmdLfStart, "start" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfStop, "stop" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfAnchor, "anchor" );
  //////////////////////////////////////////////////////////
  // IO
  //////////////////////////////////////////////////////////
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadAiger, "read_aiger" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadBench, "read_bench" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadBlif, "read_blif" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadCnf, "read_cnf" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadFormula, "read_formula" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadPla, "read_pla" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadGenlib, "read_genlib" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadLiberty, "read_liberty" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadVerilog, "read_verilog" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadGtech, "read_gtech" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadJson, "read_json" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoReadRtlil, "read_rtlil" );

  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteAiger, "write_aiger" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteBlif, "write_blif" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteBench, "write_bench" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteCnf, "write_cnf" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWritePla, "write_pla" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteVerilog, "write_verilog" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteDot, "write_dot" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteBtor, "write_btor" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteEdif, "write_edif" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteFirrtl, "write_firrtl" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteJson, "write_json" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteTruth, "write_truth" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteRtlil, "write_rtlil" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteSpice, "write_spice" );

  LF_MACOR_REGISTER_TCL_CMD( CmdLfIoWriteGraphml, "write_graphml" );

  //////////////////////////////////////////////////////////
  // arch
  //////////////////////////////////////////////////////////
  LF_MACOR_REGISTER_TCL_CMD( CmdLfArchHierarchy, "hierarchy" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfArchFlatten, "flatten" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfArchFsm, "fsm" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfArchOpt, "opt" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfArchTechmap, "techmap" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfArchAigmap, "aigmap" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfArchAbc, "abc" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfArchGtechmap, "gtechmap" );

  //////////////////////////////////////////////////////////
  // logic
  //////////////////////////////////////////////////////////
  LF_MACOR_REGISTER_TCL_CMD( CmdLfArch2Logic, "arch2logic" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicNtktype, "ntktype" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicConvert, "convert" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicUpdate, "update" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicStrash, "strash" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicBalance, "balance" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicRewrite, "rewrite" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicRefactor, "refactor" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicResub, "resub" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicMapFPGA, "map_fpga" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicMapASIC, "map_asic" );
  
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicExactMap, "exact_map" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicLutResyn, "lut_resyn" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicMighty, "mighty" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicXAG1, "xag1" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicXAG2, "xag2" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicXAGBalance, "xagba" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicXAGResub, "xagrs" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicXAGRewrite, "xagrw" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicXMGResub, "xmgrs" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogicXMGRewrite, "xmgrw" );

  //////////////////////////////////////////////////////////
  // netlist
  //////////////////////////////////////////////////////////
  LF_MACOR_REGISTER_TCL_CMD( CmdLfArch2Netlist, "arch2netlist" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfLogic2Netlist, "logic2netlist" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfNetlistConfig, "config" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfNetlistInit, "init" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfNetlistSta, "sta" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfNetlistPower, "power" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfNetlistFloorplan, "floorplan" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfNetlistPlacement, "placement" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfNetlistCts, "cts" );
  LF_MACOR_REGISTER_TCL_CMD( CmdLfNetlistRouting, "routing" );
  // TODO:
  // write def
  // write gds
  return EXIT_SUCCESS;
}

} // namespace tcl

} // namespace lf
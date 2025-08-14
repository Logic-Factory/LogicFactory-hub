#pragma once

#include "tcl/engine/tcl_cmd.hpp"
#include "tcl/engine/tcl_option.hpp"
#include "tcl/cmds/utils.hpp"

#include "misc/anchor.hpp"

#include "layer_arch/arch_manager.hpp"
#include "layer_logic/logic_manager.hpp"
#include "layer_logic/wrapper/arch_to_logic.hpp"
#include "layer_logic/aux/convert_node.hpp"
#include "layer_logic/aux/convert_update.hpp"
#include "layer_logic/aux/convert_cover.hpp"

#include "layer_logic/api/abc/pass/strash.hpp"
#include "layer_logic/api/abc/pass/balance.hpp"
#include "layer_logic/api/abc/pass/rewrite.hpp"
#include "layer_logic/api/abc/pass/refactor.hpp"
#include "layer_logic/api/abc/pass/resub.hpp"
#include "layer_logic/api/abc/pass/map_fpga.hpp"
#include "layer_logic/api/abc/pass/map_asic.hpp"

#include "layer_logic/api/lsils/pass/balance.hpp"
#include "layer_logic/api/lsils/pass/rewrite.hpp"
#include "layer_logic/api/lsils/pass/refactor.hpp"
#include "layer_logic/api/lsils/pass/resub.hpp"
#include "layer_logic/api/lsils/pass/map_fpga.hpp"
#include "layer_logic/api/lsils/pass/map_asic.hpp"
#include "layer_logic/api/lsils/pass/strash.hpp"

#include "layer_logic/api/lsnbu/exact_map.hpp"
#include "layer_logic/api/lsnbu/lut_resyn.hpp"
#include "layer_logic/api/lsnbu/mighty.hpp"
#include "layer_logic/api/lsnbu/xag_mprm_multi_mult_opt.hpp"
#include "layer_logic/api/lsnbu/xag_mprm2_area_opt.hpp"
#include "layer_logic/api/lsnbu/xagba.hpp"
#include "layer_logic/api/lsnbu/xagrs.hpp"
#include "layer_logic/api/lsnbu/xagrw.hpp"
#include "layer_logic/api/lsnbu/xmgrs.hpp"
#include "layer_logic/api/lsnbu/xmgrw.hpp"

#include "layer_logic/api/lspku/FastEx/share/exact_synthesis/exact.h"
#include "layer_logic/api/lspku/FastEx/share/incremental/incremental.h"
#include "layer_logic/api/lspku/FastEx/share/netlist/netlist.h"
#include "layer_logic/api/lspku/FastEx/share/power/power.h"
#include "layer_logic/api/lspku/FastEx/share/utility/utility.h"
#include "layer_logic/api/lspku/PowerSyn/share/netlist.h"

#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace lf
{

namespace tcl
{
class CmdLfLogicNtktype : public TclCmd
{
public:
  explicit CmdLfLogicNtktype( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {
        { "-tool", "all", "string", "" },
        { "-stat", "all", "string", "" },
        { "-type", "all", "string", "" } };
    setOptions( this, options );
  }

  ~CmdLfLogicNtktype() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = { "-tool", "-stat", "-type" };
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = { "-tool", "-stat", "-type" };
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    lfLntINST->set_ntktype( strOptionsValue["-tool"], strOptionsValue["-stat"], strOptionsValue["-type"] );

    return 1;
  }
}; // class CmdLfLogicNtktype

class CmdLfArch2Logic : public TclCmd
{
public:
  explicit CmdLfArch2Logic( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfArch2Logic() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );
    // transform arch into logic
    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();
    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_ARCH_YOSYS:
      lf::logic::arch_to_logic( lfAmINST->current<Yosys::RTLIL::Design*>() );
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfArch2Logic

class CmdLfLogicConvert : public TclCmd
{
public:
  explicit CmdLfLogicConvert( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {
        { "-from", "all", "string", "" },
        { "-to", "all", "string", "" },
        { "-n", "all", "bool", "convert by node to node" } };
    setOptions( this, options );
  }

  ~CmdLfLogicConvert() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = { "-from", "-to" };
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = { "-from", "-to" };
    std::vector<std::string> boolOptions = { "-n" };
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    if ( boolOptionsValue["-n"] )
      lf::logic::convert_node( strOptionsValue["-from"], strOptionsValue["-to"] );
    else
      lf::logic::convert_cover( strOptionsValue["-from"], strOptionsValue["-to"] );
    return 1;
  }
}; // class CmdLfLogicConvert

class CmdLfLogicUpdate : public TclCmd
{
public:
  explicit CmdLfLogicUpdate( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {
        { "-n", "all", "bool", "convert by node to node" } };
    setOptions( this, options );
  }

  ~CmdLfLogicUpdate() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = { "-n" };
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    lf::logic::convert_update( boolOptionsValue["-n"] );
    return 1;
  }
}; // class CmdLfLogicUpdate

class CmdLfLogicStrash : public TclCmd
{
public:
  explicit CmdLfLogicStrash( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {
        { "-a", "abc", "bool", "" },
        { "-c", "abc", "bool", "" },
        { "-r", "abc", "bool", "" },
        { "-i", "abc", "bool", "" } };
    setOptions( this, options );
  }

  ~CmdLfLogicStrash() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = { "-a", "-c", "-r", "-i" };
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_ABC:
      lf::logic::abc::strash( boolOptionsValue["-a"], boolOptionsValue["-c"], boolOptionsValue["-r"], boolOptionsValue["-i"] );
      break;
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsils::strash();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicStrash

class CmdLfLogicBalance : public TclCmd
{
public:
  explicit CmdLfLogicBalance( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {
        { "-l", "abc", "bool", "" },
        { "-d", "abc", "bool", "" },
        { "-s", "abc", "bool", "" },
        { "-x", "abc", "bool", "" },
        { "-v", "abc", "bool", "" },
        { "-m", "lsils", "bool", "minimize level" },
        { "-f", "lsils", "bool", "fast mode" } };
    setOptions( this, options );
  }

  ~CmdLfLogicBalance() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = { "-l", "-d", "-s", "-x", "-v", "-m", "-f" };
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_ABC:
      lf::logic::abc::balance( boolOptionsValue["-l"], boolOptionsValue["-d"], boolOptionsValue["-s"], boolOptionsValue["-x"], boolOptionsValue["-v"] );
      break;
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsils::balance( boolOptionsValue["-m"], boolOptionsValue["-f"] );
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicBalance

class CmdLfLogicRewrite : public TclCmd
{
public:
  explicit CmdLfLogicRewrite( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {
        { "-l", "all", "bool", "" },
        { "-z", "all", "bool", "" },
        { "-d", "lsils", "bool", "" },
        { "-p", "lsils", "bool", "" },
        { "-v", "all", "bool", "" },
        { "-w", "all", "bool", "" } };
    setOptions( this, options );
  }

  ~CmdLfLogicRewrite() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = { "-l", "-z", "-d", "-p", "-v", "-w" };
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_ABC:
      lf::logic::abc::rewrite( boolOptionsValue["-l"], boolOptionsValue["-z"], boolOptionsValue["-v"], boolOptionsValue["-w"] );
      break;
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsils::rewrite( boolOptionsValue["-l"], boolOptionsValue["-z"], boolOptionsValue["-d"], boolOptionsValue["-p"], boolOptionsValue["-v"], boolOptionsValue["-w"] );
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicRewrite

class CmdLfLogicRefactor : public TclCmd
{
public:
  explicit CmdLfLogicRefactor( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {
        { "-z", "all", "bool", "" },
        { "-v", "all", "bool", "" },
        { "-N", "all", "int", "max support of the collapsed node." },
        { "-M", "abc", "int", "min number of nodes saved after one step." },
        { "-l", "abc", "bool", "" },
        { "-r", "lsils", "bool", "" },
        { "-d", "lsils", "bool", "" },
        { "-p", "lsils", "bool", "" } };
    setOptions( this, options );
  }

  ~CmdLfLogicRefactor() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = { "-z", "-v", "-l", "-r", "-d", "-p" };
    std::vector<std::string> intOptions = { "-M", "-N" };
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_ABC:
      lf::logic::abc::refactor( intOptionsValue["-N"], intOptionsValue["-M"], boolOptionsValue["-l"], boolOptionsValue["-z"], boolOptionsValue["-v"] );
      break;
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsils::refactor( intOptionsValue["-N"], boolOptionsValue["-z"], boolOptionsValue["-r"], boolOptionsValue["-d"], boolOptionsValue["-p"], boolOptionsValue["-v"] );
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicRefactor

class CmdLfLogicResub : public TclCmd
{
public:
  explicit CmdLfLogicResub( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {
        { "-K", "abc", "int", "the max cut size" },
        { "-N", "abc", "int", "max number of nodes to add." },
        { "-M", "abc", "int", "min number of nodes saved after one step." },
        { "-F", "abc", "int", "the number of fanout levels foir ODC computation." },
        { "-l", "all", "bool", "" },
        { "-z", "all", "bool", "" },
        { "-v", "abc", "bool", "" },
        { "-w", "abc", "bool", "" },
        { "-NI", "lsils", "int", "max support of the collapsed node." },
        { "-MD", "lsils", "int", "max divisors" },
        { "-MI", "lsils", "int", "max inserts" },
        { "-FLR", "lsils", "int", "fanout limit of root" },
        { "-FLD", "lsils", "int", "fanout limit divisor" },
        { "-W", "lsils", "int", "window size" },
        { "-d", "lsils", "bool", "" },
        { "-p", "lsils", "bool", "" } };
    setOptions( this, options );
  }

  ~CmdLfLogicResub() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = { "-l", "-z", "-v", "-w", "-d", "-p" };
    std::vector<std::string> intOptions = { "-K", "-N", "-M", "-F", "-NI", "-MD", "-MI", "-FLR", "-FLD", "-W" };
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_ABC:
      lf::logic::abc::resub( intOptionsValue["-K"], intOptionsValue["-N"], intOptionsValue["-M"], intOptionsValue["-F"],
                             boolOptionsValue["-l"], boolOptionsValue["-z"], boolOptionsValue["-v"], boolOptionsValue["-w"] );
      break;
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsils::resub( intOptionsValue["-NI"], intOptionsValue["-MD"], intOptionsValue["-MI"], intOptionsValue["-FLR"], intOptionsValue["-FLD"], intOptionsValue["-W"],
                               boolOptionsValue["-l"], boolOptionsValue["-d"], boolOptionsValue["-p"], boolOptionsValue["-v"] );
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicResub

class CmdLfLogicMapFPGA : public TclCmd
{
public:
  explicit CmdLfLogicMapFPGA( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {
        // Integer options with descriptions
        { "-K", "all", "int", "The number of LUT inputs (2 < num < 33)." },
        { "-C", "all", "int", "The max number of priority cuts (0 < num < 2^12)." },
        { "-F", "all", "int", "The number of area flow recovery iterations (num >= 0)." },
        { "-A", "all", "int", "The number of exact area recovery iterations (num >= 0)." },
        { "-G", "abc", "int", "The max AND/OR gate size for mapping (0 = unused)." },
        { "-R", "abc", "int", "The delay relaxation ratio (num >= 0)." },
        { "-N", "abc", "int", "The max size of non-decomposable nodes." },
        { "-T", "abc", "int", "The type of LUT structures." },
        { "-X", "abc", "int", "Delay of AND-gate in LUT library units." },
        { "-Y", "abc", "int", "Area of AND-gate in LUT library units." },
        { "-U", "abc", "int", "Number of LUT inputs for delay-driven LUT decomposition." },
        { "-Z", "abc", "int", "Number of LUT inputs for delay-driven LUT decomposition." },
        // double options with descriptions
        { "-D", "abc", "double", "Sets the delay constraint for the mapping." },
        { "-E", "abc", "double", "Sets epsilon used for tie-breaking." },
        { "-W", "abc", "double", "Sets wire delay between adjacent LUTs." },
        // String options with descriptions
        { "-S", "abc", "string", "String representing the LUT structure." },
        { "-J", "abc", "string", "String representing the LUT structure (new method)." },
        // Boolean switches with descriptions
        { "-q", "abc", "bool", "Toggles preprocessing using several starting points." },
        { "-a", "abc", "bool", "Toggles area-oriented mapping." },
        { "-r", "abc", "bool", "Enables expansion/reduction of the best cuts." },
        { "-l", "abc", "bool", "Optimizes latch paths for delay, other paths for area." },
        { "-e", "abc", "bool", "Uses edge-based cut selection heuristics." },
        { "-p", "abc", "bool", "Uses power-aware cut selection heuristics." },
        { "-m", "abc", "bool", "Enables cut minimization by removing vacuous variables." },
        { "-s", "abc", "bool", "Toggles delay-oriented mapping used with -S <NN>." },
        { "-d", "abc", "bool", "Toggles deriving local AIGs using bi-decomposition." },
        { "-b", "abc", "bool", "Toggles the use of one special feature." },
        { "-g", "abc", "bool", "Toggles delay optimization by SOP balancing." },
        { "-x", "abc", "bool", "Toggles delay optimization by DSD balancing." },
        { "-y", "abc", "bool", "Toggles delay optimization with recorded library." },
        { "-u", "abc", "bool", "Toggles delay optimization with SAT-based library." },
        { "-o", "abc", "bool", "Toggles using buffers to decouple combinational outputs." },
        { "-j", "abc", "bool", "Toggles enabling additional check." },
        { "-i", "abc", "bool", "Toggles using cofactoring variables." },
        { "-k", "abc", "bool", "Toggles matching based on precomputed DSD manager." },
        { "-t", "abc", "bool", "Toggles optimizing average rather than maximum level." },
        { "-n", "abc", "bool", "Toggles computing DSDs of the cut functions." },
        { "-c", "abc", "bool", "Toggles computing truth tables in a new way." },
        { "-v", "all", "bool", "Toggles verbose output." } };
    setOptions( this, options );
  }

  ~CmdLfLogicMapFPGA() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = { "-S", "-J" };
    std::vector<std::string> boolOptions = { "-q", "-m", "-s", "-d", "-b", "-g", "-x", "-y", "-u", "-o", "-j", "-i", "-k", "-t", "-n", "-c", "-v" };
    std::vector<std::string> intOptions = { "-K", "-C", "-F", "-A", "-G", "-R", "-N", "-T", "-X", "-Y", "-U", "-Z" };
    std::vector<std::string> doubleOptions = { "-D", "-E", "-W" };
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_ABC:
      lf::logic::abc::map_fpga( intOptionsValue["-K"], intOptionsValue["-C"], intOptionsValue["-F"], intOptionsValue["-A"],
                                intOptionsValue["-G"], intOptionsValue["-R"], intOptionsValue["-N"], intOptionsValue["-T"],
                                intOptionsValue["-X"], intOptionsValue["-Y"],
                                doubleOptionsValue["-D"], doubleOptionsValue["-E"], doubleOptionsValue["-W"],
                                strOptionsValue["-S"], strOptionsValue["-J"],
                                boolOptionsValue["-q"], boolOptionsValue["-a"], boolOptionsValue["-r"], boolOptionsValue["-l"],
                                boolOptionsValue["-e"], boolOptionsValue["-p"], boolOptionsValue["-m"], boolOptionsValue["-s"],
                                boolOptionsValue["-d"], boolOptionsValue["-b"], boolOptionsValue["-g"], boolOptionsValue["-x"],
                                boolOptionsValue["-y"], boolOptionsValue["-u"], boolOptionsValue["-o"], boolOptionsValue["-j"],
                                boolOptionsValue["-i"], boolOptionsValue["-k"], boolOptionsValue["-t"], boolOptionsValue["-n"],
                                boolOptionsValue["-c"], boolOptionsValue["-v"] );
      break;
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsils::map_fpga( intOptionsValue["-K"], intOptionsValue["-C"], intOptionsValue["-F"], intOptionsValue["-A"], boolOptionsValue["-v"] );
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicMapFPGA

class CmdLfLogicMapASIC : public TclCmd
{
public:
  explicit CmdLfLogicMapASIC( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {
        { "-D", "abc", "double", "Sets the global required times. Default is not used." },
        { "-A", "abc", "double", "\"Area multiplier\" to bias gate selection. Default is 0.00." },
        { "-B", "abc", "double", "\"Delay multiplier\" to bias gate selection. Default is 0.00." },
        { "-F", "abc", "double", "The logarithmic fanout delay parameter. Default is 0.00." },
        { "-S", "abc", "double", "The slew parameter used to generate the library. Default is 0.00." },
        { "-G", "abc", "double", "The gain parameter used to generate the library. Default is 250.00." },
        { "-M", "abc", "int", "Skip gate classes whose size is less than this. Default is 0." },
        { "-a", "abc", "bool", "Toggles area-only mapping. Default is no." },
        { "-r", "abc", "bool", "Toggles area recovery. Default is yes." },
        { "-s", "abc", "bool", "Toggles sweep after mapping. Default is no." },
        { "-p", "abc", "bool", "Optimizes power by minimizing switching. Default is no." },
        { "-f", "abc", "bool", "Do not use large gates to map high-fanout nodes. Default is no." },
        { "-u", "abc", "bool", "Use standard-cell profile. Default is no." },
        { "-o", "abc", "bool", "Toggles using buffers to decouple combinational outputs. Default is no." },
        { "-v", "abc", "bool", "" } };
    setOptions( this, options );
  }

  ~CmdLfLogicMapASIC() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = { "-a", "-r", "-s", "-p", "-f", "-u", "-o", "-v" };
    std::vector<std::string> intOptions = { "-M" };
    std::vector<std::string> doubleOptions = { "-D", "-A", "-B", "-F", "-S", "-G" };
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_ABC:
      lf::logic::abc::map_asic( doubleOptionsValue["-D"], doubleOptionsValue["-A"], doubleOptionsValue["-B"], doubleOptionsValue["-F"], doubleOptionsValue["-S"], doubleOptionsValue["-G"],
                                intOptionsValue["-M"],
                                boolOptionsValue["-a"], boolOptionsValue["-r"], boolOptionsValue["-s"], boolOptionsValue["-p"], boolOptionsValue["-f"], boolOptionsValue["-u"], boolOptionsValue["-o"],
                                boolOptionsValue["-v"] );
      break;
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsils::map_asic();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicMapASIC

class CmdLfLogicXMGRewrite : public TclCmd
{
public:
  explicit CmdLfLogicXMGRewrite( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfLogicXMGRewrite() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsnbu::xmgrw();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicXMGRewrite

class CmdLfLogicXAG1 : public TclCmd
{
public:
  explicit CmdLfLogicXAG1( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfLogicXAG1() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsnbu::xag_mprm2_area_opt();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicXAG1

class CmdLfLogicXAG2 : public TclCmd
{
public:
  explicit CmdLfLogicXAG2( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfLogicXAG2() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsnbu::xag_mprm_multi_mult_opt();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicXAG2

class CmdLfLogicExactMap : public TclCmd
{
public:
  explicit CmdLfLogicExactMap( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfLogicExactMap() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsnbu::exact_map();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicExactMap

class CmdLfLogicLutResyn : public TclCmd
{
public:
  explicit CmdLfLogicLutResyn( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfLogicLutResyn() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsnbu::lut_resyn();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicLutResyn

class CmdLfLogicMighty : public TclCmd
{
public:
  explicit CmdLfLogicMighty( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfLogicMighty() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsnbu::mighty_rewrite();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicMighty

class CmdLfLogicXAGBalance : public TclCmd
{
public:
  explicit CmdLfLogicXAGBalance( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfLogicXAGBalance() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsnbu::xagba();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicXAGBalance

class CmdLfLogicXAGResub : public TclCmd
{
public:
  explicit CmdLfLogicXAGResub( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfLogicXAGResub() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsnbu::xagrs();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicXAGResub

class CmdLfLogicXAGRewrite : public TclCmd
{
public:
  explicit CmdLfLogicXAGRewrite( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfLogicXAGRewrite() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsnbu::xagrw();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicXAGRewrite

class CmdLfLogicXMGResub : public TclCmd
{
public:
  explicit CmdLfLogicXMGResub( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // set the description
    std::string description = "";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );
    // set the options
    std::vector<lfCmdOption> options = {};
    setOptions( this, options );
  }

  ~CmdLfLogicXMGResub() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = {};
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = {};
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
      lf::logic::lsnbu::xmgrs();
      break;
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
}; // class CmdLfLogicXMGResub

// PKU
class CmdLfLogicRLTestBasic : public TclCmd
{
public:
  explicit CmdLfLogicRLTestBasic( const char* cmd_name ) : TclCmd( cmd_name )
  {
    // 命令描述：明确说明使用basic特征模式
    this->set_description( "RL test command with fixed 'basic' feature mode (obs_dim=14)" );
    this->set_domain( "logic" );

    // 使用setOptions统一设置选项
    std::vector<lfCmdOption> options = {
        { "-test_list", "", "string", "Path to test circuit list file" },
        { "-result_dir", "", "string", "Directory to save results" },
        { "-test_dir", "", "string", "Directory containing test circuits" } };
    setOptions( this, options );
  }

  ~CmdLfLogicRLTestBasic() override = default;

  unsigned check() override
  {
    // 检查必填参数
    std::vector<std::string> essential = { "-test_list" };
    unsigned check_result = checkEssentialOptions( this, essential );
    if ( !check_result )
      return 0;
    return 1;
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    // 提取命令选项值
    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = { "-test_list", "-result_dir", "-test_dir" };
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions,
                    strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue,
                    strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );
    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();
    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
    {
      // 获取Python脚本路径（假设位于固定位置）
      std::string python_script = "./src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/rl_test.py";

      // 检查Python脚本是否存在
      if ( access( python_script.c_str(), F_OK ) == -1 )
      {
        std::cerr << "Python script not found: " << python_script << std::endl;
        return 0;
      }

      // 创建临时shell脚本
      char temp_sh_name[] = "./src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/rl_test_basic_XXXXXX.sh";
      int fd = mkstemps( temp_sh_name, 3 ); // 创建临时.sh文件
      if ( fd == -1 )
      {
        std::cerr << "Failed to create temporary shell script" << std::endl;
        return 0;
      }

      // 构建shell脚本内容
      std::ostringstream sh_content;
      sh_content << "#!/bin/bash\n\n";

      // 激活conda环境
      sh_content << "# Activate conda environment\n";
      sh_content << "source \"/opt/conda/etc/profile.d/conda.sh\"\n";
      sh_content << "conda activate rlgym\n\n";

      // 添加Python执行命令及所有参数
      sh_content << "# Execute Python script with parameters\n";
      sh_content << "python \"" << python_script << "\" \\\n";
      sh_content << "  --feature_mode \"" << "basic" << "\" \\\n";
      sh_content << "  --test_list \"" << strOptionsValue["-test_list"] << "\" \\\n";
      sh_content << "  --model_name \"" << "./src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/model_basic.zip" << "\" \\\n";
      sh_content << "  --result_dir \"" << strOptionsValue["-result_dir"] << "\" \\\n";
      sh_content << "  --test_dir \"" << strOptionsValue["-test_dir"] << "\" \\\n";

      sh_content << "# Deactivate conda environment\n";
      sh_content << "conda deactivate\n\n";

      sh_content << "# Capture exit status\n";
      sh_content << "exit_code=$?\n";
      sh_content << "exit $exit_code\n";

      // 写入shell脚本内容
      std::string sh_str = sh_content.str();
      if ( write( fd, sh_str.c_str(), sh_str.size() ) != static_cast<ssize_t>( sh_str.size() ) )
      {
        std::cerr << "Failed to write shell script" << std::endl;
        close( fd );
        unlink( temp_sh_name );
        return 0;
      }
      close( fd );

      // 设置执行权限
      chmod( temp_sh_name, S_IRWXU );

      // 执行shell脚本
      std::string command = temp_sh_name;
      int status = system( command.c_str() );

      // 清理临时文件
      unlink( temp_sh_name );

      if ( status != 0 )
      {
        std::cerr << "Script execution failed with status: " << status << std::endl;
        return 0;
      }
      break;
    }
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
};

class CmdLfLogicRLTestGlitch : public TclCmd
{
public:
  explicit CmdLfLogicRLTestGlitch( const char* cmd_name ) : TclCmd( cmd_name )
  {
    // 命令描述：明确说明使用glitch特征模式
    this->set_description( "RL test command with fixed 'glitch' feature mode (obs_dim=89)" );
    this->set_domain( "logic" );

    // 使用setOptions统一设置选项
    std::vector<lfCmdOption> options = {
        { "-test_list", "", "string", "Path to test circuit list file" },
        { "-result_dir", "", "string", "Directory to save results" },
        { "-test_dir", "", "string", "Directory containing test circuits" } };
    setOptions( this, options );
  }

  ~CmdLfLogicRLTestGlitch() override = default;

  unsigned check() override
  {
    // 检查必填参数
    std::vector<std::string> essential = { "-test_list" };
    unsigned check_result = checkEssentialOptions( this, essential );
    if ( !check_result )
      return 0;
    return 1;
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    // 提取命令选项值
    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = { "-test_list", "-result_dir", "-test_dir" };
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions,
                    strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue,
                    strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );
    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();
    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
    {
      // 获取Python脚本路径（假设位于固定位置）
      std::string python_script = "./src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/rl_test.py";

      // 检查Python脚本是否存在
      if ( access( python_script.c_str(), F_OK ) == -1 )
      {
        std::cerr << "Python script not found: " << python_script << std::endl;
        return 0;
      }

      // 创建临时shell脚本
      char temp_sh_name[] = "./src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/rl_test_glitch_XXXXXX.sh";
      int fd = mkstemps( temp_sh_name, 3 ); // 创建临时.sh文件
      if ( fd == -1 )
      {
        std::cerr << "Failed to create temporary shell script" << std::endl;
        return 0;
      }

      // 构建shell脚本内容
      std::ostringstream sh_content;
      sh_content << "#!/bin/bash\n\n";

      // 激活conda环境
      sh_content << "# Activate conda environment\n";
      sh_content << "source \"/opt/conda/etc/profile.d/conda.sh\"\n";
      sh_content << "conda activate rlgym\n\n";

      // 添加Python执行命令及所有参数
      sh_content << "# Execute Python script with parameters\n";
      sh_content << "python \"" << python_script << "\" \\\n";
      sh_content << "  --feature_mode \"" << "glitch" << "\" \\\n";
      sh_content << "  --test_list \"" << strOptionsValue["-test_list"] << "\" \\\n";
      sh_content << "  --model_name \"" << "./src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/model_glitch.zip" << "\" \\\n";
      sh_content << "  --result_dir \"" << strOptionsValue["-result_dir"] << "\" \\\n";
      sh_content << "  --test_dir \"" << strOptionsValue["-test_dir"] << "\" \\\n";

      sh_content << "# Deactivate conda environment\n";
      sh_content << "conda deactivate\n\n";

      sh_content << "# Capture exit status\n";
      sh_content << "exit_code=$?\n";
      sh_content << "exit $exit_code\n";

      // 写入shell脚本内容
      std::string sh_str = sh_content.str();
      if ( write( fd, sh_str.c_str(), sh_str.size() ) != static_cast<ssize_t>( sh_str.size() ) )
      {
        std::cerr << "Failed to write shell script" << std::endl;
        close( fd );
        unlink( temp_sh_name );
        return 0;
      }
      close( fd );

      // 设置执行权限
      chmod( temp_sh_name, S_IRWXU );

      // 执行shell脚本
      std::string command = temp_sh_name;
      int status = system( command.c_str() );

      // 清理临时文件
      unlink( temp_sh_name );

      if ( status != 0 )
      {
        std::cerr << "Script execution failed with status: " << status << std::endl;
        return 0;
      }
      break;
    }
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
};

class CmdLfLogicDITT : public TclCmd
{
public:
  explicit CmdLfLogicDITT( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // 设置命令描述和域
    std::string description = "Perform exact logic synthesis using DITT (Dynamic Integer Temporal Transformation) method";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );

    // 设置命令选项
    std::vector<lfCmdOption> options = {
        { "-functions", "", "string", "List of boolean functions (hex strings)" },
        { "-r", "", "int", "Number of steps (r value)" },
        { "-sat_output", "", "string", "Path to save SAT CNF encoding" },
        { "-circuit_output", "", "string", "Path to save decoded circuit" },
        { "-solver", "", "string", "SAT solver to use (kissat/cadical)" } };
    setOptions( this, options );
  }

  ~CmdLfLogicDITT() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = { "-functions" };
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    // 提取命令选项值
    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    std::vector<std::string> strOptions = { "-functions", "-sat_output", "-circuit_output", "-solver" };
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = { "-r" };
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
    {

      // 分割函数列表字符串
      std::vector<exact::Boolean> func_strs = splitString( strOptionsValue["-functions"], ',' );
      // 创建DITT对象
      exact::Technology tech;
      exact::DITT ditt( func_strs );
      ditt.r = intOptionsValue["-r"];

      // 编码为SAT问题
      exact::Encoding encoding = ditt.encode( true );

      // 保存SAT编码
      if ( !strOptionsValue["-sat_output"].empty() )
      {
        std::ofstream sat_file( strOptionsValue["-sat_output"] );
        if ( sat_file.is_open() )
        {
          encoding.write_dimacs( sat_file );
          sat_file.close();
          std::cout << "SAT encoding saved to: " << strOptionsValue["-sat_output"] << std::endl;
        }
        else
        {
          std::cerr << "Failed to open SAT output file: " << strOptionsValue["-sat_output"] << std::endl;
          return 0;
        }
      }

      // 调用SAT求解器
      std::cout << "Running " << strOptionsValue["-solver"] << " for synthesis..." << std::endl;
      auto [success, solution] = exact::synthesis( &ditt, strOptionsValue["-solver"].c_str(), std::cout );
      if ( !success )
      {
        std::cerr << "Synthesis failed (no solution found)" << std::endl;
        return 0;
      }

      // 解码并保存电路
      if ( !strOptionsValue["-circuit_output"].empty() )
      {
        ditt.decode( solution, strOptionsValue["-circuit_output"] );
        std::cout << "Decoded circuit saved to: " << strOptionsValue["-circuit_output"] << std::endl;
      }
      break;
    }
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }

private:
  // 辅助函数：将逗号分隔的字符串分割为向量
  std::vector<exact::Boolean> splitString( const std::string& str, char delimiter )
  {
    std::vector<exact::Boolean> tokens;
    std::string token;
    std::istringstream tokenStream( str );
    while ( std::getline( tokenStream, token, delimiter ) )
    {
      if ( !token.empty() ) // 忽略空字符串（处理连续逗号的情况）
        tokens.push_back( exact::Boolean( token ) );
    }
    return tokens;
  }
};

class CmdLfLogicMSV : public TclCmd
{
public:
  explicit CmdLfLogicMSV( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // 设置命令描述和域
    std::string description = "Perform exact logic synthesis using MSV (Multi-Stage Variable) method";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );

    // 设置命令选项（与 MSV 类参数对应）
    std::vector<lfCmdOption> options = {
        { "-functions", "", "string", "List of boolean functions (hex strings, comma-separated)" },
        { "-r", "", "int", "Number of synthesis steps (r value)" },
        { "-sat_output", "", "string", "Path to save SAT CNF encoding (.cnf)" },
        { "-circuit_output", "", "string", "Path to save decoded circuit (.blif)" },
        { "-solver", "", "string", "SAT solver to use (kissat/cadical)" } };
    setOptions( this, options );
  }

  ~CmdLfLogicMSV() override = default;

  unsigned check() override
  {
    // 检查必填选项
    std::vector<std::string> essential = { "-functions" };
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    // 提取选项值到对应映射表
    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    // 定义选项类型分类
    std::vector<std::string> strOptions = { "-functions", "-sat_output", "-circuit_output", "-solver" };
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = { "-r" };
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    // 提取选项值
    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    // 分割函数列表（逗号分隔的字符串→向量）
    std::vector<exact::Boolean> func_strs = splitString( strOptionsValue["-functions"], ',' );
    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
    {
      // 执行 MSV 逻辑综合流程
      // 创建 MSV 对象
      exact::Technology tech;
      exact::MSV msv( func_strs );
      msv.r = intOptionsValue["-r"]; // 设置步骤数

      // 编码为 SAT 问题
      exact::Encoding encoding = msv.encode( true ); // 保留变量注释

      // 保存 SAT 编码文件（.cnf）
      if ( !strOptionsValue["-sat_output"].empty() )
      {
        std::ofstream sat_file( strOptionsValue["-sat_output"] );
        if ( sat_file.is_open() )
        {
          encoding.write_dimacs( sat_file );
          sat_file.close();
          std::cout << "SAT encoding saved to: " << strOptionsValue["-sat_output"] << std::endl;
        }
        else
        {
          std::cerr << "Failed to open SAT output file: " << strOptionsValue["-sat_output"] << std::endl;
          return 0;
        }
      }

      // 调用 SAT 求解器进行综合
      std::cout << "Running " << strOptionsValue["-solver"] << " for MSV synthesis..." << std::endl;
      auto [success, solution] = exact::synthesis( &msv, strOptionsValue["-solver"].c_str(), std::cout );
      if ( !success )
      {
        std::cerr << "MSV synthesis failed: no solution found" << std::endl;
        return 0;
      }

      // 解码 SAT 解为逻辑电路（.blif）
      if ( !strOptionsValue["-circuit_output"].empty() )
      {
        msv.decode( solution, strOptionsValue["-circuit_output"] );
        std::cout << "Decoded circuit saved to: " << strOptionsValue["-circuit_output"] << std::endl;
      }

      break;
    }
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }

private:
  // 辅助函数：将逗号分隔的字符串分割为向量
  std::vector<exact::Boolean> splitString( const std::string& str, char delimiter )
  {
    std::vector<exact::Boolean> tokens;
    std::string token;
    std::istringstream tokenStream( str );
    while ( std::getline( tokenStream, token, delimiter ) )
    {
      if ( !token.empty() ) // 忽略空字符串（处理连续逗号的情况）
        tokens.push_back( exact::Boolean( token ) );
    }
    return tokens;
  }
};

class CmdLfLogicSSV : public TclCmd
{
public:
  explicit CmdLfLogicSSV( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // 设置命令描述和域
    std::string description = "Perform exact logic synthesis using SSV (Symmetric Stage Variable) method";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );

    // 设置命令选项（与 SSV 类参数对应）
    std::vector<lfCmdOption> options = {
        { "-functions", "", "string", "List of boolean functions (hex strings, comma-separated)" },
        { "-r", "", "int", "Number of synthesis steps (r value)" },
        { "-sat_output", "", "string", "Path to save SAT CNF encoding (.cnf)" },
        { "-circuit_output", "", "string", "Path to save decoded circuit (.blif)" },
        { "-solver", "", "string", "SAT solver to use (kissat/cadical)" } };
    setOptions( this, options );
  }

  ~CmdLfLogicSSV() override = default;

  unsigned check() override
  {
    // 检查必填选项（逻辑函数列表为必需参数）
    std::vector<std::string> essential = { "-functions" };
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    // 提取选项值到对应映射表
    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    // 定义选项类型分类
    std::vector<std::string> strOptions = { "-functions", "-sat_output", "-circuit_output", "-solver" };
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = { "-r" };
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    // 提取选项值
    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    // 分割函数列表（逗号分隔的字符串→向量）
    std::vector<exact::Boolean> func_strs = splitString( strOptionsValue["-functions"], ',' );
    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
    {
      // 创建 SSV 对象
      exact::Technology tech;
      exact::SSV ssv( func_strs );
      ssv.r = intOptionsValue["-r"]; // 设置步骤数

      // 编码为 SAT 问题
      exact::Encoding encoding = ssv.encode( true ); // 保留变量注释

      // 保存 SAT 编码文件（.cnf）
      if ( !strOptionsValue["-sat_output"].empty() )
      {
        std::ofstream sat_file( strOptionsValue["-sat_output"] );
        if ( sat_file.is_open() )
        {
          encoding.write_dimacs( sat_file );
          sat_file.close();
          std::cout << "SAT encoding saved to: " << strOptionsValue["-sat_output"] << std::endl;
        }
        else
        {
          std::cerr << "Failed to open SAT output file: " << strOptionsValue["-sat_output"] << std::endl;
          return 0;
        }
      }

      // 调用 SAT 求解器进行综合
      std::cout << "Running " << strOptionsValue["-solver"] << " for SSV synthesis..." << std::endl;
      auto [success, solution] = synthesis( &ssv, strOptionsValue["-solver"].c_str(), std::cout );
      if ( !success )
      {
        std::cerr << "SSV synthesis failed: no solution found" << std::endl;
        return 0;
      }

      // 解码 SAT 解为逻辑电路（.blif）
      if ( !strOptionsValue["-circuit_output"].empty() )
      {
        ssv.decode( solution, strOptionsValue["-circuit_output"] );
        std::cout << "Decoded circuit saved to: " << strOptionsValue["-circuit_output"] << std::endl;
      }

      break;
    }
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }

private:
  // 辅助函数：将逗号分隔的字符串分割为向量
  std::vector<exact::Boolean> splitString( const std::string& str, char delimiter )
  {
    std::vector<exact::Boolean> tokens;
    std::string token;
    std::istringstream tokenStream( str );
    while ( std::getline( tokenStream, token, delimiter ) )
    {
      if ( !token.empty() ) // 忽略空字符串（处理连续逗号的情况）
        tokens.push_back( exact::Boolean( token ) );
    }
    return tokens;
  }
};

class CmdLfLogicSSVIncremental : public TclCmd
{
public:
  explicit CmdLfLogicSSVIncremental( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // 设置命令描述和域
    std::string description = "Perform incremental exact logic synthesis using SSV_Incremental method";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );

    // 命令选项
    std::vector<lfCmdOption> options = {
        { "-num_inputs", "", "int", "" },
        { "-function", "", "string", "" },
        { "-exp", "", "string", "" },
        { "-output_file", "", "string", "" } };
    setOptions( this, options );
  }

  ~CmdLfLogicSSVIncremental() override = default;

  unsigned check() override
  {
    // 检查必填选项
    std::vector<std::string> essential = { "-num_inputs", "-function", "-output_file", "-exp" };
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    // 提取选项值到对应映射表
    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    // 定义选项类型分类
    std::vector<std::string> strOptions = { "-function", "-output_file", "-exp" };
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = { "-num_inputs" };
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    // 提取选项值
    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );
    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
    {
      // 提取参数
      int num_inputs = intOptionsValue["-num_inputs"];
      std::string hex = strOptionsValue["-function"];
      std::string output_file = strOptionsValue["-output_file"];
      std::string exp = strOptionsValue["-exp"];
      std::string temp;

      exact::Boolean func( hex );
      std::vector<exact::Boolean> funcs = { func };

      exact::SSV_Incremental ssv( funcs );
      // char similar_option[100] = "01001";   //for mute
      char similar_option[100] = "010"; // for mute_last
      strcat( similar_option, exp.c_str() );
      ssv.set_similar_function( "mute_last", similar_option );
      std::cout << ssv.get_similar_function() << "\n";
      exact::SSV_Incremental* encoder = &ssv;

      encoder->r = num_inputs - 1;

      auto [success, solution] = incremental_synthesis( encoder, "kissat", std::cout );
      if ( !success )
      {
        std::cerr << "SSV_Incremental synthesis failed for function: " << hex << std::endl;
        return 0;
      }
      ssv.decode( solution, output_file );
      std::cout << "Decoded circuit saved to: " << output_file << std::endl;

      break;
    }
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
};

class CmdLfLogicSSVPower : public TclCmd
{
public:
  explicit CmdLfLogicSSVPower( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // 设置命令描述和域
    std::string description = "Perform power-driven exact logic synthesis using SSV_Power method";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );

    // 定义命令选项（与 generate_netlist_library_power 参数对应）
    std::vector<lfCmdOption> options = {
        { "-input", "", "string", "Input file path" },
        { "-output", "", "string", "Output file path to save the generated netlist library" },
        { "-num_inputs", "", "int", "Number of input variables for the boolean functions" },
        { "-num_classes", "", "int", "Number of classes for input probability discretization" },
        { "-average", "", "bool", "Whether to use average strategy (default: true)" },
        { "-start_index", "", "int", "Start index for processing functions (default: 0)" },
        { "-partition_size", "", "int", "Maximum number of functions to process (default: INT16_MAX)" } };
    setOptions( this, options );
  }

  ~CmdLfLogicSSVPower() override = default;

  unsigned check() override
  {
    std::vector<std::string> essential = { "-input", "-output", "-num_inputs", "-num_classes" };
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    // 定义参数映射表
    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    // 分类定义选项类型
    std::vector<std::string> strOptions = { "-input", "-output" };
    std::vector<std::string> boolOptions = { "-average" };
    std::vector<std::string> intOptions = { "-num_inputs", "-num_classes", "-start_index", "-partition_size" };
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    // 提取参数到映射表
    extractOptions(
        this,
        strOptions, boolOptions, intOptions, doubleOptions,
        strvecOptions, intvecOptions, doublevecOptions,
        strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue,
        strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
    {
      std::string input_file = strOptionsValue.at( "-input" );
      std::string output_file = strOptionsValue.at( "-output" );
      int num_inputs = intOptionsValue.at( "-num_inputs" );
      int num_classes = intOptionsValue.at( "-num_classes" );
      bool average = boolOptionsValue.at( "-average" );
      int start_index = intOptionsValue.at( "-start_index" );
      int partition_size = intOptionsValue.at( "-partition_size" );

      // 调用核心函数
      exact::generate_netlist_library_power_new(
          input_file,
          output_file,
          num_inputs,
          num_classes,
          average,
          start_index,
          partition_size );
      break;
    }
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
};

class CmdLfLogicLutRewrite : public TclCmd
{
public:
  explicit CmdLfLogicLutRewrite( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    std::string description = "Perform LUT rewriting on netlist using optimal library";
    this->set_description( description );
    this->set_domain( "logic" );

    // 定义命令选项
    std::vector<lfCmdOption> options = {
        { "-input", "", "string", "Input BLIF file path (without .blif extension)" },
        { "-lib", "", "string", "Optimal library file path" },
        { "-output_dir", "", "string", "Output directory for rewritten netlist" },
        { "-input_dir", "", "string", "Input directory for BLIF files" } };
    setOptions( this, options );
  }

  ~CmdLfLogicLutRewrite() override = default;

  unsigned check() override
  {
    // 检查必选选项
    std::vector<std::string> essential = { "-input", "-lib", "-output_dir" };
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 1;

    // 定义参数映射表
    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    // 其他类型映射表（未使用）
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    // 分类定义选项类型
    std::vector<std::string> strOptions = { "-input", "-lib", "-output_dir", "-input_dir" };
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    // 提取参数到映射表
    extractOptions(
        this,
        strOptions, boolOptions, intOptions, doubleOptions,
        strvecOptions, intvecOptions, doublevecOptions,
        strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue,
        strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
    {
      std::string input_name = strOptionsValue.at( "-input" );
      std::string lib_path = strOptionsValue.at( "-lib" );
      std::string output_dir = strOptionsValue.at( "-output_dir" );
      std::string input_dir = strOptionsValue.at( "-input_dir" );

      // 构建完整路径
      std::string input_path = input_dir + input_name + ".blif";
      std::string output_path = output_dir + input_name + ".blif";

      // 加载网表
      NET::Netlist netlist;
      NET::read_blif( input_path, netlist );
      std::cout << "Finish netlist loading: " << input_path << std::endl;

      // 执行LUT重写
      NET::lut_rewrite_power( netlist, lib_path );
      std::cout << "Power-driven LUT rewriting completed" << std::endl;

      // 保存结果
      NET::write_blif( output_path, netlist );
      std::cout << "Rewritten netlist saved to: " << output_path << std::endl;

      break;
    }
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1;
  }
};

class CmdLfLogicTechMapping : public TclCmd
{
public:
  explicit CmdLfLogicTechMapping( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // 设置命令描述和域
    std::string description = "Perform technology mapping using cut enumeration and standard cell library";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );

    // 命令选项（与技术映射功能对应）
    std::vector<lfCmdOption> options = {
        { "-input", "", "string", "Input netlist file (.blif)" },
        { "-output", "", "string", "Output mapped netlist file (.v for Verilog)" },
        { "-tech_lib", "", "string", "Technology library file (.lib in Liberty format)" } };
    setOptions( this, options );
  }

  ~CmdLfLogicTechMapping() override = default;

  unsigned check() override
  {
    // 检查必填选项
    std::vector<std::string> essential = { "-input", "-output", "-tech_lib" };
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    // 提取选项值到对应映射表
    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    // 定义选项类型分类
    std::vector<std::string> strOptions = { "-input", "-output", "-tech_lib" };
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    // 提取选项值
    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
    {
      // 执行技术映射核心逻辑
      PASyn::technology_mapping_api( strOptionsValue["-input"], strOptionsValue["-tech_lib"], strOptionsValue["-output"] );

      std::cout << "Technology mapping completed successfully." << std::endl;
      break;
    }
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1; // 成功执行
  }
};

class CmdLfLogicCalculatePower : public TclCmd
{
public:
  explicit CmdLfLogicCalculatePower( const char* cmd_name )
      : TclCmd( cmd_name )
  {
    // 设置命令描述和域
    std::string description = "Calculate power consumption (static/dynamic/internal/wire) of a netlist";
    this->set_description( description );
    std::string domain = "logic";
    this->set_domain( domain );

    // 命令选项（与功耗计算功能对应）
    std::vector<lfCmdOption> options = {
        { "-input", "", "string", "Input netlist file (.blif)" },
        { "-tech_lib", "", "string", "Technology library file (.lib in Liberty format)" },
        { "-output", "", "string", "Output file to save power results (optional, if not set print to console)" } };
    setOptions( this, options );
  }

  ~CmdLfLogicCalculatePower() override = default;

  unsigned check() override
  {
    // 检查必填选项
    std::vector<std::string> essential = { "-input", "-tech_lib" };
    return checkEssentialOptions( this, essential );
  }

  unsigned exec() override
  {
    if ( !check() )
      return 0;

    // 提取选项值到对应映射表
    std::map<std::string, std::string> strOptionsValue;
    std::map<std::string, bool> boolOptionsValue;
    std::map<std::string, int> intOptionsValue;
    std::map<std::string, double> doubleOptionsValue;
    std::map<std::string, std::vector<std::string>> strvecOptionsValue;
    std::map<std::string, std::vector<int>> intvecOptionsValue;
    std::map<std::string, std::vector<double>> doublevecOptionsValue;

    // 定义选项类型分类
    std::vector<std::string> strOptions = { "-input", "-tech_lib", "-output" };
    std::vector<std::string> boolOptions = {};
    std::vector<std::string> intOptions = {};
    std::vector<std::string> doubleOptions = {};
    std::vector<std::string> strvecOptions = {};
    std::vector<std::string> intvecOptions = {};
    std::vector<std::string> doublevecOptions = {};

    // 提取选项值
    extractOptions( this, strOptions, boolOptions, intOptions, doubleOptions, strvecOptions, intvecOptions, doublevecOptions,
                    strOptionsValue, boolOptionsValue, intOptionsValue, doubleOptionsValue, strvecOptionsValue, intvecOptionsValue, doublevecOptionsValue );

    auto anchor_tool_domain = lfAnchorINST->get_anchor_tool_domain();

    switch ( anchor_tool_domain )
    {
    case lf::misc::E_LF_ANCHOR_TOOL::E_LF_ANCHOR_TOOL_LOGIC_LSILS:
    {

      std::string input = strOptionsValue["-input"];
      std::string tech_lib = strOptionsValue["-tech_lib"];
      std::cout << 1 << std::endl;
      std::vector<double> power_results = PASyn::calculate_power_api( input, tech_lib, 0 );
      std::cout << 2 << std::endl;
      // 格式化输出内容
      std::stringstream output_ss;
      output_ss << "Power Consumption Breakdown:" << std::endl;
      output_ss << "  Static Power:    " << power_results[0] << " W" << std::endl;
      output_ss << "  Dynamic Power:   " << power_results[1] << " W" << std::endl;
      output_ss << "  Internal Power:  " << power_results[2] << " W" << std::endl;
      output_ss << "  Wire Power:      " << power_results[3] << " W" << std::endl;
      output_ss << "  Total Power:     " << power_results[4] << " W" << std::endl;

      // 输出到文件或控制台
      if ( !strOptionsValue["-output"].empty() )
      {
        // 保存到文件
        std::ofstream output_file( strOptionsValue["-output"] );
        if ( !output_file.is_open() )
        {
          std::cerr << "Failed to open output file: " << strOptionsValue["-output"] << std::endl;
          return 0;
        }
        output_file << output_ss.str();
        output_file.close();
        std::cout << "Power results saved to: " << strOptionsValue["-output"] << std::endl;
      }
      else
      {
        // 打印到控制台
        std::cout << output_ss.str() << std::endl;
      }

      std::cout << "Power calculation completed successfully." << std::endl;
      break;
    }
    default:
      std::cerr << "Unsupported anchor domain, please use anchor to set the anchor!" << std::endl;
      return 0;
    }
    return 1; // 成功执行
  }
};

} // namespace tcl
} // namespace lf

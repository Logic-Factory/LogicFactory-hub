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

} // namespace tcl
} // namespace lf
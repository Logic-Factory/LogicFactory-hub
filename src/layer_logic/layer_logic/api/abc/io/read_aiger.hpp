#pragma once

#include "layer_logic/logic_manager.hpp"
#include "layer_logic/api/abc/frame.hpp"
#include "utility/string.hpp"

#include <cstdio>
#include <string>

namespace lf
{

namespace logic
{

namespace abc
{

/**
 * @brief Reads file into the current logic network.
 * @example
 *  read_aiger [options] [filename]
 *  options: -c
 * @note
 */
void read_aiger( const std::string& file, bool is_checking = false )
{
  // check the current network type
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_ABC_LOGIC_AIG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_ABC_LOGIC_AIG )
  {
    std::cerr << "Unmatched network type." << std::endl;
    return;
  }

  auto ntk_ptr = lfLmINST->current<babc::Abc_Frame_t*>(); // the the network from shared_ptr

  int argc = 1; // command name
  if ( is_checking )
    argc += 1;

  argc += 1; // file name

  char** argv = ABC_ALLOC( char*, argc + 1 );

  int pos = 0;

  argv[pos++] = babc::Extra_UtilStrsav( "read_aiger" );

  if ( is_checking )
    argv[pos++] = babc::Extra_UtilStrsav( " -c " );

  argv[pos++] = babc::Extra_UtilStrsav( file.c_str() );

  babc::IoCommandReadAiger( ntk_ptr, argc, argv );
}

} // namespace abc

} // namespace logic

} // end namespace lf
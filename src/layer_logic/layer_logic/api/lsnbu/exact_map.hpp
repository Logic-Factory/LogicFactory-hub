#pragma once

#include "layer_logic/logic_manager.hpp"

#include "mockturtle/algorithms/mapper.hpp"
#include "mockturtle/algorithms/node_resynthesis/xmg_npn.hpp"
#include "mockturtle/algorithms/node_resynthesis/mig_npn.hpp"
#include "mockturtle/algorithms/node_resynthesis/xag_npn.hpp"
#include "mockturtle/networks/aig.hpp"
#include "mockturtle/networks/klut.hpp"
#include "mockturtle/networks/mig.hpp"
#include "mockturtle/networks/xag.hpp"
#include "mockturtle/networks/xmg.hpp"
#include "mockturtle/utils/tech_library.hpp"

namespace lf
{

namespace logic
{

namespace lsnbu
{

void exact_map()
{
  printf( "exact_map\n" );
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG )
  {
    std::cerr << "[ERROR] write_bench: wrong ntk type!" << std::endl;
    return;
  }

  lf::logic::lsils::aig_seq_network ntk = lfLmINST->current<lf::logic::lsils::aig_seq_network>();
  mockturtle::depth_view depth_ntk{ ntk };
  std::cout << "aig gates = " << ntk.num_gates() << " aig levels = " << depth_ntk.depth() << std::endl;
  mockturtle::xmg_npn_resynthesis resyn;
  mockturtle::exact_library<lf::logic::lsils::xmg_seq_network> lib( resyn );
  mockturtle::map_params ps;
  // if( is_set( "logic_sharing" ) )
  // {
  //     ps.enable_logic_sharing = true;
  // }
  mockturtle::map_stats st;
  lf::logic::lsils::xmg_seq_network xmg = mockturtle::map( ntk, lib, ps, &st );
  mockturtle::depth_view depth_xmg{ xmg };
  std::cout << "xmg gates = " << xmg.num_gates() << " xmg levels = " << depth_xmg.depth() << std::endl;
  lfLmINST->set_current( xmg );
}

} // end namespace lsnbu

} // end namespace logic

} // end namespace lf

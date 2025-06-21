#pragma once

#include "layer_logic/logic_manager.hpp"
#include "mockturtle/networks/xag.hpp"
#include "mockturtle/algorithms/balancing.hpp"
#include "mockturtle/algorithms/balancing/esop_balancing.hpp"

#include "./core/misc.hpp"

namespace lf
{
namespace logic
{
namespace lsnbu
{

inline void xagba()
{
  printf( "xagba\n" );
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG )
  {
    std::cerr << "[ERROR] xagba: wrong ntk type!" << std::endl;
    return;
  }

  lf::logic::lsils::xag_seq_network ntk = lfLmINST->current<lf::logic::lsils::xag_seq_network>();
  mockturtle::depth_view depth_ntk{ ntk };
  std::cout << "xag gates = " << ntk.num_gates() << " xag levels = " << depth_ntk.depth() << std::endl;
  lf::logic::lsils::xag_seq_network xag = ntk;

  xag = mockturtle::balancing( xag, { mockturtle::esop_rebalancing<lf::logic::lsils::xag_seq_network>{} } );
  xag = mockturtle::cleanup_dangling( xag );

  ntk = xag;
  mockturtle::depth_view depth_ntk2{ ntk };
  std::cout << "xag gates = " << ntk.num_gates() << " xag levels = " << depth_ntk2.depth() << std::endl;
  lfLmINST->set_current( ntk );
}

} // namespace lsnbu
} // namespace logic
} // namespace lf

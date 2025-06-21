#pragma once

#include "layer_logic/logic_manager.hpp"
#include "mockturtle/mockturtle.hpp"
#include "mockturtle/networks/xag.hpp"
#include "mockturtle/algorithms/xag_optimization.hpp"
#include "mockturtle/algorithms/equivalence_checking.hpp"
#include "mockturtle/properties/migcost.hpp"
#include "./core/misc.hpp"
#include "./core/xag_rewriting.hpp"

namespace lf
{
namespace logic
{
namespace lsnbu
{

struct xagrw_params
{
  int strategy = 0; // 0: aggressive, 1: selective, 2: dfs
  bool cec = false;
  bool verbose = false;
};

inline void xagrw()
{
  xagrw_params params = {};
  printf( "xagrw\n" );
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG )
  {
    std::cerr << "[ERROR] xagrw: wrong ntk type!" << std::endl;
    return;
  }

  lf::logic::lsils::xag_seq_network ntk = lfLmINST->current<lf::logic::lsils::xag_seq_network>();
  mockturtle::depth_view depth_ntk{ ntk };
  std::cout << "xag gates = " << ntk.num_gates() << " xag levels = " << depth_ntk.depth() << std::endl;
  lf::logic::lsils::xag_seq_network xag = ntk;
  lf::logic::lsils::xag_seq_network xag1 = xag, xag2;

  xag_depth_rewriting_params ps_xag;
  if ( params.strategy == 0 )
    ps_xag.strategy = xag_depth_rewriting_params::aggressive;
  else if ( params.strategy == 1 )
    ps_xag.strategy = xag_depth_rewriting_params::selective;
  else if ( params.strategy == 2 )
    ps_xag.strategy = xag_depth_rewriting_params::dfs;
  else
    assert( false && "strategy must be 0, 1, or 2" );

  mockturtle::depth_view<lf::logic::lsils::xag_seq_network> depth_xag1( xag1 );
  xag_depth_rewriting( depth_xag1, ps_xag );
  xag2 = mockturtle::cleanup_dangling( xag );

  if ( params.verbose )
  {
    std::cout << "[xagrw] ";
    also::print_stats( xag );
  }

  ntk = xag;
  mockturtle::depth_view depth_ntk2{ ntk };
  std::cout << "xag gates = " << ntk.num_gates() << " xag levels = " << depth_ntk2.depth() << std::endl;
  lfLmINST->set_current( ntk );
}

} // namespace lsnbu
} // namespace logic
} // namespace lf

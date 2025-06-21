#pragma once

#include "layer_logic/logic_manager.hpp"
#include "mockturtle/mockturtle.hpp"
#include "mockturtle/algorithms/xmg_resub.hpp"
#include "mockturtle/networks/xmg.hpp"

#include "./core/misc.hpp"

namespace lf
{
namespace logic
{
namespace lsnbu
{

struct xmgrs_params
{
  bool verbose = false;
  bool cec = false;
};

inline void xmgrs()
{
  printf( "xmgrs\n" );
  xmgrs_params params{};
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG )
  {
    std::cerr << "[ERROR] xmgrs: wrong ntk type!" << std::endl;
    return;
  }

  lf::logic::lsils::xmg_seq_network ntk = lfLmINST->current<lf::logic::lsils::xmg_seq_network>();
  mockturtle::depth_view depth_ntk{ ntk };
  std::cout << "xmg gates = " << ntk.num_gates() << " xmg levels = " << depth_ntk.depth() << std::endl;
  lf::logic::lsils::xmg_seq_network xmg = ntk;
  lf::logic::lsils::xmg_seq_network xmg1 = xmg, xmg2 = xmg;

  using view_t = mockturtle::depth_view<mockturtle::fanout_view<lf::logic::lsils::xmg_seq_network>>;
  mockturtle::fanout_view<lf::logic::lsils::xmg_seq_network> fanout_view{ xmg1 };
  view_t resub_view{ fanout_view };
  mockturtle::xmg_resubstitution( resub_view );
  xmg2 = mockturtle::cleanup_dangling( xmg1 );

  if ( params.verbose )
  {
    std::cout << "[xmgrs] ";
    auto xmg_copy = mockturtle::cleanup_dangling( xmg2 );
    also::print_stats( xmg_copy );
  }

  ntk = xmg2;
  mockturtle::depth_view depth_ntk2{ ntk };
  std::cout << "xmg gates = " << ntk.num_gates() << " xmg levels = " << depth_ntk2.depth() << std::endl;
  lfLmINST->set_current( ntk );
}

} // namespace lsnbu
} // namespace logic
} // namespace lf

#pragma once

#include "layer_logic/logic_manager.hpp"
#include "mockturtle/networks/mig.hpp"
#include "mockturtle/views/depth_view.hpp"
#include "mockturtle/algorithms/mig_algebraic_rewriting.hpp"
#include "mockturtle/algorithms/mig_resub.hpp"
#include "./core/misc.hpp"

namespace lf
{
namespace logic
{
namespace lsnbu
{

/**
 * @brief MIG algebraic rewrite parameter configuration
 * @param strategy 0:dfs, 1:aggressive, 2:selective
 * @param area_aware Whether to restrict the growth of area
 */
struct mighty_params
{
  int strategy = 0;
  bool area_aware = false;
};

void mighty_rewrite()
{
  mighty_params params;
  printf( "mighty\n" );
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_MIG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_MIG )
  {
    std::cerr << "[ERROR] write_bench: wrong ntk type!" << std::endl;
    return;
  }

  auto ntk = lfLmINST->current<lf::logic::lsils::mig_seq_network>();
  mockturtle::depth_view depth_ntk{ ntk };
  std::cout << "mig gates = " << ntk.num_gates() << " mig levels = " << depth_ntk.depth() << std::endl;
  lf::logic::lsils::mig_seq_network mig = ntk;

  mockturtle::mig_algebraic_depth_rewriting_params ps_mig;
  ps_mig.allow_area_increase = !params.area_aware;
  switch ( params.strategy )
  {
  case 0:
    ps_mig.strategy = mockturtle::mig_algebraic_depth_rewriting_params::dfs;
    break;
  case 1:
    ps_mig.strategy = mockturtle::mig_algebraic_depth_rewriting_params::aggressive;
    break;
  case 2:
    ps_mig.strategy = mockturtle::mig_algebraic_depth_rewriting_params::selective;
    break;
  default:
    std::cerr << "Error: strategy must be in [0,2]" << std::endl;
    return;
  }

  mockturtle::depth_view depth_mig( mig );
  mockturtle::mig_algebraic_depth_rewriting( depth_mig, ps_mig );
  mig = mockturtle::cleanup_dangling( mig );

  using view_t = mockturtle::depth_view<mockturtle::fanout_view<lf::logic::lsils::mig_seq_network>>;
  mockturtle::fanout_view<lf::logic::lsils::mig_seq_network> fanout_view{ mig };
  view_t resub_view{ fanout_view };
  mockturtle::mig_resubstitution( resub_view );
  mig = mockturtle::cleanup_dangling( mig );

  ntk = mig;
  mockturtle::depth_view depth_ntk2{ ntk };
  std::cout << "mig gates = " << ntk.num_gates() << " mig levels = " << depth_ntk2.depth() << std::endl;
  lfLmINST->set_current( ntk );
}

} // namespace lsnbu
} // namespace logic
} // namespace lf
#pragma once

#include "layer_logic/logic_manager.hpp"

#include "mockturtle/networks/xmg.hpp"
#include "mockturtle/views/depth_view.hpp"
#include "mockturtle/algorithms/equivalence_checking.hpp"
#include "mockturtle/algorithms/mig_algebraic_rewriting.hpp"

#include "./core/xmg_rewriting.hpp"
#include "./core/xmg_expand.hpp"
#include "./core/misc.hpp"

namespace lf
{

namespace logic
{

namespace lsnbu
{

/**
 * @brief XMG algebraic rewriting function
 * @param params parameter configuration
 * int strategy             qca=0, aggressive=1, selective=2, dfs=3
 * bool area_aware          Whether to restrict the growth of area
 * bool xor3_flattan        Whether to expand XOR3 becomes XOR2
 * bool only_maj            Whether to handle only MAJ nodes
 * bool cec                 Whether to perform the equivalence check
 * bool expand              Whether to expand XOR
 * bool hunt_constant_xor   Whether to search for the constant XOR node
 * @note This function performs algebraic rewriting on the current XMG network
 */

struct xmgrw_params
{
  int strategy = 0;
  bool area_aware = false;
  bool xor3_flattan = false;
  bool only_maj = false;
  bool cec = false;
  bool expand = false;
  bool hunt_constant_xor = false;
};

void xmgrw()
{
  printf( "xmgrw\n" );
  xmgrw_params params;
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG )
  {
    std::cerr << "[ERROR] write_bench: wrong ntk type!" << std::endl;
    return;
  }

  lf::logic::lsils::xmg_seq_network ntk = lfLmINST->current<lf::logic::lsils::xmg_seq_network>();
  mockturtle::depth_view depth_ntk{ ntk };
  std::cout << "xmg gates = " << ntk.num_gates() << " xmg levels = " << depth_ntk.depth() << std::endl;
  lf::logic::lsils::xmg_seq_network xmg = ntk;

  if ( params.strategy < 0 || params.strategy > 3 )
  {
    std::cerr << "Error: strategy must be in [0,3]" << std::endl;
    return;
  }

  if ( params.only_maj )
  {
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
      assert( false );
    }

    mockturtle::depth_view depth_xmg{ xmg };
    mockturtle::mig_algebraic_depth_rewriting( depth_xmg, ps_mig );
    xmg = mockturtle::cleanup_dangling( xmg );
  }
  // else if ( params.hunt_constant_xor )
  // {
  //     auto xors = also::xmg_extract( xmg );
  //     xmg_expand_rewriting_params ps_expand;
  //     ps_expand.strategy = xmg_expand_rewriting_params::constants;
  //     ps_expand.xor_index = xors;

  //     mockturtle::depth_view depth_xmg{ xmg };
  //     xmg_expand_rewriting( depth_xmg, ps_expand );
  //     xmg = mockturtle::cleanup_dangling( xmg );
  // }
  else if ( params.expand )
  {
    xmg_expand_rewriting_params ps_expand;
    ps_expand.strategy = xmg_expand_rewriting_params::expand;

    mockturtle::depth_view depth_xmg{ xmg };
    xmg_expand_rewriting( depth_xmg, ps_expand );
    xmg = mockturtle::cleanup_dangling( xmg );
  }
  else
  {
    xmg_depth_rewriting_params ps_xmg;
    mockturtle::mig_algebraic_depth_rewriting_params ps_mig;
    ps_xmg.allow_area_increase = !params.area_aware;
    ps_xmg.apply_xor3_to_xor2 = params.xor3_flattan;
    ps_mig.allow_area_increase = !params.area_aware;

    switch ( params.strategy )
    {
    case 0:
      ps_xmg.strategy = xmg_depth_rewriting_params::qca;
      ps_mig.strategy = mockturtle::mig_algebraic_depth_rewriting_params::dfs;
      break;
    case 1:
      ps_xmg.strategy = xmg_depth_rewriting_params::aggressive;
      ps_mig.strategy = mockturtle::mig_algebraic_depth_rewriting_params::aggressive;
      break;
    case 2:
      ps_xmg.strategy = xmg_depth_rewriting_params::selective;
      ps_mig.strategy = mockturtle::mig_algebraic_depth_rewriting_params::selective;
      break;
    case 3:
      ps_xmg.strategy = xmg_depth_rewriting_params::dfs;
      ps_mig.strategy = mockturtle::mig_algebraic_depth_rewriting_params::dfs;
      break;
    default:
      assert( false );
    }

    mockturtle::depth_view depth_xmg1{ xmg };
    mockturtle::mig_algebraic_depth_rewriting( depth_xmg1, ps_mig );
    xmg = mockturtle::cleanup_dangling( xmg );

    mockturtle::depth_view depth_xmg2{ xmg };
    xmg_depth_rewriting( depth_xmg2, ps_xmg );
    xmg = mockturtle::cleanup_dangling( xmg );
  }

  ntk = xmg;
  mockturtle::depth_view depth_ntk2{ ntk };
  std::cout << "xmg gates = " << ntk.num_gates() << " xmg levels = " << depth_ntk2.depth() << std::endl;
  lfLmINST->set_current( ntk );
}

} // end namespace lsnbu

} // end namespace logic

} // end namespace lf

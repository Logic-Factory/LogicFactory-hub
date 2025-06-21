#pragma once

#include "layer_logic/logic_manager.hpp"
#include "./core/xag_mprm_multi_mult_opt_imp.hpp"
using namespace mockturtle;
namespace lf
{

namespace logic
{

namespace lsnbu
{

/**
 * @brief Multilevel RM logic optimization
 * @example
 *  xag_mprm_multi_mult_opt [options]
 *  options: [KCM] [mzlcpvw]
 * @note
 */

void xag_mprm_multi_mult_opt()
{
  printf( "xag_mprm_multi_mult_opt\n" );
  rm_rewriting_params2 ps_ntk;
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG )
  {
    std::cerr << "[ERROR] write_bench: wrong ntk type!" << std::endl;
    return;
  }
  lf::logic::lsils::xag_seq_network ntk = lfLmINST->current<lf::logic::lsils::xag_seq_network>();
  mockturtle::depth_view depth_ntk{ ntk };
  std::cout << "xag gates = " << ntk.num_gates() << " xag levels = " << depth_ntk.depth() << std::endl;
  ps_ntk.multiplicative_complexity = true; // Enable multiplicative complexity optimization
  cut_rewriting_params ps;
  ps.cut_enumeration_ps.cut_size = 6;
  ps.cut_enumeration_ps.cut_limit = 12;
  ps.min_cand_cut_size = 2;
  ps.allow_zero_gain = true;
  ps.progress = true;
  rm_mixed_polarity2( ntk, ps_ntk, ps );
  ntk = mockturtle::cleanup_dangling( ntk );
  mockturtle::depth_view depth_ntk2{ ntk };
  std::cout << "xag gates = " << ntk.num_gates() << " xag levels = " << depth_ntk2.depth() << std::endl;
  lfLmINST->set_current( ntk );
}

} // namespace lsnbu

} // end namespace logic

} // end namespace lf
#pragma once

#include "layer_logic/logic_manager.hpp"
#include "./core/xag_mprm2_area_opt_imp.hpp"

namespace lf
{

namespace logic
{

namespace lsnbu
{

/**
 * @brief xag_mprm2_area_opt
 * @example
 *  xag_mprm2_area_opt [options]
 *  options: [KCM] [mzlcpvw]
 * @note
 */

void xag_mprm2_area_opt()
{
  printf( "xag_mprm2_area_opt\n" );
  rm_rewriting_params ps_ntk;
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
  mockturtle::depth_view depth_xag1( ntk );
  mockturtle::rm_mixed_polarity( depth_xag1, ps_ntk );
  std::cout << "xag gates = " << depth_xag1.num_gates() << " xag levels = " << depth_xag1.depth() << std::endl;
  lfLmINST->set_current( ntk );
}

} // namespace lsnbu

} // end namespace logic

} // end namespace lf
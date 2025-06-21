#pragma once

#include "layer_logic/logic_manager.hpp"

#include "mockturtle/mockturtle.hpp"
#include "mockturtle/algorithms/resubstitution.hpp"
#include "mockturtle/networks/xag.hpp"

#include "./core/misc.hpp"

namespace lf
{
namespace logic
{
namespace lsnbu
{

struct xagrs_params
{
  bool use_bdiff = false;   // 是否使用 Boolean difference resub
  bool verbose = false;     // 是否显示详细信息
  unsigned max_inserts = 3; // 最大插入数，仅对 bdiff 有效
};
void xagrs()
{
  xagrs_params params;
  printf( "xagrs\n" );
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG )
  {
    std::cerr << "[ERROR] xagrs: wrong ntk type!" << std::endl;
    return;
  }
  lf::logic::lsils::xag_seq_network ntk = lfLmINST->current<lf::logic::lsils::xag_seq_network>();
  mockturtle::depth_view depth_ntk{ ntk };
  std::cout << "xag gates = " << ntk.num_gates() << " xag levels = " << depth_ntk.depth() << std::endl;
  lf::logic::lsils::xag_seq_network xag = ntk;
  mockturtle::resubstitution_params ps;
  mockturtle::resubstitution_stats st;
  ps.verbose = params.verbose;

  if ( params.use_bdiff )
  {
    ps.use_dont_cares = true;
    ps.max_inserts = params.max_inserts;
    if ( params.verbose )
      ps.verbose = true;
    // mockturtle::resubstitution_xag_bdiff(xag, ps, &st);
  }
  else
  {
    mockturtle::default_resubstitution( xag, ps, &st );
  }
  xag = mockturtle::cleanup_dangling( xag );
  ntk = xag;
  mockturtle::depth_view depth_ntk2{ ntk };
  std::cout << "xag gates = " << ntk.num_gates() << " xag levels = " << depth_ntk2.depth() << std::endl;
  lfLmINST->set_current( ntk );
}

} // end namespace lsnbu

} // end namespace logic

} // end namespace lf

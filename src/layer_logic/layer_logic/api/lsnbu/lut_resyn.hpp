#pragma once
#include "layer_logic/logic_manager.hpp"

#include "mockturtle/mockturtle.hpp"
#include "mockturtle/algorithms/node_resynthesis/xmg_npn.hpp"
#include "mockturtle/algorithms/node_resynthesis/xmg3_npn.hpp"
#include "mockturtle/algorithms/node_resynthesis/shannon.hpp"
#include "mockturtle/algorithms/node_resynthesis/dsd.hpp"
#include "./core/misc.hpp"

namespace lf
{
namespace logic
{
namespace lsnbu
{
/**
 * @brief parameter configuration
 * @param cut_size set the cut size from 2 to 8, default = 4
 * @param target_network network type
 * @param new_entry adds new store entry
 * @param enable_direct_mapping enable aig to xmg by direct mapping for comparison
 */
struct lut_resyn_params
{
  enum target_type_t
  {
    MIG = 0,
    XMG,
    XMG3,
    M5IG,
    IMG,
    XAG
  } target_type = MIG;
  int cut_size = 4;
  bool new_entry = false;
  bool enable_direct_mapping = false;
};

// void lut_resyn()
// {
//     lut_resyn_params params {0, 4, true, false};
//     auto klut = lfLmINST->current<lf::logic::lsils::klut_comb_network>();
//     mockturtle::mig_npn_resynthesis resyn;
//     const lf::logic::lsils::mig_comb_network mig = mockturtle::node_resynthesis<lf::logic::lsils::mig_comb_network>( klut, resyn );
//     if( params.new_entry )
//     {
//         lfLmINST->set_current( mig );
//     }

// }
// void lut_resyn()
// {
//   lut_resyn_params params{ 0, 4, true, false };
//   lf::logic::lsils::klut_seq_network klut = lfLmINST->current<lf::logic::lsils::klut_seq_network>();
//   mockturtle::mig_npn_resynthesis resyn;
//   const lf::logic::lsils::mig_seq_network mig = mockturtle::node_resynthesis<lf::logic::lsils::mig_seq_network>( klut, resyn );
//   mockturtle::depth_view depth_ntk{ mig };
//   std::cout << "mig gates = " << mig.num_gates() << " mig levels = " << depth_ntk.depth() << std::endl;
//   if ( params.new_entry )
//   {
//     lfLmINST->set_current( mig );
//   }
// }
void lut_resyn()
{
  printf( "lut_resyn\n" );
  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG )
  {
    std::cerr << "[ERROR] lut_resyn: wrong ntk type!" << std::endl;
    return;
  }

  lf::logic::lsils::aig_seq_network aig = lfLmINST->current<lf::logic::lsils::aig_seq_network>();
  mockturtle::mapping_view<lf::logic::lsils::aig_seq_network, true> mapped_aig{ aig };
  mockturtle::lut_mapping_params ps;
  ps.cut_enumeration_ps.cut_size = 4;
  mockturtle::lut_mapping<mockturtle::mapping_view<lf::logic::lsils::aig_seq_network, true>, true, mockturtle::cut_enumeration_mf_cut>( mapped_aig, ps );
  const auto lut_ntk = *mockturtle::collapse_mapped_network<lf::logic::lsils::klut_seq_network>( mapped_aig );
  mockturtle::depth_view depth_lut{ lut_ntk };
  std::cout << "lut gates = " << lut_ntk.num_gates() << " lut levels = " << depth_lut.depth() << std::endl;

  lut_resyn_params params{ 0, 4, true, false };
  //   lf::logic::lsils::klut_seq_network klut = lfLmINST->current<lf::logic::lsils::klut_seq_network>();
  lf::logic::lsils::klut_seq_network klut = lut_ntk;
  mockturtle::mig_npn_resynthesis resyn;
  const lf::logic::lsils::mig_seq_network mig = mockturtle::node_resynthesis<lf::logic::lsils::mig_seq_network>( klut, resyn );
  mockturtle::depth_view depth_ntk{ mig };
  std::cout << "mig gates = " << mig.num_gates() << " mig levels = " << depth_ntk.depth() << std::endl;
  if ( params.new_entry )
  {
    lfLmINST->set_current( mig );
  }
}

} // namespace lsnbu
} // namespace logic
} // namespace lf

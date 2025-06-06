#pragma once

#include "layer_logic/logic_manager.hpp"

namespace lf
{

namespace logic
{

namespace lsils
{

/**
 * @brief Logic optimization
 * @example
 *  resubing [options]
 *  options: [PDIRFW] [ldpv]
 * @note
 */
template<typename Ntk = aig_seq_network>
void resubing( int NInputMax = -1, int Max_divisors = -1, int Max_inserts = -1, int fanout_limib_Root = -1, int Fanout_limit_divisor = -1, int Window_size = -1,
               bool is_preserve_depth = false, bool is_dont_cares = false, bool is_progress = false, bool is_verbose = false )
{
  // update the params
  mockturtle::resubstitution_params ps;
  if ( NInputMax > 0 )
    ps.max_pis = NInputMax;
  if ( Max_divisors > 0 )
    ps.max_divisors = Max_divisors;
  if ( Max_inserts > 0 )
    ps.max_inserts = Max_inserts;
  if ( fanout_limib_Root > 0 )
    ps.skip_fanout_limit_for_roots = fanout_limib_Root;
  if ( Fanout_limit_divisor > 0 )
    ps.skip_fanout_limit_for_divisors = Fanout_limit_divisor;
  if ( Window_size > 0 )
    ps.window_size = Window_size;
  if ( is_preserve_depth )
    ps.preserve_depth = true;
  if ( is_dont_cares )
    ps.use_dont_cares = true;
  if ( is_progress )
    ps.progress = true;
  if ( is_verbose )
    ps.verbose = true;

  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_MIG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_MIG )
  {
    std::cerr << "[ERROR] write_bench: wrong ntk type!" << std::endl;
    return;
  }

  switch ( ntktype )
  {
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG:
  {
    lf::logic::lsils::aig_seq_network ntk = lfLmINST->current<lf::logic::lsils::aig_seq_network>();
    mockturtle::default_resubstitution( ntk, ps );
    lfLmINST->set_current<lf::logic::lsils::aig_seq_network>( ntk );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XAG:
  {
    lf::logic::lsils::xag_seq_network ntk = lfLmINST->current<lf::logic::lsils::xag_seq_network>();
    mockturtle::default_resubstitution( ntk, ps );
    lfLmINST->set_current<lf::logic::lsils::xag_seq_network>( ntk );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG:
  {
    lf::logic::lsils::xmg_seq_network ntk = lfLmINST->current<lf::logic::lsils::xmg_seq_network>();
    mockturtle::default_resubstitution( ntk, ps );
    lfLmINST->set_current<lf::logic::lsils::xmg_seq_network>( ntk );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_MIG:
  {
    lf::logic::lsils::mig_seq_network ntk = lfLmINST->current<lf::logic::lsils::mig_seq_network>();
    mockturtle::default_resubstitution( ntk, ps );
    lfLmINST->set_current<lf::logic::lsils::mig_seq_network>( ntk );
    break;
  }
  default:
  {
    std::cerr << "unsupport network type!\n";
    assert( false );
    break;
  }
  }
}

template<typename Ntk = aig_seq_network>
void resub( int NInputMax = -1, int Max_divisors = -1, int Max_inserts = -1, int fanout_limit_Root = -1, int Fanout_limit_divisor = -1, int Window_size = -1,
            bool is_preserve_depth = false, bool is_dont_cares = false, bool is_progress = false, bool is_verbose = false )
{
  printf( "resub\n" );
  mockturtle::resubstitution_params ps;
  if ( NInputMax > 0 )
    ps.max_pis = NInputMax;
  if ( Max_divisors > 0 )
    ps.max_divisors = Max_divisors;
  if ( Max_inserts > 0 )
    ps.max_inserts = Max_inserts;
  if ( fanout_limit_Root > 0 )
    ps.skip_fanout_limit_for_roots = fanout_limit_Root;
  if ( Fanout_limit_divisor > 0 )
    ps.skip_fanout_limit_for_divisors = Fanout_limit_divisor;
  if ( Window_size > 0 )
    ps.window_size = Window_size;
  if ( is_preserve_depth )
    ps.preserve_depth = true;
  if ( is_dont_cares )
    ps.use_dont_cares = true;
  if ( is_progress )
    ps.progress = true;
  if ( is_verbose )
    ps.verbose = true;

  auto ntktype = lfLntINST->get_ntktype_curr();
  assert( ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG ||
          ntktype == lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG );
  if ( ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG &&
       ntktype != lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG )
  {
    std::cerr << "[ERROR] write_bench: wrong ntk type!" << std::endl;
    return;
  }

  switch ( ntktype )
  {
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_AIG:
  {
    lf::logic::lsils::aig_seq_network ntk = lfLmINST->current<lf::logic::lsils::aig_seq_network>();
    mockturtle::aig_resubstitution( ntk, ps );
    lfLmINST->set_current( ntk );
    lfLmINST->set_current<lf::logic::lsils::aig_seq_network>( ntk );
    break;
  }
  case lf::misc::E_LF_NTK_TYPE::E_LF_NTK_TYPE_LSILS_STRASH_XMG:
  {
    lf::logic::lsils::xmg_seq_network ntk = lfLmINST->current<lf::logic::lsils::xmg_seq_network>();
    mockturtle::xmg_resubstitution( ntk, ps );
    lfLmINST->set_current( ntk );
    lfLmINST->set_current<lf::logic::lsils::xmg_seq_network>( ntk );
    break;
  }
  default:
  {
    std::cerr << "unsupport network type!\n";
    assert( false );
    break;
  }
  }
}

} // end namespace lsils

} // end namespace logic

} // end namespace lf

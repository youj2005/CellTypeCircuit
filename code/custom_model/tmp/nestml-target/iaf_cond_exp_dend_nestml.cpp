// #define DEBUG 1
/*
 *  iaf_cond_exp_dend_nestml.cpp
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Generated from NESTML at time: 2025-03-14 15:25:03.866005
**/

// C++ includes:
#include <limits>

// Includes from libnestutil:
#include "numerics.h"

// Includes from nestkernel:
#include "exceptions.h"
#include "kernel_manager.h"
#include "universal_data_logger_impl.h"

// Includes from sli:
#include "dict.h"
#include "dictutils.h"
#include "doubledatum.h"
#include "integerdatum.h"
#include "lockptrdatum.h"

#include "iaf_cond_exp_dend_nestml.h"

// ---------------------------------------------------------------------------
//   Recordables map
// ---------------------------------------------------------------------------
nest::RecordablesMap<iaf_cond_exp_dend_nestml> iaf_cond_exp_dend_nestml::recordablesMap_;
namespace nest
{

  // Override the create() method with one call to RecordablesMap::insert_()
  // for each quantity to be recorded.
template <> void RecordablesMap<iaf_cond_exp_dend_nestml>::create()
  {
    // add state variables to recordables map
   insert_(iaf_cond_exp_dend_nestml_names::_V_m, &iaf_cond_exp_dend_nestml::get_V_m);
   insert_(iaf_cond_exp_dend_nestml_names::_g_exc2__X__exc_spikes, &iaf_cond_exp_dend_nestml::get_g_exc2__X__exc_spikes);
   insert_(iaf_cond_exp_dend_nestml_names::_g_inh__X__inh_spikes, &iaf_cond_exp_dend_nestml::get_g_inh__X__inh_spikes);
   insert_(iaf_cond_exp_dend_nestml_names::_g_exc__X__exc_spikes, &iaf_cond_exp_dend_nestml::get_g_exc__X__exc_spikes);
   insert_(iaf_cond_exp_dend_nestml_names::_g_inh_dend2__X__inh_dend_spikes, &iaf_cond_exp_dend_nestml::get_g_inh_dend2__X__inh_dend_spikes);
   insert_(iaf_cond_exp_dend_nestml_names::_g_inh_dend__X__inh_dend_spikes, &iaf_cond_exp_dend_nestml::get_g_inh_dend__X__inh_dend_spikes);

    // Add vector variables  
  }
}

// ---------------------------------------------------------------------------
//   Default constructors defining default parameters and state
//   Note: the implementation is empty. The initialization is of variables
//   is a part of iaf_cond_exp_dend_nestml's constructor.
// ---------------------------------------------------------------------------

iaf_cond_exp_dend_nestml::Parameters_::Parameters_()
{
}

iaf_cond_exp_dend_nestml::State_::State_()
{
}

// ---------------------------------------------------------------------------
//   Parameter and state extractions and manipulation functions
// ---------------------------------------------------------------------------

iaf_cond_exp_dend_nestml::Buffers_::Buffers_(iaf_cond_exp_dend_nestml &n):
  logger_(n)
  , spike_inputs_( std::vector< nest::RingBuffer >( SUP_SPIKE_RECEPTOR - 1 ) )
  , __s( 0 ), __c( 0 ), __e( 0 )
{
  // Initialization of the remaining members is deferred to init_buffers_().
}

iaf_cond_exp_dend_nestml::Buffers_::Buffers_(const Buffers_ &, iaf_cond_exp_dend_nestml &n):
  logger_(n)
  , spike_inputs_( std::vector< nest::RingBuffer >( SUP_SPIKE_RECEPTOR - 1 ) )
  , __s( 0 ), __c( 0 ), __e( 0 )
{
  // Initialization of the remaining members is deferred to init_buffers_().
}

// ---------------------------------------------------------------------------
//   Default constructor for node
// ---------------------------------------------------------------------------

iaf_cond_exp_dend_nestml::iaf_cond_exp_dend_nestml():ArchivingNode(), P_(), S_(), B_(*this)
{
  const double __resolution = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the resolution() function
  calibrate();

  // use a default "good enough" value for the absolute error. It can be adjusted via `node.set()`
  P_.__gsl_error_tol = 1e-3;
  // initial values for parameters
    
    P_.V_th = (-(55)); // as mV
    
    P_.V_reset = (-(60)); // as mV
    
    P_.t_ref = 2; // as ms
    
    P_.g_L = 16.6667; // as nS
    
    P_.C_m = 250; // as pF
    
    P_.E_exc = 0; // as mV
    
    P_.E_inh = (-(85)); // as mV
    
    P_.E_L = (-(70)); // as mV
    
    P_.tau_syn_exc = 0.2; // as ms
    
    P_.tau_syn_inh = 2; // as ms
    
    P_.alpha_ei_inv = (-(1.0)); // as nS
    
    P_.I_e = 0; // as pA
  // initial values for state variables
    
    S_.ode_state[State_::r] = 0; // as integer
    
    S_.ode_state[State_::V_m] = P_.E_L; // as mV
    
    S_.ode_state[State_::g_exc2__X__exc_spikes] = 0; // as real
    
    S_.ode_state[State_::g_inh__X__inh_spikes] = 0; // as real
    
    S_.ode_state[State_::g_exc__X__exc_spikes] = 0; // as real
    
    S_.ode_state[State_::g_inh_dend2__X__inh_dend_spikes] = 0; // as real
    
    S_.ode_state[State_::g_inh_dend__X__inh_dend_spikes] = 0; // as real
  recordablesMap_.create();
}

// ---------------------------------------------------------------------------
//   Copy constructor for node
// ---------------------------------------------------------------------------

iaf_cond_exp_dend_nestml::iaf_cond_exp_dend_nestml(const iaf_cond_exp_dend_nestml& __n):
  ArchivingNode(), P_(__n.P_), S_(__n.S_), B_(__n.B_, *this) {

  // copy parameter struct P_
  P_.V_th = __n.P_.V_th;
  P_.V_reset = __n.P_.V_reset;
  P_.t_ref = __n.P_.t_ref;
  P_.g_L = __n.P_.g_L;
  P_.C_m = __n.P_.C_m;
  P_.E_exc = __n.P_.E_exc;
  P_.E_inh = __n.P_.E_inh;
  P_.E_L = __n.P_.E_L;
  P_.tau_syn_exc = __n.P_.tau_syn_exc;
  P_.tau_syn_inh = __n.P_.tau_syn_inh;
  P_.alpha_ei_inv = __n.P_.alpha_ei_inv;
  P_.I_e = __n.P_.I_e;

  // copy state struct S_
  S_.ode_state[State_::r] = __n.S_.ode_state[State_::r];
  S_.ode_state[State_::V_m] = __n.S_.ode_state[State_::V_m];
  S_.ode_state[State_::g_exc2__X__exc_spikes] = __n.S_.ode_state[State_::g_exc2__X__exc_spikes];
  S_.ode_state[State_::g_inh__X__inh_spikes] = __n.S_.ode_state[State_::g_inh__X__inh_spikes];
  S_.ode_state[State_::g_exc__X__exc_spikes] = __n.S_.ode_state[State_::g_exc__X__exc_spikes];
  S_.ode_state[State_::g_inh_dend2__X__inh_dend_spikes] = __n.S_.ode_state[State_::g_inh_dend2__X__inh_dend_spikes];
  S_.ode_state[State_::g_inh_dend__X__inh_dend_spikes] = __n.S_.ode_state[State_::g_inh_dend__X__inh_dend_spikes];


  // copy internals V_
  V_.RefractoryCounts = __n.V_.RefractoryCounts;
  V_.__h = __n.V_.__h;
  V_.__P__g_exc2__X__exc_spikes__g_exc2__X__exc_spikes = __n.V_.__P__g_exc2__X__exc_spikes__g_exc2__X__exc_spikes;
  V_.__P__g_inh__X__inh_spikes__g_inh__X__inh_spikes = __n.V_.__P__g_inh__X__inh_spikes__g_inh__X__inh_spikes;
  V_.__P__g_exc__X__exc_spikes__g_exc__X__exc_spikes = __n.V_.__P__g_exc__X__exc_spikes__g_exc__X__exc_spikes;
  V_.__P__g_inh_dend2__X__inh_dend_spikes__g_inh_dend2__X__inh_dend_spikes = __n.V_.__P__g_inh_dend2__X__inh_dend_spikes__g_inh_dend2__X__inh_dend_spikes;
  V_.__P__g_inh_dend__X__inh_dend_spikes__g_inh_dend__X__inh_dend_spikes = __n.V_.__P__g_inh_dend__X__inh_dend_spikes__g_inh_dend__X__inh_dend_spikes;
}

// ---------------------------------------------------------------------------
//   Destructor for node
// ---------------------------------------------------------------------------

iaf_cond_exp_dend_nestml::~iaf_cond_exp_dend_nestml()
{
  // GSL structs may not have been allocated, so we need to protect destruction

  if (B_.__s)
  {
    gsl_odeiv_step_free( B_.__s );
  }

  if (B_.__c)
  {
    gsl_odeiv_control_free( B_.__c );
  }

  if (B_.__e)
  {
    gsl_odeiv_evolve_free( B_.__e );
  }
}

// ---------------------------------------------------------------------------
//   Node initialization functions
// ---------------------------------------------------------------------------

void iaf_cond_exp_dend_nestml::init_buffers_()
{
  get_exc_spikes().clear(); //includes resize
  get_inh_spikes().clear(); //includes resize
  get_inh_dend_spikes().clear(); //includes resize
  get_I_stim().clear(); //includes resize
  B_.logger_.reset(); // includes resize

  if ( B_.__s == 0 )
  {
    B_.__s = gsl_odeiv_step_alloc( gsl_odeiv_step_rkf45, 7 );
  }
  else
  {
    gsl_odeiv_step_reset( B_.__s );
  }

  if ( B_.__c == 0 )
  {
    B_.__c = gsl_odeiv_control_y_new( P_.__gsl_error_tol, 0.0 );
  }
  else
  {
    gsl_odeiv_control_init( B_.__c, P_.__gsl_error_tol, 0.0, 1.0, 0.0 );
  }

  if ( B_.__e == 0 )
  {
    B_.__e = gsl_odeiv_evolve_alloc( 7 );
  }
  else
  {
    gsl_odeiv_evolve_reset( B_.__e );
  }

  B_.__sys.function = iaf_cond_exp_dend_nestml_dynamics;
  B_.__sys.jacobian = NULL;
  B_.__sys.dimension = 7;
  B_.__sys.params = reinterpret_cast< void* >( this );
  B_.__step = nest::Time::get_resolution().get_ms();
  B_.__integration_step = nest::Time::get_resolution().get_ms();
}

void iaf_cond_exp_dend_nestml::recompute_internal_variables(bool exclude_timestep) {
  const double __resolution = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the resolution() function

  if (exclude_timestep) {    
      
      V_.RefractoryCounts = nest::Time(nest::Time::ms((double) (P_.t_ref))).get_steps(); // as integer
      
      V_.__P__g_exc2__X__exc_spikes__g_exc2__X__exc_spikes = std::exp((-(V_.__h)) / P_.tau_syn_exc); // as real
      
      V_.__P__g_inh__X__inh_spikes__g_inh__X__inh_spikes = std::exp((-(V_.__h)) / P_.tau_syn_inh); // as real
      
      V_.__P__g_exc__X__exc_spikes__g_exc__X__exc_spikes = std::exp((-(V_.__h)) / P_.tau_syn_exc); // as real
      
      V_.__P__g_inh_dend2__X__inh_dend_spikes__g_inh_dend2__X__inh_dend_spikes = std::exp((-(V_.__h)) / P_.tau_syn_inh); // as real
      
      V_.__P__g_inh_dend__X__inh_dend_spikes__g_inh_dend__X__inh_dend_spikes = std::exp((-(V_.__h)) / P_.tau_syn_inh); // as real
  }
  else {
    // internals V_
      
      V_.RefractoryCounts = nest::Time(nest::Time::ms((double) (P_.t_ref))).get_steps(); // as integer
      
      V_.__h = __resolution; // as ms
      
      V_.__P__g_exc2__X__exc_spikes__g_exc2__X__exc_spikes = std::exp((-(V_.__h)) / P_.tau_syn_exc); // as real
      
      V_.__P__g_inh__X__inh_spikes__g_inh__X__inh_spikes = std::exp((-(V_.__h)) / P_.tau_syn_inh); // as real
      
      V_.__P__g_exc__X__exc_spikes__g_exc__X__exc_spikes = std::exp((-(V_.__h)) / P_.tau_syn_exc); // as real
      
      V_.__P__g_inh_dend2__X__inh_dend_spikes__g_inh_dend2__X__inh_dend_spikes = std::exp((-(V_.__h)) / P_.tau_syn_inh); // as real
      
      V_.__P__g_inh_dend__X__inh_dend_spikes__g_inh_dend__X__inh_dend_spikes = std::exp((-(V_.__h)) / P_.tau_syn_inh); // as real
  }
}
void iaf_cond_exp_dend_nestml::calibrate() {
  B_.logger_.init();

  recompute_internal_variables();

  // buffers B_
}

// ---------------------------------------------------------------------------
//   Update and spike handling functions
// ---------------------------------------------------------------------------

extern "C" inline int iaf_cond_exp_dend_nestml_dynamics(double, const double ode_state[], double f[], void* pnode)
{
  typedef iaf_cond_exp_dend_nestml::State_ State_;
  // get access to node so we can almost work as in a member function
  assert( pnode );
  const iaf_cond_exp_dend_nestml& node = *( reinterpret_cast< iaf_cond_exp_dend_nestml* >( pnode ) );

  // ode_state[] here is---and must be---the state vector supplied by the integrator,
  // not the state vector in the node, node.S_.ode_state[].
  f[State_::V_m] = node.get_E_L() * node.get_g_L() / node.get_C_m() - ode_state[State_::V_m] * node.get_g_L() / node.get_C_m() + (node.get_E_exc() * ode_state[State_::g_exc__X__exc_spikes] - node.get_E_exc() * ode_state[State_::g_exc2__X__exc_spikes] * ode_state[State_::g_inh_dend2__X__inh_dend_spikes] / node.get_alpha_ei_inv() + node.get_E_inh() * ode_state[State_::g_inh__X__inh_spikes] + node.get_E_inh() * ode_state[State_::g_inh_dend__X__inh_dend_spikes] + node.get_I_e() + node.B_.I_stim_grid_sum_ - ode_state[State_::V_m] * ode_state[State_::g_exc__X__exc_spikes] - ode_state[State_::V_m] * ode_state[State_::g_inh__X__inh_spikes] - ode_state[State_::V_m] * ode_state[State_::g_inh_dend__X__inh_dend_spikes] + ode_state[State_::V_m] * ode_state[State_::g_exc2__X__exc_spikes] * ode_state[State_::g_inh_dend2__X__inh_dend_spikes] / node.get_alpha_ei_inv()) / node.get_C_m();
  f[State_::g_exc2__X__exc_spikes] = (-(ode_state[State_::g_exc2__X__exc_spikes])) / node.get_tau_syn_exc();
  f[State_::g_inh__X__inh_spikes] = (-(ode_state[State_::g_inh__X__inh_spikes])) / node.get_tau_syn_inh();
  f[State_::g_exc__X__exc_spikes] = (-(ode_state[State_::g_exc__X__exc_spikes])) / node.get_tau_syn_exc();
  f[State_::g_inh_dend2__X__inh_dend_spikes] = (-(ode_state[State_::g_inh_dend2__X__inh_dend_spikes])) / node.get_tau_syn_inh();
  f[State_::g_inh_dend__X__inh_dend_spikes] = (-(ode_state[State_::g_inh_dend__X__inh_dend_spikes])) / node.get_tau_syn_inh();
  f[State_::r] = 0.;

  return GSL_SUCCESS;
}

void iaf_cond_exp_dend_nestml::update(nest::Time const & origin,const long from, const long to)
{
  const double __resolution = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the resolution() function



  for ( long lag = from ; lag < to ; ++lag )
  {
    B_.exc_spikes_grid_sum_ = get_exc_spikes().get_value(lag);
    B_.inh_spikes_grid_sum_ = get_inh_spikes().get_value(lag);
    B_.inh_dend_spikes_grid_sum_ = get_inh_dend_spikes().get_value(lag);
    B_.I_stim_grid_sum_ = get_I_stim().get_value(lag);

    // NESTML generated code for the update block:
  double g_exc2__X__exc_spikes__tmp = V_.__P__g_exc2__X__exc_spikes__g_exc2__X__exc_spikes * get_g_exc2__X__exc_spikes();
  double g_inh__X__inh_spikes__tmp = V_.__P__g_inh__X__inh_spikes__g_inh__X__inh_spikes * get_g_inh__X__inh_spikes();
  double g_exc__X__exc_spikes__tmp = V_.__P__g_exc__X__exc_spikes__g_exc__X__exc_spikes * get_g_exc__X__exc_spikes();
  double g_inh_dend2__X__inh_dend_spikes__tmp = V_.__P__g_inh_dend2__X__inh_dend_spikes__g_inh_dend2__X__inh_dend_spikes * get_g_inh_dend2__X__inh_dend_spikes();
  double g_inh_dend__X__inh_dend_spikes__tmp = V_.__P__g_inh_dend__X__inh_dend_spikes__g_inh_dend__X__inh_dend_spikes * get_g_inh_dend__X__inh_dend_spikes();
  double __t = 0;
  // numerical integration with adaptive step size control:
  // ------------------------------------------------------
  // gsl_odeiv_evolve_apply performs only a single numerical
  // integration step, starting from t and bounded by step;
  // the while-loop ensures integration over the whole simulation
  // step (0, step] if more than one integration step is needed due
  // to a small integration step size;
  // note that (t+IntegrationStep > step) leads to integration over
  // (t, step] and afterwards setting t to step, but it does not
  // enforce setting IntegrationStep to step-t; this is of advantage
  // for a consistent and efficient integration across subsequent
  // simulation intervals
  while ( __t < B_.__step )
  {
    const int status = gsl_odeiv_evolve_apply(B_.__e,
                                              B_.__c,
                                              B_.__s,
                                              &B_.__sys,              // system of ODE
                                              &__t,                   // from t
                                              B_.__step,              // to t <= step
                                              &B_.__integration_step, // integration step size
                                              S_.ode_state);          // neuronal state

    if ( status != GSL_SUCCESS )
    {
      throw nest::GSLSolverFailure( get_name(), status );
    }
  }
  /* replace analytically solvable variables with precisely integrated values  */
  S_.ode_state[State_::g_exc2__X__exc_spikes] = g_exc2__X__exc_spikes__tmp;
  S_.ode_state[State_::g_inh__X__inh_spikes] = g_inh__X__inh_spikes__tmp;
  S_.ode_state[State_::g_exc__X__exc_spikes] = g_exc__X__exc_spikes__tmp;
  S_.ode_state[State_::g_inh_dend2__X__inh_dend_spikes] = g_inh_dend2__X__inh_dend_spikes__tmp;
  S_.ode_state[State_::g_inh_dend__X__inh_dend_spikes] = g_inh_dend__X__inh_dend_spikes__tmp;
      S_.ode_state[State_::g_exc2__X__exc_spikes] += (B_.exc_spikes_grid_sum_) / (1.0);
      S_.ode_state[State_::g_exc__X__exc_spikes] += (B_.exc_spikes_grid_sum_) / (1.0);
      S_.ode_state[State_::g_inh__X__inh_spikes] += (B_.inh_spikes_grid_sum_) / (1.0);
      S_.ode_state[State_::g_inh_dend2__X__inh_dend_spikes] += (B_.inh_dend_spikes_grid_sum_) / (1.0);
      S_.ode_state[State_::g_inh_dend__X__inh_dend_spikes] += (B_.inh_dend_spikes_grid_sum_) / (1.0);
  if (get_r()!=0)
  {
      S_.ode_state[State_::r] = get_r() - 1;
      S_.ode_state[State_::V_m] = P_.V_reset;
  }
  else if (get_V_m()>=P_.V_th)
  {
      S_.ode_state[State_::r] = V_.RefractoryCounts;
      S_.ode_state[State_::V_m] = P_.V_reset;
  set_spiketime(nest::Time::step(origin.get_steps()+lag+1));
  nest::SpikeEvent se;
  nest::kernel().event_delivery_manager.send(*this, se, lag);
  }

    // voltage logging
    B_.logger_.record_data(origin.get_steps() + lag);
  }
}

// Do not move this function as inline to h-file. It depends on
// universal_data_logger_impl.h being included here.
void iaf_cond_exp_dend_nestml::handle(nest::DataLoggingRequest& e)
{
  B_.logger_.handle(e);
}

void iaf_cond_exp_dend_nestml::handle(nest::SpikeEvent &e)
{
  assert(e.get_delay_steps() > 0);
  assert( e.get_rport() < static_cast< int >( B_.spike_inputs_.size() ) );

  B_.spike_inputs_[ e.get_rport() ].add_value(
    e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin() ),
    e.get_weight() * e.get_multiplicity() );
}

void iaf_cond_exp_dend_nestml::handle(nest::CurrentEvent& e)
{
  assert(e.get_delay_steps() > 0);

  const double current = e.get_current();     // we assume that in NEST, this returns a current in pA
  const double weight = e.get_weight();
  get_I_stim().add_value(
               e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin()),
               weight * current );
}

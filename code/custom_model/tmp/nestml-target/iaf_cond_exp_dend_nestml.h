/**
 *  iaf_cond_exp_dend_nestml.h
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
#ifndef IAF_COND_EXP_DEND_NESTML
#define IAF_COND_EXP_DEND_NESTML

#include "config.h"

#ifndef HAVE_GSL
#error "The GSL library is required for neurons that require a numerical solver."
#endif

// External includes:
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

// Includes from nestkernel:
#include "archiving_node.h"
#include "connection.h"
#include "event.h"
#include "nest_types.h"
#include "ring_buffer.h"
#include "universal_data_logger.h"

// Includes from sli:
#include "dictdatum.h"

namespace nest
{
namespace iaf_cond_exp_dend_nestml_names
{
    const Name _r( "r" );
    const Name _V_m( "V_m" );
    const Name _g_exc2__X__exc_spikes( "g_exc2__X__exc_spikes" );
    const Name _g_inh__X__inh_spikes( "g_inh__X__inh_spikes" );
    const Name _g_exc__X__exc_spikes( "g_exc__X__exc_spikes" );
    const Name _g_inh_dend2__X__inh_dend_spikes( "g_inh_dend2__X__inh_dend_spikes" );
    const Name _g_inh_dend__X__inh_dend_spikes( "g_inh_dend__X__inh_dend_spikes" );
    const Name _V_th( "V_th" );
    const Name _V_reset( "V_reset" );
    const Name _t_ref( "t_ref" );
    const Name _g_L( "g_L" );
    const Name _C_m( "C_m" );
    const Name _E_exc( "E_exc" );
    const Name _E_inh( "E_inh" );
    const Name _E_L( "E_L" );
    const Name _tau_syn_exc( "tau_syn_exc" );
    const Name _tau_syn_inh( "tau_syn_inh" );
    const Name _alpha_ei_inv( "alpha_ei_inv" );
    const Name _I_e( "I_e" );
}
}



/**
 * Function computing right-hand side of ODE for GSL solver.
 * @note Must be declared here so we can befriend it in class.
 * @note Must have C-linkage for passing to GSL. Internally, it is
 *       a first-class C++ function, but cannot be a member function
 *       because of the C-linkage.
 * @note No point in declaring it inline, since it is called
 *       through a function pointer.
 * @param void* Pointer to model neuron instance.
**/
extern "C" inline int iaf_cond_exp_dend_nestml_dynamics( double, const double y[], double f[], void* pnode );


#include "nest_time.h"




/* BeginDocumentation
  Name: iaf_cond_exp_dend_nestml.

  Description:

    

  Parameters:
  The following parameters can be set in the status dictionary.
V_th [mV]  Threshold potential
V_reset [mV]  Reset potential
t_ref [ms]  Refractory period
g_L [nS]  Leak conductance
C_m [pF]  Membrane capacitance
E_exc [mV]  Inhibitory reversal potential
E_inh [mV]  Inhibitory reversal potential
E_L [mV]  Leak reversal potential (aka resting potential)
tau_syn_exc [ms]  Synaptic time constant of excitatory synapse
tau_syn_inh [ms]  Synaptic time constant of inhibitory synapse
alpha_ei_inv [nS]  Dendritic interaction parameter between syn_inh_dend and syn_exc
 constant external input current
I_e [pA]  constant external input current


  Dynamic state variables:
r [integer]  counts number of tick during the refractory period
V_m [mV]  membrane potential


  Sends: nest::SpikeEvent

  Receives: Spike, Current, DataLoggingRequest
*/
class iaf_cond_exp_dend_nestml : public nest::ArchivingNode
{
public:
  /**
   * The constructor is only used to create the model prototype in the model manager.
  **/
  iaf_cond_exp_dend_nestml();

  /**
   * The copy constructor is used to create model copies and instances of the model.
   * @node The copy constructor needs to initialize the parameters and the state.
   *       Initialization of buffers and interal variables is deferred to
   *       @c init_buffers_() and @c pre_run_hook() (or calibrate() in NEST 3.3 and older).
  **/
  iaf_cond_exp_dend_nestml(const iaf_cond_exp_dend_nestml &);

  /**
   * Destructor.
  **/
  ~iaf_cond_exp_dend_nestml();

  // -------------------------------------------------------------------------
  //   Import sets of overloaded virtual functions.
  //   See: Technical Issues / Virtual Functions: Overriding, Overloading,
  //        and Hiding
  // -------------------------------------------------------------------------

  using nest::Node::handles_test_event;
  using nest::Node::handle;

  /**
   * Used to validate that we can send nest::SpikeEvent to desired target:port.
  **/
  nest::port send_test_event(nest::Node& target, nest::rport receptor_type, nest::synindex, bool);

  // -------------------------------------------------------------------------
  //   Functions handling incoming events.
  //   We tell nest that we can handle incoming events of various types by
  //   defining handle() for the given event.
  // -------------------------------------------------------------------------


  void handle(nest::SpikeEvent &);        //! accept spikes
  void handle(nest::CurrentEvent &);      //! accept input current
  void handle(nest::DataLoggingRequest &);//! allow recording with multimeter
  nest::port handles_test_event(nest::SpikeEvent&, nest::port);
  nest::port handles_test_event(nest::CurrentEvent&, nest::port);
  nest::port handles_test_event(nest::DataLoggingRequest&, nest::port);

  // -------------------------------------------------------------------------
  //   Functions for getting/setting parameters and state values.
  // -------------------------------------------------------------------------

  void get_status(DictionaryDatum &) const;
  void set_status(const DictionaryDatum &);

  // -------------------------------------------------------------------------
  //   Getters/setters for state block
  // -------------------------------------------------------------------------

  inline long get_r() const
  {
    return S_.ode_state[State_::r];
  }

  inline void set_r(const long __v)
  {
    S_.ode_state[State_::r] = __v;
  }

  inline double get_V_m() const
  {
    return S_.ode_state[State_::V_m];
  }

  inline void set_V_m(const double __v)
  {
    S_.ode_state[State_::V_m] = __v;
  }

  inline double get_g_exc2__X__exc_spikes() const
  {
    return S_.ode_state[State_::g_exc2__X__exc_spikes];
  }

  inline void set_g_exc2__X__exc_spikes(const double __v)
  {
    S_.ode_state[State_::g_exc2__X__exc_spikes] = __v;
  }

  inline double get_g_inh__X__inh_spikes() const
  {
    return S_.ode_state[State_::g_inh__X__inh_spikes];
  }

  inline void set_g_inh__X__inh_spikes(const double __v)
  {
    S_.ode_state[State_::g_inh__X__inh_spikes] = __v;
  }

  inline double get_g_exc__X__exc_spikes() const
  {
    return S_.ode_state[State_::g_exc__X__exc_spikes];
  }

  inline void set_g_exc__X__exc_spikes(const double __v)
  {
    S_.ode_state[State_::g_exc__X__exc_spikes] = __v;
  }

  inline double get_g_inh_dend2__X__inh_dend_spikes() const
  {
    return S_.ode_state[State_::g_inh_dend2__X__inh_dend_spikes];
  }

  inline void set_g_inh_dend2__X__inh_dend_spikes(const double __v)
  {
    S_.ode_state[State_::g_inh_dend2__X__inh_dend_spikes] = __v;
  }

  inline double get_g_inh_dend__X__inh_dend_spikes() const
  {
    return S_.ode_state[State_::g_inh_dend__X__inh_dend_spikes];
  }

  inline void set_g_inh_dend__X__inh_dend_spikes(const double __v)
  {
    S_.ode_state[State_::g_inh_dend__X__inh_dend_spikes] = __v;
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for parameters
  // -------------------------------------------------------------------------

  inline double get_V_th() const
  {
    return P_.V_th;
  }

  inline void set_V_th(const double __v)
  {
    P_.V_th = __v;
  }

  inline double get_V_reset() const
  {
    return P_.V_reset;
  }

  inline void set_V_reset(const double __v)
  {
    P_.V_reset = __v;
  }

  inline double get_t_ref() const
  {
    return P_.t_ref;
  }

  inline void set_t_ref(const double __v)
  {
    P_.t_ref = __v;
  }

  inline double get_g_L() const
  {
    return P_.g_L;
  }

  inline void set_g_L(const double __v)
  {
    P_.g_L = __v;
  }

  inline double get_C_m() const
  {
    return P_.C_m;
  }

  inline void set_C_m(const double __v)
  {
    P_.C_m = __v;
  }

  inline double get_E_exc() const
  {
    return P_.E_exc;
  }

  inline void set_E_exc(const double __v)
  {
    P_.E_exc = __v;
  }

  inline double get_E_inh() const
  {
    return P_.E_inh;
  }

  inline void set_E_inh(const double __v)
  {
    P_.E_inh = __v;
  }

  inline double get_E_L() const
  {
    return P_.E_L;
  }

  inline void set_E_L(const double __v)
  {
    P_.E_L = __v;
  }

  inline double get_tau_syn_exc() const
  {
    return P_.tau_syn_exc;
  }

  inline void set_tau_syn_exc(const double __v)
  {
    P_.tau_syn_exc = __v;
  }

  inline double get_tau_syn_inh() const
  {
    return P_.tau_syn_inh;
  }

  inline void set_tau_syn_inh(const double __v)
  {
    P_.tau_syn_inh = __v;
  }

  inline double get_alpha_ei_inv() const
  {
    return P_.alpha_ei_inv;
  }

  inline void set_alpha_ei_inv(const double __v)
  {
    P_.alpha_ei_inv = __v;
  }

  inline double get_I_e() const
  {
    return P_.I_e;
  }

  inline void set_I_e(const double __v)
  {
    P_.I_e = __v;
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for internals
  // -------------------------------------------------------------------------

  inline long get_RefractoryCounts() const
  {
    return V_.RefractoryCounts;
  }

  inline void set_RefractoryCounts(const long __v)
  {
    V_.RefractoryCounts = __v;
  }

  inline double get___h() const
  {
    return V_.__h;
  }

  inline void set___h(const double __v)
  {
    V_.__h = __v;
  }

  inline double get___P__g_exc2__X__exc_spikes__g_exc2__X__exc_spikes() const
  {
    return V_.__P__g_exc2__X__exc_spikes__g_exc2__X__exc_spikes;
  }

  inline void set___P__g_exc2__X__exc_spikes__g_exc2__X__exc_spikes(const double __v)
  {
    V_.__P__g_exc2__X__exc_spikes__g_exc2__X__exc_spikes = __v;
  }

  inline double get___P__g_inh__X__inh_spikes__g_inh__X__inh_spikes() const
  {
    return V_.__P__g_inh__X__inh_spikes__g_inh__X__inh_spikes;
  }

  inline void set___P__g_inh__X__inh_spikes__g_inh__X__inh_spikes(const double __v)
  {
    V_.__P__g_inh__X__inh_spikes__g_inh__X__inh_spikes = __v;
  }

  inline double get___P__g_exc__X__exc_spikes__g_exc__X__exc_spikes() const
  {
    return V_.__P__g_exc__X__exc_spikes__g_exc__X__exc_spikes;
  }

  inline void set___P__g_exc__X__exc_spikes__g_exc__X__exc_spikes(const double __v)
  {
    V_.__P__g_exc__X__exc_spikes__g_exc__X__exc_spikes = __v;
  }

  inline double get___P__g_inh_dend2__X__inh_dend_spikes__g_inh_dend2__X__inh_dend_spikes() const
  {
    return V_.__P__g_inh_dend2__X__inh_dend_spikes__g_inh_dend2__X__inh_dend_spikes;
  }

  inline void set___P__g_inh_dend2__X__inh_dend_spikes__g_inh_dend2__X__inh_dend_spikes(const double __v)
  {
    V_.__P__g_inh_dend2__X__inh_dend_spikes__g_inh_dend2__X__inh_dend_spikes = __v;
  }

  inline double get___P__g_inh_dend__X__inh_dend_spikes__g_inh_dend__X__inh_dend_spikes() const
  {
    return V_.__P__g_inh_dend__X__inh_dend_spikes__g_inh_dend__X__inh_dend_spikes;
  }

  inline void set___P__g_inh_dend__X__inh_dend_spikes__g_inh_dend__X__inh_dend_spikes(const double __v)
  {
    V_.__P__g_inh_dend__X__inh_dend_spikes__g_inh_dend__X__inh_dend_spikes = __v;
  }



protected:

private:
  void recompute_internal_variables(bool exclude_timestep=false);

private:
  /**
   * Synapse types to connect to
   * @note Excluded upper and lower bounds are defined as INF_, SUP_.
   *       Excluding port 0 avoids accidental connections.
  **/
  enum SynapseTypes
  {
    INF_SPIKE_RECEPTOR = 0,
      EXC_SPIKES ,
      INH_SPIKES ,
      INH_DEND_SPIKES ,
    SUP_SPIKE_RECEPTOR
  };

  /**
   * Reset internal buffers of neuron.
  **/
  void init_buffers_();

  /**
   * Initialize auxiliary quantities, leave parameters and state untouched.
  **/
  void calibrate();

  /**
   * Take neuron through given time interval
  **/
  void update(nest::Time const &, const long, const long);

  // The next two classes need to be friends to access the State_ class/member
  friend class nest::RecordablesMap<iaf_cond_exp_dend_nestml>;
  friend class nest::UniversalDataLogger<iaf_cond_exp_dend_nestml>;

  /**
   * Free parameters of the neuron.
   *
   *
   *
   * These are the parameters that can be set by the user through @c `node.set()`.
   * They are initialized from the model prototype when the node is created.
   * Parameters do not change during calls to @c update() and are not reset by
   * @c ResetNetwork.
   *
   * @note Parameters_ need neither copy constructor nor @c operator=(), since
   *       all its members are copied properly by the default copy constructor
   *       and assignment operator. Important:
   *       - If Parameters_ contained @c Time members, you need to define the
   *         assignment operator to recalibrate all members of type @c Time . You
   *         may also want to define the assignment operator.
   *       - If Parameters_ contained members that cannot copy themselves, such
   *         as C-style arrays, you need to define the copy constructor and
   *         assignment operator to copy those members.
  **/
  struct Parameters_
  {    
    //!  Threshold potential
    double V_th;
    //!  Reset potential
    double V_reset;
    //!  Refractory period
    double t_ref;
    //!  Leak conductance
    double g_L;
    //!  Membrane capacitance
    double C_m;
    //!  Inhibitory reversal potential
    double E_exc;
    //!  Inhibitory reversal potential
    double E_inh;
    //!  Leak reversal potential (aka resting potential)
    double E_L;
    //!  Synaptic time constant of excitatory synapse
    double tau_syn_exc;
    //!  Synaptic time constant of inhibitory synapse
    double tau_syn_inh;
    //!  Dendritic interaction parameter between syn_inh_dend and syn_exc
    //!  constant external input current
    double alpha_ei_inv;
    //!  constant external input current
    double I_e;

    double __gsl_error_tol;

    /**
     * Initialize parameters to their default values.
    **/
    Parameters_();
  };

  /**
   * Dynamic state of the neuron.
   *
   *
   *
   * These are the state variables that are advanced in time by calls to
   * @c update(). In many models, some or all of them can be set by the user
   * through @c `node.set()`. The state variables are initialized from the model
   * prototype when the node is created. State variables are reset by @c ResetNetwork.
   *
   * @note State_ need neither copy constructor nor @c operator=(), since
   *       all its members are copied properly by the default copy constructor
   *       and assignment operator. Important:
   *       - If State_ contained @c Time members, you need to define the
   *         assignment operator to recalibrate all members of type @c Time . You
   *         may also want to define the assignment operator.
   *       - If State_ contained members that cannot copy themselves, such
   *         as C-style arrays, you need to define the copy constructor and
   *         assignment operator to copy those members.
  **/
  struct State_
  {
    //! Symbolic indices to the elements of the state vector y
    enum StateVecElems
    {
      V_m,
      g_exc2__X__exc_spikes,
      g_inh__X__inh_spikes,
      g_exc__X__exc_spikes,
      g_inh_dend2__X__inh_dend_spikes,
      g_inh_dend__X__inh_dend_spikes,
      // moved state variables from synapse
      r,
      STATE_VEC_SIZE
    };

    //! state vector, must be C-array for GSL solver
    double ode_state[STATE_VEC_SIZE];

    State_();
  };

  struct DelayedVariables_
  {
  };

  /**
   * Internal variables of the neuron.
   *
   *
   *
   * These variables must be initialized by @c pre_run_hook (or calibrate in NEST 3.3 and older), which is called before
   * the first call to @c update() upon each call to @c Simulate.
   * @node Variables_ needs neither constructor, copy constructor or assignment operator,
   *       since it is initialized by @c pre_run_hook() (or calibrate() in NEST 3.3 and older). If Variables_ has members that
   *       cannot destroy themselves, Variables_ will need a destructor.
  **/
  struct Variables_
  {
    //!  refractory time in steps
    long RefractoryCounts;
    double __h;
    double __P__g_exc2__X__exc_spikes__g_exc2__X__exc_spikes;
    double __P__g_inh__X__inh_spikes__g_inh__X__inh_spikes;
    double __P__g_exc__X__exc_spikes__g_exc__X__exc_spikes;
    double __P__g_inh_dend2__X__inh_dend_spikes__g_inh_dend2__X__inh_dend_spikes;
    double __P__g_inh_dend__X__inh_dend_spikes__g_inh_dend__X__inh_dend_spikes;
  };

  /**
   * Buffers of the neuron.
   * Usually buffers for incoming spikes and data logged for analog recorders.
   * Buffers must be initialized by @c init_buffers_(), which is called before
   * @c pre_run_hook() (or calibrate() in NEST 3.3 and older) on the first call to @c Simulate after the start of NEST,
   * ResetKernel or ResetNetwork.
   * @node Buffers_ needs neither constructor, copy constructor or assignment operator,
   *       since it is initialized by @c init_nodes_(). If Buffers_ has members that
   *       cannot destroy themselves, Buffers_ will need a destructor.
  **/
  struct Buffers_
  {
    Buffers_(iaf_cond_exp_dend_nestml &);
    Buffers_(const Buffers_ &, iaf_cond_exp_dend_nestml &);

    /**
     * Logger for all analog data
    **/
    nest::UniversalDataLogger<iaf_cond_exp_dend_nestml> logger_;
    std::vector<long> receptor_types_;
    // -----------------------------------------------------------------------
    //   Buffers and sums of incoming spikes/currents per timestep
    // -----------------------------------------------------------------------
    std::vector< nest::RingBuffer > spike_inputs_;
    inline nest::RingBuffer& get_exc_spikes() {  return spike_inputs_[EXC_SPIKES - 1]; }
    double exc_spikes_grid_sum_;
    inline nest::RingBuffer& get_inh_spikes() {  return spike_inputs_[INH_SPIKES - 1]; }
    double inh_spikes_grid_sum_;
    inline nest::RingBuffer& get_inh_dend_spikes() {  return spike_inputs_[INH_DEND_SPIKES - 1]; }
    double inh_dend_spikes_grid_sum_;
    //!< Buffer for input (type: pA)
    nest::RingBuffer I_stim;
    inline nest::RingBuffer& get_I_stim() {return I_stim;}
    double I_stim_grid_sum_;

    // -----------------------------------------------------------------------
    //   GSL ODE solver data structures
    // -----------------------------------------------------------------------

    gsl_odeiv_step* __s;    //!< stepping function
    gsl_odeiv_control* __c; //!< adaptive stepsize control function
    gsl_odeiv_evolve* __e;  //!< evolution function
    gsl_odeiv_system __sys; //!< struct describing system

    // __integration_step should be reset with the neuron on ResetNetwork,
    // but remain unchanged during calibration. Since it is initialized with
    // step_, and the resolution cannot change after nodes have been created,
    // it is safe to place both here.
    double __step;             //!< step size in ms
    double __integration_step; //!< current integration time step, updated by GSL

  };

  // -------------------------------------------------------------------------
  //   Getters/setters for inline expressions
  // -------------------------------------------------------------------------
  
  inline double get_I_syn_exc() const
  {
    return get_g_exc__X__exc_spikes() * (get_V_m() - P_.E_exc);
  }

  inline double get_I_syn_inh() const
  {
    return get_g_inh__X__inh_spikes() * (get_V_m() - P_.E_inh);
  }

  inline double get_I_syn_inh_dend() const
  {
    return get_g_inh_dend__X__inh_dend_spikes() * (get_V_m() - P_.E_inh);
  }

  inline double get_I_syn_ei_dend() const
  {
    return get_g_inh_dend2__X__inh_dend_spikes() * get_g_exc2__X__exc_spikes() * (get_V_m() - P_.E_exc) / P_.alpha_ei_inv;
  }

  inline double get_I_leak() const
  {
    return P_.g_L * (get_V_m() - P_.E_L);
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for input buffers
  // -------------------------------------------------------------------------
  
  inline nest::RingBuffer& get_exc_spikes() {return B_.get_exc_spikes();};
  inline nest::RingBuffer& get_inh_spikes() {return B_.get_inh_spikes();};
  inline nest::RingBuffer& get_inh_dend_spikes() {return B_.get_inh_dend_spikes();};
  inline nest::RingBuffer& get_I_stim() {return B_.get_I_stim();};

  // -------------------------------------------------------------------------
  //   Member variables of neuron model.
  //   Each model neuron should have precisely the following four data members,
  //   which are one instance each of the parameters, state, buffers and variables
  //   structures. Experience indicates that the state and variables member should
  //   be next to each other to achieve good efficiency (caching).
  //   Note: Devices require one additional data member, an instance of the
  //   ``Device`` child class they belong to.
  // -------------------------------------------------------------------------


  Parameters_       P_;        //!< Free parameters.
  State_            S_;        //!< Dynamic state.
  DelayedVariables_ DV_;       //!< Delayed state variables.
  Variables_        V_;        //!< Internal Variables
  Buffers_          B_;        //!< Buffers.

  //! Mapping of recordables names to access functions
  static nest::RecordablesMap<iaf_cond_exp_dend_nestml> recordablesMap_;
  friend int iaf_cond_exp_dend_nestml_dynamics( double, const double y[], double f[], void* pnode );


}; /* neuron iaf_cond_exp_dend_nestml */

inline nest::port iaf_cond_exp_dend_nestml::send_test_event(nest::Node& target, nest::rport receptor_type, nest::synindex, bool)
{
  // You should usually not change the code in this function.
  // It confirms that the target of connection @c c accepts @c nest::SpikeEvent on
  // the given @c receptor_type.
  nest::SpikeEvent e;
  e.set_sender(*this);
  return target.handles_test_event(e, receptor_type);
}

inline nest::port iaf_cond_exp_dend_nestml::handles_test_event(nest::SpikeEvent&, nest::port receptor_type)
{
    assert( B_.spike_inputs_.size() == 3 );

    if ( !( INF_SPIKE_RECEPTOR < receptor_type && receptor_type < SUP_SPIKE_RECEPTOR ) )
    {
      throw nest::UnknownReceptorType( receptor_type, get_name() );
      return 0;
    }
    else
    {
      return receptor_type - 1;
    }
}

inline nest::port iaf_cond_exp_dend_nestml::handles_test_event(nest::CurrentEvent&, nest::port receptor_type)
{
  // You should usually not change the code in this function.
  // It confirms to the connection management system that we are able
  // to handle @c CurrentEvent on port 0. You need to extend the function
  // if you want to differentiate between input ports.
  if (receptor_type != 0)
  {
    throw nest::UnknownReceptorType(receptor_type, get_name());
  }
  return 0;
}

inline nest::port iaf_cond_exp_dend_nestml::handles_test_event(nest::DataLoggingRequest& dlr, nest::port receptor_type)
{
  // You should usually not change the code in this function.
  // It confirms to the connection management system that we are able
  // to handle @c DataLoggingRequest on port 0.
  // The function also tells the built-in UniversalDataLogger that this node
  // is recorded from and that it thus needs to collect data during simulation.
  if (receptor_type != 0)
  {
    throw nest::UnknownReceptorType(receptor_type, get_name());
  }

  return B_.logger_.connect_logging_device(dlr, recordablesMap_);
}

inline void iaf_cond_exp_dend_nestml::get_status(DictionaryDatum &__d) const
{
  // parameters
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_V_th, get_V_th());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_V_reset, get_V_reset());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_t_ref, get_t_ref());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_L, get_g_L());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_C_m, get_C_m());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_E_exc, get_E_exc());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_E_inh, get_E_inh());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_E_L, get_E_L());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_tau_syn_exc, get_tau_syn_exc());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_tau_syn_inh, get_tau_syn_inh());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_alpha_ei_inv, get_alpha_ei_inv());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_I_e, get_I_e());

  // initial values for state variables in ODE or kernel
  def<long>(__d, nest::iaf_cond_exp_dend_nestml_names::_r, get_r());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_V_m, get_V_m());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_exc2__X__exc_spikes, get_g_exc2__X__exc_spikes());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_inh__X__inh_spikes, get_g_inh__X__inh_spikes());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_exc__X__exc_spikes, get_g_exc__X__exc_spikes());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_inh_dend2__X__inh_dend_spikes, get_g_inh_dend2__X__inh_dend_spikes());
  def<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_inh_dend__X__inh_dend_spikes, get_g_inh_dend__X__inh_dend_spikes());

  ArchivingNode::get_status( __d );
  DictionaryDatum __receptor_type = new Dictionary();
  ( *__receptor_type )[ "EXC_SPIKES" ] = EXC_SPIKES;
  ( *__receptor_type )[ "INH_SPIKES" ] = INH_SPIKES;
  ( *__receptor_type )[ "INH_DEND_SPIKES" ] = INH_DEND_SPIKES;
  ( *__d )[ "receptor_types" ] = __receptor_type;

  (*__d)[nest::names::recordables] = recordablesMap_.get_list();
  def< double >(__d, nest::names::gsl_error_tol, P_.__gsl_error_tol);
  if ( P_.__gsl_error_tol <= 0. ){
    throw nest::BadProperty( "The gsl_error_tol must be strictly positive." );
  }
}

inline void iaf_cond_exp_dend_nestml::set_status(const DictionaryDatum &__d)
{
  // parameters
  double tmp_V_th = get_V_th();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_V_th, tmp_V_th);
  double tmp_V_reset = get_V_reset();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_V_reset, tmp_V_reset);
  double tmp_t_ref = get_t_ref();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_t_ref, tmp_t_ref);
  double tmp_g_L = get_g_L();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_L, tmp_g_L);
  double tmp_C_m = get_C_m();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_C_m, tmp_C_m);
  double tmp_E_exc = get_E_exc();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_E_exc, tmp_E_exc);
  double tmp_E_inh = get_E_inh();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_E_inh, tmp_E_inh);
  double tmp_E_L = get_E_L();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_E_L, tmp_E_L);
  double tmp_tau_syn_exc = get_tau_syn_exc();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_tau_syn_exc, tmp_tau_syn_exc);
  double tmp_tau_syn_inh = get_tau_syn_inh();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_tau_syn_inh, tmp_tau_syn_inh);
  double tmp_alpha_ei_inv = get_alpha_ei_inv();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_alpha_ei_inv, tmp_alpha_ei_inv);
  double tmp_I_e = get_I_e();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_I_e, tmp_I_e);

  // initial values for state variables in ODE or kernel
  long tmp_r = get_r();
  updateValue<long>(__d, nest::iaf_cond_exp_dend_nestml_names::_r, tmp_r);
  double tmp_V_m = get_V_m();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_V_m, tmp_V_m);
  double tmp_g_exc2__X__exc_spikes = get_g_exc2__X__exc_spikes();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_exc2__X__exc_spikes, tmp_g_exc2__X__exc_spikes);
  double tmp_g_inh__X__inh_spikes = get_g_inh__X__inh_spikes();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_inh__X__inh_spikes, tmp_g_inh__X__inh_spikes);
  double tmp_g_exc__X__exc_spikes = get_g_exc__X__exc_spikes();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_exc__X__exc_spikes, tmp_g_exc__X__exc_spikes);
  double tmp_g_inh_dend2__X__inh_dend_spikes = get_g_inh_dend2__X__inh_dend_spikes();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_inh_dend2__X__inh_dend_spikes, tmp_g_inh_dend2__X__inh_dend_spikes);
  double tmp_g_inh_dend__X__inh_dend_spikes = get_g_inh_dend__X__inh_dend_spikes();
  updateValue<double>(__d, nest::iaf_cond_exp_dend_nestml_names::_g_inh_dend__X__inh_dend_spikes, tmp_g_inh_dend__X__inh_dend_spikes);

  // We now know that (ptmp, stmp) are consistent. We do not
  // write them back to (P_, S_) before we are also sure that
  // the properties to be set in the parent class are internally
  // consistent.
  ArchivingNode::set_status(__d);

  // if we get here, temporaries contain consistent set of properties
  set_V_th(tmp_V_th);
  set_V_reset(tmp_V_reset);
  set_t_ref(tmp_t_ref);
  set_g_L(tmp_g_L);
  set_C_m(tmp_C_m);
  set_E_exc(tmp_E_exc);
  set_E_inh(tmp_E_inh);
  set_E_L(tmp_E_L);
  set_tau_syn_exc(tmp_tau_syn_exc);
  set_tau_syn_inh(tmp_tau_syn_inh);
  set_alpha_ei_inv(tmp_alpha_ei_inv);
  set_I_e(tmp_I_e);
  set_r(tmp_r);
  set_V_m(tmp_V_m);
  set_g_exc2__X__exc_spikes(tmp_g_exc2__X__exc_spikes);
  set_g_inh__X__inh_spikes(tmp_g_inh__X__inh_spikes);
  set_g_exc__X__exc_spikes(tmp_g_exc__X__exc_spikes);
  set_g_inh_dend2__X__inh_dend_spikes(tmp_g_inh_dend2__X__inh_dend_spikes);
  set_g_inh_dend__X__inh_dend_spikes(tmp_g_inh_dend__X__inh_dend_spikes);


  updateValue< double >(__d, nest::names::gsl_error_tol, P_.__gsl_error_tol);
  if ( P_.__gsl_error_tol <= 0. )
  {
    throw nest::BadProperty( "The gsl_error_tol must be strictly positive." );
  }

  // recompute internal variables in case they are dependent on parameters or state that might have been updated in this call to set_status()
  recompute_internal_variables();
};

#endif /* #ifndef IAF_COND_EXP_DEND_NESTML */

// -*- C++ -*-
/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v3.0.11
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       https://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     https://www.dre.vanderbilt.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:631

#ifndef _TAO_IDL_LOGGERS_OUAGCU_CPP_
#define _TAO_IDL_LOGGERS_OUAGCU_CPP_


#include "LoggerS.h"
#include "tao/PortableServer/Operation_Table_Perfect_Hash.h"
#include "tao/PortableServer/Upcall_Command.h"
#include "tao/PortableServer/Upcall_Wrapper.h"
#include "tao/TAO_Server_Request.h"
#include "tao/ORB_Core.h"
#include "tao/Profile.h"
#include "tao/Stub.h"
#include "tao/IFR_Client_Adapter.h"
#include "tao/Object_T.h"
#include "tao/AnyTypeCode/TypeCode.h"
#include "tao/AnyTypeCode/DynamicC.h"
#include "tao/CDR.h"
#include "tao/operation_details.h"
#include "tao/PortableInterceptor.h"
#include "ace/Dynamic_Service.h"
#include "ace/Malloc_Allocator.h"
#include "cstring"
// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_interface.cpp:1853

class TAO_Logger_Perfect_Hash_OpTable
  : public TAO_Perfect_Hash_OpTable
{
private:
  unsigned int hash (const char *str, unsigned int len) override;

public:
  const TAO_operation_db_entry * lookup (const char *str, unsigned int len) override;
};

/* C++ code produced by gperf version 2.8 (ACE version) */
/* Command-line: ace_gperf -m -M -J -c -C -D -E -T -f 0 -F 0,0 -a -o -t -p -K opname -L C++ -Z TAO_Logger_Perfect_Hash_OpTable -N lookup */

unsigned int
TAO_Logger_Perfect_Hash_OpTable::hash (const char *str, unsigned int len)
{
  static const unsigned char asso_values[] =
    {
     19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19, 19, 19,
     19, 19, 19, 19, 19,  0, 19,  0, 19, 19,
      0,  0, 19,  0, 19, 19, 19, 19,  0, 19,
      0, 19, 19, 19, 19,  0,  5, 19, 19, 19,
     19, 19, 19, 19, 19, 19, 19, 19,
    };
  return len + asso_values[static_cast<int>(str[len - 1])] + asso_values[static_cast<int>(str[0])];
}

const TAO_operation_db_entry *
TAO_Logger_Perfect_Hash_OpTable::lookup (const char *str, unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 9,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 14,
      MIN_HASH_VALUE = 3,
      MAX_HASH_VALUE = 18,
      HASH_VALUE_RANGE = 16,
      DUPLICATES = 2,
      WORDLIST_SIZE = 12
    };

  static const TAO_operation_db_entry wordlist[] =
    {
      {"",0,0},{"",0,0},{"",0,0},
      {"log", std::addressof(POA_Logger::log_skel), nullptr},
      {"_is_a", std::addressof(TAO_ServantBase::_is_a_thru_poa_skel), nullptr},
      {"shutdown", std::addressof(POA_Logger::shutdown_skel), nullptr},
      {"_interface", std::addressof(TAO_ServantBase::_interface_skel), nullptr},
      {"_get_verbose", std::addressof(POA_Logger::_get_verbose_skel), 0},
      {"_set_verbose", std::addressof(POA_Logger::_set_verbose_skel), nullptr},
      {"_repository_id", std::addressof(TAO_ServantBase::_repository_id_thru_poa_skel), nullptr},
      {"_component", std::addressof(TAO_ServantBase::_component_thru_poa_skel), nullptr},
      {"_non_existent", std::addressof(TAO_ServantBase::_non_existent_thru_poa_skel), nullptr},
    };

  static const signed char lookup[] =
    {
       -1,  -1,  -1,   3,  -1,   4,  -7,  -2,   5,  -1,   6,  -1, -24,  -1, 
        9,  10,  -1,  -1,  11, 
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int const key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          int slot = lookup[key];

          if (slot >= 0 && slot < WORDLIST_SIZE)
            {
              const char *s = wordlist[slot].opname;

              if (*str == *s && !ACE_OS::strncmp (str + 1, s + 1, len - 1))
                return &wordlist[slot];
            }
          else if (slot < 0 && slot >= -MAX_HASH_VALUE)
            return 0;
          else
            {
              unsigned int offset = key + slot + (slot > 0 ? -MAX_HASH_VALUE : MAX_HASH_VALUE);
              const TAO_operation_db_entry *base = &wordlist[-lookup[offset]];
              const TAO_operation_db_entry *ptr = base + -lookup[offset + 1];

              while (--ptr >= base)
                if (*str == *ptr->opname && !ACE_OS::strncmp (str + 1, ptr->opname + 1, len - 1))
                  return ptr;
            }
        }
    }
  return 0;
}

static TAO_Logger_Perfect_Hash_OpTable tao_Logger_optable;


// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_interface/interface_ss.cpp:89



POA_Logger::POA_Logger ()
  : TAO_ServantBase ()
{
  this->optable_ = std::addressof(tao_Logger_optable);
}

POA_Logger::POA_Logger (const POA_Logger& rhs)
  : TAO_Abstract_ServantBase (rhs),
    TAO_ServantBase (rhs)
{
}


// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/upcall_command_ss.cpp:79

class _get_verbose_Logger
  : public TAO::Upcall_Command
{
public:
  inline _get_verbose_Logger (
    POA_Logger * servant,
    TAO_Operation_Details const * operation_details,
    TAO::Argument * const args[])
    : servant_ (servant)
      , operation_details_ (operation_details)
      , args_ (args)
  {
  }

  void execute () override
  {
    TAO::SArg_Traits< ::ACE_InputCDR::to_boolean>::ret_arg_type retval =
      TAO::Portable_Server::get_ret_arg< ::ACE_InputCDR::to_boolean> (
        this->operation_details_,
        this->args_);
    
    retval =
      this->servant_->verbose ();
  }

private:
  POA_Logger * const servant_;
  TAO_Operation_Details const * const operation_details_;
  TAO::Argument * const * const args_;
};
// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_ss.cpp:167

void POA_Logger::_get_verbose_skel (
  TAO_ServerRequest & server_request,
  TAO::Portable_Server::Servant_Upcall *TAO_INTERCEPTOR (servant_upcall),
  TAO_ServantBase *servant)
{TAO::SArg_Traits< ::ACE_InputCDR::to_boolean>::ret_val retval;

  TAO::Argument * const args[] =
    {
      std::addressof(retval)
    };
  
  POA_Logger * const impl =
    dynamic_cast<POA_Logger *> (servant);

  if (!impl)
    {
      throw ::CORBA::INTERNAL ();
    }

  _get_verbose_Logger command (
    impl,
    server_request.operation_details (),
    args);
  
  TAO::Upcall_Wrapper upcall_wrapper;
  upcall_wrapper.upcall (server_request
                         , args
                         , 1
                         , command
#if TAO_HAS_INTERCEPTORS == 1
                         , servant_upcall
                         , nullptr
                         , 0
#endif  /* TAO_HAS_INTERCEPTORS == 1 */
                         );
}


// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/upcall_command_ss.cpp:79

class _set_verbose_Logger
  : public TAO::Upcall_Command
{
public:
  inline _set_verbose_Logger (
    POA_Logger * servant,
    TAO_Operation_Details const * operation_details,
    TAO::Argument * const args[])
    : servant_ (servant)
      , operation_details_ (operation_details)
      , args_ (args)
  {
  }

  void execute () override
  {
    TAO::SArg_Traits< ::ACE_InputCDR::to_boolean>::in_arg_type arg_1 =
      TAO::Portable_Server::get_in_arg< ::ACE_InputCDR::to_boolean> (
        this->operation_details_,
        this->args_,
        1);
      
    this->servant_->verbose (
      arg_1);
  }

private:
  POA_Logger * const servant_;
  TAO_Operation_Details const * const operation_details_;
  TAO::Argument * const * const args_;
};
// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_ss.cpp:167

void POA_Logger::_set_verbose_skel (
  TAO_ServerRequest & server_request,
  TAO::Portable_Server::Servant_Upcall *TAO_INTERCEPTOR (servant_upcall),
  TAO_ServantBase *servant)
{TAO::SArg_Traits< void>::ret_val retval;
  TAO::SArg_Traits< ::ACE_InputCDR::to_boolean>::in_arg_val _tao_verbose;

  TAO::Argument * const args[] =
    {
      std::addressof(retval),
      std::addressof(_tao_verbose)
    };
  
  POA_Logger * const impl =
    dynamic_cast<POA_Logger *> (servant);

  if (!impl)
    {
      throw ::CORBA::INTERNAL ();
    }

  _set_verbose_Logger command (
    impl,
    server_request.operation_details (),
    args);
  
  TAO::Upcall_Wrapper upcall_wrapper;
  upcall_wrapper.upcall (server_request
                         , args
                         , 2
                         , command
#if TAO_HAS_INTERCEPTORS == 1
                         , servant_upcall
                         , nullptr
                         , 0
#endif  /* TAO_HAS_INTERCEPTORS == 1 */
                         );
}


// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/upcall_command_ss.cpp:79

class log_Logger
  : public TAO::Upcall_Command
{
public:
  inline log_Logger (
    POA_Logger * servant,
    TAO_Operation_Details const * operation_details,
    TAO::Argument * const args[])
    : servant_ (servant)
      , operation_details_ (operation_details)
      , args_ (args)
  {
  }

  void execute () override
  {
    TAO::SArg_Traits< std::string>::in_arg_type arg_1 =
      TAO::Portable_Server::get_in_arg< std::string> (
        this->operation_details_,
        this->args_,
        1);
      
    TAO::SArg_Traits< std::string>::in_arg_type arg_2 =
      TAO::Portable_Server::get_in_arg< std::string> (
        this->operation_details_,
        this->args_,
        2);
      
    TAO::SArg_Traits< ::CORBA::UShort>::in_arg_type arg_3 =
      TAO::Portable_Server::get_in_arg< ::CORBA::UShort> (
        this->operation_details_,
        this->args_,
        3);
      
    TAO::SArg_Traits< ::CORBA::ULong>::in_arg_type arg_4 =
      TAO::Portable_Server::get_in_arg< ::CORBA::ULong> (
        this->operation_details_,
        this->args_,
        4);
      
    TAO::SArg_Traits< std::string>::in_arg_type arg_5 =
      TAO::Portable_Server::get_in_arg< std::string> (
        this->operation_details_,
        this->args_,
        5);
      
    this->servant_->log (
      arg_1
      , arg_2
      , arg_3
      , arg_4
      , arg_5);
  }

private:
  POA_Logger * const servant_;
  TAO_Operation_Details const * const operation_details_;
  TAO::Argument * const * const args_;
};
// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_ss.cpp:167

void POA_Logger::log_skel (
  TAO_ServerRequest & server_request,
  TAO::Portable_Server::Servant_Upcall *TAO_INTERCEPTOR (servant_upcall),
  TAO_ServantBase *servant)
{TAO::SArg_Traits< void>::ret_val retval;
  TAO::SArg_Traits< std::string>::in_arg_val _tao_severidade;
  TAO::SArg_Traits< std::string>::in_arg_val _tao_endereco;
  TAO::SArg_Traits< ::CORBA::UShort>::in_arg_val _tao_pid;
  TAO::SArg_Traits< ::CORBA::ULong>::in_arg_val _tao_hora;
  TAO::SArg_Traits< std::string>::in_arg_val _tao_msg;

  TAO::Argument * const args[] =
    {
      std::addressof(retval),
      std::addressof(_tao_severidade),
      std::addressof(_tao_endereco),
      std::addressof(_tao_pid),
      std::addressof(_tao_hora),
      std::addressof(_tao_msg)
    };
  
  POA_Logger * const impl =
    dynamic_cast<POA_Logger *> (servant);

  if (!impl)
    {
      throw ::CORBA::INTERNAL ();
    }

  log_Logger command (
    impl,
    server_request.operation_details (),
    args);
  
  TAO::Upcall_Wrapper upcall_wrapper;
  upcall_wrapper.upcall (server_request
                         , args
                         , 6
                         , command
#if TAO_HAS_INTERCEPTORS == 1
                         , servant_upcall
                         , nullptr
                         , 0
#endif  /* TAO_HAS_INTERCEPTORS == 1 */
                         );
}


// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/upcall_command_ss.cpp:79

class shutdown_Logger
  : public TAO::Upcall_Command
{
public:
  inline shutdown_Logger (
    POA_Logger * servant)
    : servant_ (servant)
  {
  }

  void execute () override
  {
    this->servant_->shutdown ();
  }

private:
  POA_Logger * const servant_;
};
// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_operation/operation_ss.cpp:167

void POA_Logger::shutdown_skel (
  TAO_ServerRequest & server_request,
  TAO::Portable_Server::Servant_Upcall *TAO_INTERCEPTOR (servant_upcall),
  TAO_ServantBase *servant)
{TAO::SArg_Traits< void>::ret_val retval;

  TAO::Argument * const args[] =
    {
      std::addressof(retval)
    };
  
  POA_Logger * const impl =
    dynamic_cast<POA_Logger *> (servant);

  if (!impl)
    {
      throw ::CORBA::INTERNAL ();
    }

  shutdown_Logger command (
    impl);
  
  TAO::Upcall_Wrapper upcall_wrapper;
  upcall_wrapper.upcall (server_request
                         , args
                         , 1
                         , command
#if TAO_HAS_INTERCEPTORS == 1
                         , servant_upcall
                         , nullptr
                         , 0
#endif  /* TAO_HAS_INTERCEPTORS == 1 */
                         );
}




// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_interface/interface_ss.cpp:155





::CORBA::Boolean POA_Logger::_is_a (const char* value)
{
  return
    (
      std::strcmp (value, "IDL:Logger:1.0") == 0 ||
      std::strcmp (value, "IDL:omg.org/CORBA/Object:1.0") == 0
    );
}

const char* POA_Logger::_interface_repository_id () const
{
  return "IDL:Logger:1.0";
}


// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_interface/interface_ss.cpp:403



void POA_Logger::_dispatch (
  TAO_ServerRequest & req,
  TAO::Portable_Server::Servant_Upcall* servant_upcall)
{
  this->synchronous_upcall_dispatch (req, servant_upcall, this);
}


// TAO_IDL - Generated from
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_interface/interface_ss.cpp:354



Logger *
POA_Logger::_this ()
{
  TAO_Stub *stub = this->_create_stub ();

  TAO_Stub_Auto_Ptr safe_stub (stub);
  ::CORBA::Object_ptr tmp {};

  ::CORBA::Boolean const _tao_opt_colloc =
    stub->servant_orb_var ()->orb_core ()->optimize_collocation_objects ();
  
  ACE_NEW_RETURN (
      tmp,
      ::CORBA::Object (stub, _tao_opt_colloc, this),
      nullptr);
  
  ::CORBA::Object_var obj = tmp;
  (void) safe_stub.release ();

  return TAO::Narrow_Utils< ::Logger>::unchecked_narrow (obj.in ());
}

#endif /* ifndef */


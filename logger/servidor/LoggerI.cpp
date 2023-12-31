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
// /opt/ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1621

#include "LoggerI.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

extern CORBA::ORB_var orb;

using namespace std;

// Implementation skeleton constructor
Logger_i::Logger_i () {
	verbose_ = (::CORBA::Boolean) true;
}

// Implementation skeleton destructor
Logger_i::~Logger_i () {
}

::CORBA::Boolean Logger_i::verbose () {
  // Get verbose - retorna atual valor de verbose
  return verbose_;
}

void Logger_i::verbose (::CORBA::Boolean verbose) {
  // Set verbose - troca o valor booleano
  verbose_ = verbose;
}

void Logger_i::log (
  const std::string severidade,
  const std::string endereco,
  ::CORBA::UShort pid,
  ::CORBA::ULong hora,
  const std::string msg)
{  
  // Tratamento da severidade
  std::string severity_label = severidade;
  if (severidade == "DEBUG") {
    severity_label = "[DEBUG]";
  } else if (severidade == "WARNING") {
    severity_label = "[WARNING]";
  } else if (severidade == "ERROR") {
    severity_label = "[ERROR]";
  } else if (severidade == "CRITICAL") {
    severity_label = "[CRITICAL]";
  } else {
    severity_label = "[UNKNOWN]";
  }
	// Tratamento do verbose
	if (verbose_) {
		const time_t epoch = (time_t) hora;
		const struct tm * t = localtime(&epoch);
		char buf[80];
		strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M:%S", t);
		// Exibição da mensagem
		cout << severity_label << " - [pid: " << pid << " no endereco: " << endereco << ", hora: " << buf << "]: " << msg << endl;
	}
	
}

void Logger_i::shutdown ()
{
  orb->shutdown();
}

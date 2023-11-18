//
//   Arquitetura de Sistemas Distribuídos, Paralelos e Concorrentes
//   Escola Politécnica - PUCPR
//   Tasi Guilhen Pasin
//	 Mateus Ferro Antunes de Oliveira
//

#include <iostream>
#include <string>
#include <orbsvcs/CosNamingC.h>
#include <ctime>
#include "LoggerC.h"

using namespace std;
using namespace CosNaming;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cerr << "USAGE: " << argv[0] << " file://<ior_file>" << endl;
		return 1;
	}

	try {
		// 1. Initiate ORB
		CORBA::ORB_var orb = CORBA::ORB_init(argc,argv,"ORB");

		// 2. Obtain object reference
		CORBA::Object_ptr tmp_ref;
		Logger_var logger;

		// Lê IOR de arquivo
		//tmp_ref = orb->string_to_object(argv[1]);
		//account = Conta::_narrow(tmp_ref);

		// Obtém IOR do servidor de nomes
		tmp_ref = orb->resolve_initial_references("NameService");
		NamingContext_var sn = NamingContext::_narrow(tmp_ref);
		Name nome(1);
		nome.length(1);
		nome[0].id = CORBA::string_dup(argv[1]);
		tmp_ref = sn->resolve(nome);
		logger = Logger::_narrow(tmp_ref);

		// 3. Use logger - Trabalho
		::CORBA::UShort pid;
		::CORBA::ULong timestamp;
		string address;
		string message;
		string sev;
		string dest_ior;
		string command;

		do {
			cout << "> ";
			getline (cin, command);
			if (command == "log") {
				
				// Valores preenchidos manualmente - ficticios
				address = "172.16.254.3:8080";
				pid = 23541;
				timestamp = time(0);
				
				// Valores solicitados ao usuario
				cout << "Digite a Severidade: " << endl;
				getline(cin, sev);
				cout << "Qual a mensagem de erro: " << endl;
				getline(cin, message);
				
				// Chamar o Logger passando os 5 parametros
				logger->log(sev, address, pid, timestamp, message);
				
			} else if (command == "verbose") {
				logger->verbose((::CORBA::Boolean) !logger->verbose());
				cout << "\tVerbose: = " << logger->verbose() << endl;
			} else if (command == "shutdown") {
				logger->shutdown();
				command = "fim";	// exits client too
			}

		} while (command != "fim");

		// 4. Destroi ORB
		orb->destroy();
	} catch (CORBA::Exception& e) {
		cerr << "CORBA EXCEPTION:" << e << endl;
	}

	return 0;
}

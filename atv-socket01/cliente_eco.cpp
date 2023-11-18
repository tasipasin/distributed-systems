//
// Modelo Básico de CLIENTE TCP
// (C) 2021 Luiz Lima Jr.
// Sistemas Distribuídos - PUCPR
//
// Usando getaddrinfo() ao invés de inet_pton() (que não resolve nomes)
//

#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <stdbool.h>
#include <list>

using namespace std;

void assegure(bool cond, const char *msg);

int main(int argc, char* argv[])
{
	// Lista de portas para conectar
	list<char *> portList {"1512", "1513", "1514", "1515", "1516", "1517"};

	list<int> valuesReceived;
	const char *HOST = "localhost";
	for(char *port : portList) {
		int connAttempt = 1;
		bool connected = false;
		int clisock;
		while(!connected){
			cout << "Tentando conexão com " << HOST << ":" << port << " [" << connAttempt << "]..." << endl;
			struct addrinfo dica;
			memset(&dica,0,sizeof(dica));
			dica.ai_family = AF_INET;		// IPv4
			dica.ai_socktype = SOCK_STREAM;	// TCP

			struct addrinfo *servinfos;
			int erro = getaddrinfo(HOST, port, &dica, &servinfos);
			assegure(erro == 0, "getaddrinfo()");

			struct addrinfo *info;
			for (info = servinfos; info != nullptr; info = info->ai_next) {
				clisock = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
				if (clisock != -1) break;
			}
			assegure(info != nullptr,"socket()");

			// tenta conexão com o servidor
			erro = connect(clisock,info->ai_addr,info->ai_addrlen);
			assegure(erro != -1,"connect()");
			connected = erro != -1;
			freeaddrinfo(servinfos);
			sleep(1);
			connAttempt++;
		}
		int valueReceived;
		int bytes = read(clisock, &valueReceived, sizeof(valueReceived));

		cout << "Recebido valor " << valueReceived << "} da porta {" << port << "}" << endl;
		valuesReceived.push_back(valueReceived);

		close(clisock);
	}
	int sumAll = 0;
	for(int value : valuesReceived){
		sumAll += value;
	}
	cout << "Todos os valores recebidos. A soma total eh: " << sumAll << endl;
}

void assegure(bool cond, const char *msg)
{
	if (!cond) {
		cerr << "Erro no " << msg << endl;
		exit(1);
	}
}

//
// Modelo Básico de SERVIDOR TCP
// (C) 2021 Luiz Lima Jr.
// Sistemas Distribuídos - PUCPR
//

#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <unistd.h>

using namespace std;

void assegure(bool cond, const char *msg);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cerr << "USO: " << argv[0] << " <porta>" << endl;
		return 1;
	}

	const char *PORTA = argv[1];

	struct addrinfo dica;
	memset(&dica,0,sizeof(dica));	// "zera" estrutura
	dica.ai_family = AF_INET;		// IPv4
	dica.ai_socktype = SOCK_STREAM;	// TCP
	dica.ai_flags = AI_PASSIVE;		// use meu endereço IP

	// obtém lista de endereços IP (de acordo com dica)
	struct addrinfo *servinfos;
	int erro = getaddrinfo(nullptr, PORTA, &dica, &servinfos);
	assegure(erro == 0, "getaddrinfo()");

	int servsock;
	struct addrinfo *info;
	for (info = servinfos; info != nullptr; info = info->ai_next) {
		servsock = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
		if (servsock != -1) break;	// a 1a que for bem-sucedida está ok
	}
	assegure(info != nullptr, "socket()");

	erro = ::bind(servsock,info->ai_addr,info->ai_addrlen);
	assegure(erro == 0, "bind()");

	freeaddrinfo(servinfos);		// libera memória alocada para lista de endereços

	erro = listen(servsock,1024);	// coloca servsock em modo escuta
	assegure(erro == 0, "listen()");

	cout << "Aguardando conexoes na porta " << PORTA << endl;
	struct sockaddr_in endcli;		// endereço do cliente
	socklen_t tam_endcli;			// tamanho do endereço do cliente em bytes
	int clisock = accept(servsock,(struct sockaddr*)&endcli, &tam_endcli);	// aguarda conexões

	close(servsock);	// não mais necessário

	// trocas de mensagens
	constexpr ssize_t TAMBUF = 256;
	char buffer[TAMBUF+1];
	ssize_t bytes = read(clisock, buffer, TAMBUF);
	buffer[bytes] = '\0';	// fim de string

	string msg = buffer;

	cout << "Recebidos " << bytes << " bytes: " << msg << endl;
	msg += "_ECO";		// acrescenta sufixo à mensagem

	bytes = write(clisock,msg.c_str(), msg.size());
	cout << "Enviados " << bytes << " bytes: " << msg << endl;

	close(clisock);
}

void assegure(bool cond, const char *msg)
{
	if (!cond) {
		cerr << "Erro no " << msg << endl;
		exit(1);
	}
}

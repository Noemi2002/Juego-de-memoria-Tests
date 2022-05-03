ifndef SERVIDORJUEGOMEMORIA_SERVER_H
#define SERVIDORJUEGOMEMORIA_SERVER_H
#include <ws2tcpip.h>
#include <winsock2.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include <fcntl.h>
#include <fstream>

#include "ComunicacionJuego.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;
class Server {
public:
    Server();
    void startServer();
private:
    WSADATA wsaData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsaData);
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in hint;
    sockaddr_in client;
    int clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    ComunicacionJuego *partida;

};


#endif //SERVIDORJUEGOMEMORIA_SERVER_H

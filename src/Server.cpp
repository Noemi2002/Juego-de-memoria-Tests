#include "Server.h"


Server::Server() {
    this->partida = new ComunicacionJuego();
}

void Server::startServer() {

    int port = 5555;
    char msg[6000];

    sockaddr_in servAddr;
    ZeroMemory((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr,
                          sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }

    listen(serverSd, 5);
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);


    while(1) {
        cout << "Awaiting client response..." << endl;
        int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);

        if(newSd < 0)
        {
            cerr << "Error accepting request from client!" << endl;
            exit(1);
        }
        cout << "Connected with client!" << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        recv(newSd, (char *) &msg, sizeof(msg), 0);
        if (!strcmp(msg, "exit")) {
            cout << "Client has quit the session" << endl;

        }
        string mensaje = msg;
        partida->EnviarInstrucciones(mensaje);
        cout << "Client: " << mensaje << endl;
        string data;
        data = partida->GetMessageToSend();
        cout << "Server: " << data << endl;
        int n = data.length();

        char datachar[data.length()];

        strcpy(datachar, data.c_str());

        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        if (data == "exit") {
            send(newSd, (char *) &datachar, strlen(datachar), 0);
            break;
        }
        send(newSd, (char *) &datachar, strlen(datachar), 0);
        closesocket(newSd);
    }
    closesocket(serverSd);
    WSACleanup();
}



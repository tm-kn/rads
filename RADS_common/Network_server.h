#pragma once

#include<map>
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "6881"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "Network_data.h"

using std::map;

class Network_server
{
public:
    Network_server();
    ~Network_server();
    int disconnect_server();
    int etablish_server_communication();
    void accept_connections();
    void receive_data();
private:
    SOCKET ClientSocket;
    SOCKET ListenSocket;
    addrinfo *result;
    int iResult;
    map<unsigned int, SOCKET> sessions;
    unsigned int client_id;
    int accept_connection(unsigned int & id);
    int create_socket();
    int bind_socket();
    int listen_on_socket();
    int receive_data_from_client(unsigned int client_id, char* recvbuf);
    char network_data[MAX_PACKET_SIZE];
};


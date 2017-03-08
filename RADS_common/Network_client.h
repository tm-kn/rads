#pragma once

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#include "Network_data.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "6881"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class Network_client
{
public:
    int disconnect_client();
    int establish_client_connection();
    int send_data(char * message, int message_size);
    Network_client();
    ~Network_client();
private:
    addrinfo *ptr;
    addrinfo *result;
    int iResult;
    SOCKET ConnectSocket;
    int create_client_socket();
};


#include <iostream>

#include "Network_client.h"

Network_client::Network_client(string ip, int port)
{
    this->ip = ip;
    this->port = port;

    WSADATA wsaData;

    this->iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("Network Client: WSAStartup failed: %d\n", iResult);
        exit(1);
    }
}


Network_client::~Network_client()
{
}

int Network_client::create_client_socket() {
    struct addrinfo *result = NULL,
        *ptr = NULL,
        hints;

    this->ptr = ptr;
    this->result = result;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    char ip[50];
    char port[50];
    strcpy_s(ip, sizeof ip, this->ip.c_str());
    _itoa_s(this->port, port, 10);
 
    this->iResult = getaddrinfo(ip, port, &hints, &result);
    if (this->iResult != 0) {
        printf("Network Client: getaddrinfo failed: %d\n", this->iResult);
        WSACleanup();
        return 1;
    }

    this->ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    this->ptr = result;

    // Create a SOCKET for connecting to server
    this->ConnectSocket = socket(this->ptr->ai_family, this->ptr->ai_socktype,
        this->ptr->ai_protocol);

    return 0;
}

int Network_client::establish_client_connection() {
    if (this->create_client_socket() != 0) {
        return 1;
    }

    this->iResult = connect(this->ConnectSocket, this->ptr->ai_addr, (int)this->ptr->ai_addrlen);
    
    if (this->iResult == SOCKET_ERROR) {
        closesocket(this->ConnectSocket);
        this->ConnectSocket = INVALID_SOCKET;
        return 1;
    }

    freeaddrinfo(this->result);

    if (this->ConnectSocket == INVALID_SOCKET) {
        printf("Network Client: Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    return 0;
}

int Network_client::send_data(char * message, int message_size) {
    // Send an initial buffer
    this->iResult = send(this->ConnectSocket, message, message_size, 0);
    if (this->iResult == SOCKET_ERROR) {
        printf("Network Client: Send failed: %d\n", WSAGetLastError());
        closesocket(this->ConnectSocket);
        WSACleanup();
        return this->iResult;
    }

    return this->iResult;
}

int Network_client::disconnect_client() {
    // cleanup
    closesocket(this->ConnectSocket);
    WSACleanup();

    return 0;

}
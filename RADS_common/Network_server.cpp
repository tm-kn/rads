#include <iostream>
#include <map>
#include <vector>
#include "Network_server.h"

using std::pair;
using std::cout;
using std::endl;
using std::vector;


// Please note that Network_server::receive_data is implemented in the header file
// since it's a template and compiler will fail if it's in this cpp file.

Network_server::Network_server()
{
    WSADATA wsaData;

    // Initialize Winsock
    this->iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (this->iResult != 0) {
        printf("Network Server: WSAStartup failed: %d\n", this->iResult);
        exit(1);
    }

}


Network_server::~Network_server()
{
}

int Network_server::establish_server_communication() {
    if (this->create_socket() != 0) {
        return 1;
    }

    if (this->bind_socket() != 0) {
        return 1;
    }

    if (this->listen_on_socket() != 0) {
        return 1;
    }

    return 0;
}

int Network_server::create_socket() {
    struct addrinfo *result = NULL, *ptr = NULL, hints;

    this->result = result;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the local address and port to be used by the server
    this->iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &this->result);
    if (this->iResult != 0) {
        printf("Network Server: getaddrinfo failed: %d\n", this->iResult);
        //WSACleanup();
        return 1;
    }

    this->ListenSocket = INVALID_SOCKET;

    this->ListenSocket = socket(this->result->ai_family, this->result->ai_socktype, this->result->ai_protocol);

    if (this->ListenSocket == INVALID_SOCKET) {
        printf("Network Server: Error at socket(): %ld\n", WSAGetLastError());
        //freeaddrinfo(this->result);
        //WSACleanup();
        return 1;
    }

    u_long iMode = 1;
    this->iResult = ioctlsocket(this->ListenSocket, FIONBIO, &iMode);

    if (this->iResult == SOCKET_ERROR) {
        printf("Network server: ioctlsocket failed with error: %d\n", WSAGetLastError());
        //closesocket(this->ListenSocket);
        //WSACleanup();
        return 1;
    }

    return 0;
}

int Network_server::bind_socket() {
    // Setup the TCP listening socket
    this->iResult = bind(this->ListenSocket, this->result->ai_addr, (int)this->result->ai_addrlen);
    if (this->iResult == SOCKET_ERROR) {
        printf("Network Server: bind failed with error: %d\n", WSAGetLastError());
        //freeaddrinfo(this->result);
        //closesocket(this->ListenSocket);
        //WSACleanup();
        return 1;
    }

    freeaddrinfo(this->result);

    return 0;
}

int Network_server::listen_on_socket() {
    if (listen(this->ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        printf("Network Server: Listen failed with error: %ld\n", WSAGetLastError());
        //closesocket(this->ListenSocket);
        //WSACleanup();
        return 1;
    }

    return 0;
}

void Network_server::accept_connections() {
    if (this->accept_connection(this->client_id) == 0) {
        printf("Network server: Accepted connection to the server (client %d)\n", this->client_id);
        this->client_id++;
    }
}

int Network_server::accept_connection(unsigned int id) {
    SOCKET ClientSocket = INVALID_SOCKET;

    // Accept a client socket
    ClientSocket = accept(this->ListenSocket, NULL, NULL);

    if (ClientSocket == INVALID_SOCKET) {
        return 1;
    }

    //disable nagle on the client's socket
    char value = 1;
    setsockopt(ClientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

    // insert new client into session id table
    this->sessions.insert(pair<unsigned int, SOCKET>(id, ClientSocket));

    return 0;
}

int Network_server::receive_data_from_client(unsigned int id, char * recvbuf) {
    if (this->sessions.find(id) != this->sessions.end())
    {
        SOCKET currentSocket = this->sessions[id];
        this->iResult = recv(currentSocket, recvbuf, MAX_PACKET_SIZE, 0);

        if (this->iResult == 0)
        {
            cout << "Network server: Connection to client " << id << " closed" << endl;
            closesocket(currentSocket);
        }

        return this->iResult;
    }

    return 0;
}

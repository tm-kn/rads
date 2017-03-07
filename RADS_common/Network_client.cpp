#include <iostream>

#include "Network_client.h"

Network_client::Network_client()
{
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

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    this->iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &result);
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

    this->iResult = connect(ConnectSocket, this->ptr->ai_addr, (int)this->ptr->ai_addrlen);
    
    if (this->iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        return 1;
    }

    return 0;
}

int Network_client::send_data() {
    int recvbuflen = DEFAULT_BUFLEN;

    char *sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];

    // Send an initial buffer
    this->iResult = send(this->ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (this->iResult == SOCKET_ERROR) {
        printf("Network Client: Send failed: %d\n", WSAGetLastError());
        closesocket(this->ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Network Client: Bytes Sent: %ld\n", this->iResult);

    // shutdown the connection for sending since no more data will be sent
    // the client can still use the ConnectSocket for receiving data
    this->iResult = shutdown(ConnectSocket, SD_SEND);
    if (this->iResult == SOCKET_ERROR) {
        printf("Network Client: shutdown failed: %d\n", WSAGetLastError());
        closesocket(this->ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive data until the server closes the connection
    do {
        this->iResult = recv(this->ConnectSocket, recvbuf, recvbuflen, 0);
        if (this->iResult > 0)
            printf("Network Client: Bytes received: %d\n", iResult);
        else if (this->iResult == 0)
            printf("Network Client: Connection closed\n");
        else
            printf("Network Client: recv failed: %d\n", WSAGetLastError());
    } while (this->iResult > 0);

    return 0;
}

int Network_client::disconnect_client() {
    // shutdown the send half of the connection since no more data will be sent
    this->iResult = shutdown(this->ConnectSocket, SD_SEND);
    if (this->iResult == SOCKET_ERROR) {
        printf("Network Client: Shutdown failed: %d\n", WSAGetLastError());
        closesocket(this->ConnectSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(this->ConnectSocket);
    WSACleanup();

    return 0;

}
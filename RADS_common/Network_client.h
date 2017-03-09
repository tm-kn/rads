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

///
/// <summary>Wrapper around winsocks for the client-side.</summary>
///
class Network_client
{
public:
    Network_client();
    
    ~Network_client();

    ///
    /// <summary>Establish client connection so it's ready to ivoke <see cref="send_data" />.</summary>
    /// <returns>Returns 0 if connection has been established. Returns 1 if it is not possible to establish the connection.</returns>
    ///
    int establish_client_connection();

    ///
    /// <summary>Send message to the server.</summary>
    /// <param name="message">Pointer to char array with message to send over the network.</param>
    /// <param name="message_size">Size of the array that is about to be sent.</param>
    /// <returns>Number of bytes that has been sent.</returns>
    ///
    int send_data(char * message, int message_size);
    
    ///
    /// <summary>Close the socket.</summary>
    /// <returns>Returns 0 if it was successful, 1 otherwise.</returns>
    ///
    int disconnect_client();
private:
    ///
    /// <summary>Pointer required to be shared within the class for the sake of winsockets implementation.</summary>
    ///
    addrinfo *ptr;

    ///
    /// <summary>Pointer required to be shared within the class for the sake of winsockets implementation.</summary>
    ///
    addrinfo *result;

    ///
    /// <summary>Result of the winsocks operation.</summary>
    ///
    int iResult;

    ///
    /// <summary>Socket used to connecting to the server.</summary>
    ///
    SOCKET ConnectSocket;

    ///
    /// <summary>Create client socket.</summary>
    /// <returns>0 if successful, 1 otherwise.</returns>
    ///
    int create_client_socket();
};


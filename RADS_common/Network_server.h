#pragma once

#include <map>
#include <vector>
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
using std::vector;
using std::pair;

///
/// <summary>Winsocks wrapper for the connection on the server-side.</summary>
///
class Network_server
{
public:
    Network_server();

    ~Network_server();

    ///
    /// <summary>Establish server communication so it's ready to accept clients.</summary>
    /// <returns>0 if successful, otherwise it returns 1.</returns>
    ///
    int establish_server_communication();

    ///
    /// <summary>Accept connections from the server. Required <see cref="establish_server_communication" /> to be successfuly performed first.</summary>
    /// <example>
    /// To be used in the server loop.
    /// <code>
    /// Network_server * network_server = new Network_server();
    /// if (network_server->establish_connection() == 0)
    ///     // Connection successful
    ///     while(true) {
    ///         this->accept_connections();
    ///         // Sleep for a second.
    ///     }
    /// }
    /// </code>
    /// </example>
    void accept_connections();

    ///
    /// <summary>Receive data and convert it to <see cref="Packet" /> instances.</summary>
    /// <param name="cls">Instance of class which member method will be called as a callback.</param>
    /// <param name="callback">Class method that will be called as callback. It needs to take vector of <see cref="Packet" /> instances as its parameter.</param>
    /// <returns>0 if successful.</returns>
    /// <example>
    /// Example callback can look like the following code.
    /// <code>
    /// void Controller::process_packets(vector<Packet> packets) {
    ///     // Do something with received packets.
    /// }
    /// </code>
    /// An example way of calling the <see cref="receive_data" /> may be as follows.
    /// <code>
    /// void Controller::start_receiving_data() {
    ///     Network_server * network_server = network_server;
    ///     network_server->receive_data(*this, &Controller::process_packets);
    /// }
    /// </example>
    ///
    ///
    template <class T> int receive_data(T & cls, void (T::*callback)(vector<Packet>));
private:
    ///
    /// <summary>Socket used to listen on connections comming from the clients.</summary>
    ///
    SOCKET ListenSocket;

    ///
    /// <summary>Pointer required to share data between class methods, for the sake of winsocks implementation.</summary>
    ///
    addrinfo *result;

    ///
    /// <summary>Result of winsocks operation, for the sake of winsocks implementation.</summary>
    ///
    int iResult;

    ///
    /// <summary>Chracters array used to store incoming data from the clients.</summary>
    ///
    char network_data[MAX_PACKET_SIZE];

    ///
    /// <summary>Map of sessions with the server. Contains client_id (integer) and separate socket for each of the clients.</summary>
    ///
    map<unsigned int, SOCKET> sessions;

    ///
    /// <summary>Client ID assigned to new clients.</summary>
    ///
    unsigned int client_id;

    ///
    /// <summary>Accept connection from particular client ID.</summary>
    /// <param name="id">Client ID</param>
    ///
    int accept_connection(unsigned int id);

    ///
    /// <summary>Create socket for oncoming connections.</summary>
    /// <returns>0 if successful.</returns>
    ///
    int create_socket();

    ///
    /// <summary>Bind socket so can be used for listening to oncoming connections.</summary>
    /// <returns>0 if successful.</returns>
    ///
    int bind_socket();

    ///
    /// <summary>Listen for oncoming connection.</summary>
    /// <returns>0 if sucessful.</returns>
    ///
    int listen_on_socket();

    ///
    /// <summary>Receive data from particular client's socket.</summary>
    /// <param name="client_id">Client ID which socket will be received data from.</param>
    /// <param name="recvbuf">Pointer to char array where to save incoming data to.</param>
    /// <returns>0 if successful.</returns>
    ///
    int receive_data_from_client(unsigned int client_id, char* recvbuf);
};

// Need to include this method here since it's a template.
// The compiler won't evaluate it properly in cpp file.
template<class T> int Network_server::receive_data(T & cls, void (T::*callback)(vector<Packet>)) {
    bool new_data_received = false;
    Packet packet;
    vector<Packet> packets;

    // go through all clients using an iterator
    for (pair<unsigned int, SOCKET> session_pair : this->sessions) {
        int data_length = this->receive_data_from_client(session_pair.first, this->network_data);

        if (data_length <= 0)
        {
            //no data recieved
            continue;
        }

        new_data_received = true;

        int i = 0;
        while (i < (unsigned int)data_length)
        {
            packet.deserialize(&(this->network_data[i]));
            i += sizeof(Packet);

            //switch based on packet type
            switch (packet.packet_type) {

            case INIT_CONNECTION:
                cout << "Network server: Received init packet from client " << session_pair.first << " of ID " << packet.sender_id << endl;
                break;

            case DATA_EVENT:
                cout << "Network server: Received packet from client " << session_pair.first << endl;
                cout << "Network server: [" << packet.sender_id << "][" << packet.datetime << "][" << packet.data_type << "]" << packet.data << endl << endl;
                packets.push_back(packet);
                break;

            default:
                cout << "Network server: error in packet types" << endl;
                break;
            }
        }
    }

    if (new_data_received) {
        (cls.*callback)(packets);
        return 0;
    }

    return 1;
}
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

class Network_server
{
public:
    Network_server();
    ~Network_server();
    int etablish_server_communication();
    void accept_connections();
    template <class T> int receive_data(T & cls, void (T::*callback)(vector<Packet>));
private:
    SOCKET ClientSocket;
    SOCKET ListenSocket;
    addrinfo *result;
    int iResult;
    map<unsigned int, SOCKET> sessions;
    unsigned int client_id;
    int accept_connection(unsigned int id);
    int create_socket();
    int bind_socket();
    int listen_on_socket();
    int receive_data_from_client(unsigned int client_id, char* recvbuf);
    char network_data[MAX_PACKET_SIZE];
};

// Need to include this method here since it's a template
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
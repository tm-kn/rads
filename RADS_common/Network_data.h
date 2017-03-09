#pragma once
#include <ctime>
#include <cstring>
#define MAX_PACKET_SIZE 1000000

using std::time_t;
using std::string;

///
/// <summary>Enumerable containing possible packet types.</summary>
///
enum Packet_type {
    ///
    /// <summary>Packet initiating the transmission.</summary>
    ///
    INIT_CONNECTION = 0,

    ///
    /// <summary>Packet containing data.</summary>
    ///
    DATA_EVENT = 1,
};

///
/// <summary>Structure of the packet.</summary>
///
struct Packet {
    ///
    /// <summary>Packet type - use <see cref="Packet_type" /> enumerable.</summary>
    ///
    unsigned int packet_type;

    ///
    /// <summary>Sender identifier.</summary>
    ///
    char sender_id[50];

    ///
    /// <summary>Data type sent in the packet, e.g. sensor reading type.</summary>
    ///
    unsigned int data_type;

    ///
    /// <summary>Data that is being sent over.</summary>
    ///
    char data[100];

    ///
    /// <summary>Time of the event, e.g. sensor reading.</summary>
    ///
    time_t datetime;
   
    ///
    /// <summary>Serialize bytes to Packet instance.</summary>
    ///
    void serialize(char * data) {
        memcpy(data, this, sizeof(Packet));
    }

    ///
    /// <summary>Deerialize Packet to bytes.</summary>
    ///
    void deserialize(char * data) {
        memcpy(this, data, sizeof(Packet));
    }
};
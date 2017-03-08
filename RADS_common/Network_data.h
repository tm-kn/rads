#pragma once
#include <ctime>
#include <cstring>
#define MAX_PACKET_SIZE 1000000

using std::time_t;
using std::string;

enum PacketTypes {
    INIT_CONNECTION = 0,
    DATA_EVENT = 1,
};


struct Packet {

    unsigned int packet_type;
    char sender_id[50];
    unsigned int data_type;
    char data[100];
    time_t datetime;
   

    void serialize(char * data) {
        memcpy(data, this, sizeof(Packet));
    }

    void deserialize(char * data) {
        memcpy(this, data, sizeof(Packet));
    }
};
#include <string.h>
#include <iostream>

#include "Sending_state.h"

using std::cout;
using std::endl;

namespace RADS_client {
    namespace State {
        Sending::Sending()
        {
        }


        Sending::~Sending()
        {
        }

        void Sending::perform() {
            cout << "Client Controller: Start sending" << endl;

            this->client = this->get_client_controller()->get_network_client();
            
            if (this->send_init_connection_packet() != 0) {
                cout << "Client Controller: Failed to send INIT_CONNETION packet" << endl;
            }
            else {
                if (this->send_reading_data() != 0) {
                    cout << "Client Controller: Error occured while sending reading data" << endl;
                }
                else {
                    cout << "Client Controller: Sent reading data" << endl;
                }
            }

            this->client->disconnect_client();

            cout << "Client Controller: Finished sending" << endl;
        }

        int Sending::send_init_connection_packet() {
            const unsigned int packet_size = sizeof(Packet);
            char packet_data[packet_size];

            Packet packet;
            packet.packet_type = INIT_CONNECTION;
            strcpy_s(packet.sender_id, sizeof packet.sender_id, this->get_client_controller()->get_id().c_str());
            packet.serialize(packet_data);

            cout << "Client controller: Sending INIT_CONNETION" << endl;
            return this->client->send_data(packet_data, packet_size);
        }

        int Sending::send_reading_data() {
            Reading_data *reading_data = this->get_client_controller()->get_reading_data();

            const unsigned int packet_size = sizeof(Packet);
            char packet_data[packet_size];

            for (Sensor * sensor : reading_data->get_data()) {
                Packet packet;
                packet.packet_type = DATA_EVENT;
                strcpy_s(packet.sender_id, sizeof packet.sender_id, this->get_client_controller()->get_id().c_str());
                packet.data_type = sensor->get_sensor_type_int();
                strcpy_s(packet.data, sizeof packet.data, sensor->get_sensor_data().c_str());
                packet.datetime = sensor->get_datetime();

                packet.serialize(packet_data);

                if (this->client->send_data(packet_data, packet_size) != 0) {
                    return 1;
                }
            }

            return 0;
        }
    }
}
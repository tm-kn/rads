#pragma once

#include <string>
#include <vector>

#include "../RADS_common/Network_client.h"
#include "../RADS_common/Reading_data.h"
#include "../RADS_common/Sensor_reader.h"

using std::string;
using std::vector;
using Readings::Reading_data;
using Readings::Sensor_reader;

namespace RADS_client {
    class Client_controller
    {
    public:
        enum Client_controller_state { READING, CONNECTING, SENDING };
        Client_controller();
        ~Client_controller();
        string get_id();
        Network_client* get_network_client();
        Reading_data* get_reading_data();
        vector<Sensor_reader*> get_sensor_readers();
        void start_communicating();
        void start_reading();
        void perform();
    private:
        string id;
        void set_state(Client_controller_state state);
        vector<Sensor_reader*> sensor_readers;
        int transmission_frequency;
        Client_controller_state current_state;
        Network_client* network_client;
    };
}

#pragma once

#include <map>
#include <vector>

#include "../RADS_common/Network_server.h"
#include "../RADS_common/Reading_data.h"
#include "Observer.h"

using std::map;
using std::vector;
using Readings::Reading_data;

namespace RADS_server {
    class Server_controller
    {
    public:
        Server_controller();
        ~Server_controller();
        void start_communication();
        void process_received_data(vector<Packet> packets);
    private:
        map<unsigned int, vector<Reading_data>> reading_data;
        vector<Observer*> observers;
        Network_server * network_server;
        void notify_observers();
        void update();
    };
}

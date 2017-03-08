#pragma once

#include <vector>

#include "../RADS_common/Network_server.h"
#include "Observer.h"

using std::vector;

namespace RADS_server {
    class Server_controller
    {
    public:
        Server_controller();
        ~Server_controller();
        void start_communication();
    private:
        vector<Observer*> observers;
        Network_server * network_server;
        void notify_observers();
        void update();
    };
}

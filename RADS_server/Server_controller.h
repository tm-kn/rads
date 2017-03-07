#pragma once

#include "../RADS_common/Network_server.h"

namespace RADS_server {
    class Server_controller
    {
    public:
        Server_controller();
        ~Server_controller();
        void start_communication();
    private:
        unsigned int client_id;
        Network_server network_server;
        void update();
    };
}
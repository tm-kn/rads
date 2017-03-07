#pragma once

#include "../RADS_common/Network_client.h"

namespace RADS_server {
    class Server_controller
    {
    public:
        Server_controller();
        ~Server_controller();
        void start_communication();
    private:
        Network_client network_client;
    };
}
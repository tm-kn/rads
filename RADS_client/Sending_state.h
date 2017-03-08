#pragma once

#include "Base_state.h"

using RADS_client::State::Base;

namespace RADS_client {
    namespace State {
        class Sending :
            public Base
        {
        public:
            Sending();
            ~Sending();
            void perform();
        private:
            Network_client* client;
            int send_init_connection_packet();
            int send_reading_data();
        };
    }
}
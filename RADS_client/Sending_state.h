#pragma once

#include "Base_state.h"

using RADS_client::State::Base;

namespace RADS_client {
    namespace State {
        ///
        /// <summary>Contains logic of the sending state of the client.</summary>
        ///
        class Sending :
            public Base
        {
        public:
            Sending();
            ~Sending();

            ///
            /// <summary>Send sensor data to the server.</summary>
            ///
            void perform();
        private:
            ///
            /// <summary>Instance of <see cref="Network_client" /> used by the state.</summary>
            ///
            Network_client* client;

            ///
            /// <summary>Send <see cref="INIT_CONNECTION" /> packet data type to the server.</summary>
            ///
            int send_init_connection_packet();

            ///
            /// <summary>Send data read from sensors to the server.</summary>
            ///
            int send_reading_data();
        };
    }
}
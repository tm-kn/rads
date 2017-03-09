#pragma once

#include "Client_controller.h"

using RADS_client::Client_controller;

namespace RADS_client {
    namespace State {

        ///
        /// <summary>Base abstract class for client states. To be used as a parent class for all the client state classes.</summary>
        ///
        class Base
        {
        public:
            Base();
            ~Base();

            ///
            /// <summary>Get pointer to related Client_controller instance.</summary>
            /// <returns>Pointer to <see cref="Client_controller" /> instance.</returns>
            ///
            Client_controller* get_client_controller();

            ///
            /// <summary>Set related <see cref="Client_controller" /> instance.</summary>
            /// <param name="client_controller">Set related <see cref="Client_controller" /> instance.</param>
            ///
            void set_client_controller(Client_controller* client_controller);

            ///
            /// <summary>Perform state's specific logic. Has to be implemented on derived classes.</summary>
            ///
            virtual void perform() = 0;
        private:

            ///
            /// <summary>Pointer to <see cref="Client_controller" /> instance.</summary>
            ///
            Client_controller* client_controller;
        };
    }
}

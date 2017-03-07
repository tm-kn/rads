#include "Client_controller.h"
#include "Base_state.h"

using RADS_client::Client_controller;

namespace RADS_client {
    namespace State {
        Base::Base()
        {
        }


        Base::~Base()
        {
        }

        Client_controller* Base::get_client_controller() {
            return this->client_controller;
        }

        void Base::set_client_controller(Client_controller* client_controller) {
            this->client_controller = client_controller;
        }
    }
}

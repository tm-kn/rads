#include "Server_controller.h"
#include "Observer.h"

namespace RADS_server {
    Observer::Observer() {}

    Observer::~Observer() {}

    void Observer::set_server_controller(Server_controller * server_controller) {
        this->server_controller = server_controller;
    }

    Server_controller * Observer::get_server_controller() {
        return this->server_controller;
    }
}
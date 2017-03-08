#pragma once

namespace RADS_server {
    class Server_controller;

    class Observer
    {
    public:
        Observer();
        ~Observer();
        void set_server_controller(Server_controller * server_controller);
        Server_controller * get_server_controller();
        virtual void update() = 0;
    private:
        Server_controller * server_controller;
    };
}

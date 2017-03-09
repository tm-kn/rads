#pragma once

// Please include Observer.h and Server_controller.h in all the files that want to use this class.

namespace RADS_server {
    // For ciruclar import problem's sake.
    class Server_controller;

    ///
    /// <summary>Base class for all the <see cref="Observer" /> derived classes.</summary>
    ///
    class Observer
    {
    public:
        Observer();
        ~Observer();

        ///
        /// <summary>Set server controller instance used by the observer's.</summary>
        /// <param name="server_controller">Pointer to <see cref="Server_controller" /> instance.</param>
        ///
        void set_server_controller(Server_controller * server_controller);

        ///
        /// <summary>Get <See cref="Server_controller" />'s instance used by the observers.</summary>
        ///
        Server_controller * get_server_controller();

        ///
        /// <summary>Update observer. Method to be implemented by the derived classes.</summary>
        ///
        virtual void update() = 0;
    private:
        ///
        /// <summary>Pointer to <see crf="Server_controller" />'s instance.</summary>
        ///
        Server_controller * server_controller;
    };
}
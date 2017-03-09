#pragma once
#include "Observer.h"

namespace RADS_server {
    ///
    /// <summary>Observer class that updates the CLI. It's an example implementation of the observer.</summary>
    ///
    class CLI_observer :
        public Observer
    {
    public:
        CLI_observer();
        ~CLI_observer();

        ///
        /// <summary>Update the CLI interface (output lines of data to the console).</summary>
        ///
        void update();
    };
}
#pragma once
#include "Observer.h"

namespace RADS_server {
    class CLI_observer :
        public Observer
    {
    public:
        void update();
        CLI_observer();
        ~CLI_observer();
    };
}
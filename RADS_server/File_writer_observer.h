#pragma once
#include "Observer.h"

namespace RADS_server {
    class File_writer_observer :
        public Observer
    {
    public:
        File_writer_observer();
        ~File_writer_observer();
        void update();
    };
}
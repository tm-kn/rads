#pragma once
#include "Base_state.h"

using RADS_client::State::Base;

namespace RADS_client {
    namespace State {
        class Reading :
            public Base
        {
        public:
            Reading();
            ~Reading();
            void perform();
        };

    }
}

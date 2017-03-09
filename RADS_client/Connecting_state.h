#pragma once

#include "Base_state.h"

namespace RADS_client {
    namespace State {
        ///
        /// <summary>Contains logic of client's connecting state.</summary>
        ///
        class Connecting :
            public Base
        {
        public:
            Connecting();
            ~Connecting();

            ///
            /// <summary>Establish connection to the server.</summary>
            ///
            void perform();
        };
    }
}

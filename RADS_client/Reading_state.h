#pragma once
#include "Base_state.h"

using RADS_client::State::Base;

namespace RADS_client {
    namespace State {
        ///
        /// <summary>Contains logic of the sensor reading state of the client.</summary>
        ///
        class Reading :
            public Base
        {
        public:
            Reading();
            ~Reading();

            ///
            /// <summary>Perform readings of sensors attached to the client.</summary>
            ///
            void perform();
        };

    }
}

#pragma once

#include "Base_state.h"

namespace RADS_client {
	namespace State {
		class Connecting :
			public Base
		{
		public:
			Connecting();
			~Connecting();
			void perform();
		};
	}
}
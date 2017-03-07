#pragma once

#include "Client_controller.h"

using RADS_client::Client_controller;

namespace RADS_client {
	namespace State {
		class Base
		{
		public:
			Base();
			~Base();
			Client_controller* get_client_controller();
			void set_client_controller(Client_controller* client_controller);
			virtual void perform() = 0;
		private:
			Client_controller* client_controller = NULL;
		};
	}
}
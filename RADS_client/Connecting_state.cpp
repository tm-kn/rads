#include <chrono>
#include <iostream>
#include <thread>

#include "Connecting_state.h"

using std::chrono::seconds;
using std::cout;
using std::endl;
using std::this_thread::sleep_for;

namespace RADS_client {
	namespace State {
		Connecting::Connecting()
		{
		}


		Connecting::~Connecting()
		{
		}

		void Connecting::perform() {
			cout << "Client controller: Start connecting" << endl;
			
			sleep_for(seconds(10));

			cout << "Client controller: Stopped connecting" << endl << endl << endl;
		}
	}
}
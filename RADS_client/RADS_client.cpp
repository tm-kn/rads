#include <iostream>

#include "Client_controller.h"

using std::cout;
using std::endl;

using RADS_client::Client_controller;

int main() {
	cout << "Remote Aeroplane Data System" << endl;

	Client_controller client_controller;

	client_controller.start_reading();

	client_controller.stop_reading();

	while (true);
}
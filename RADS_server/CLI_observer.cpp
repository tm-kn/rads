#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../RADS_common/Reading_data.h"
#include "CLI_observer.h"
#include "Server_controller.h"

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;
using Readings::Reading_data;

namespace RADS_server {
    void CLI_observer::update()
    {
        cout << endl << endl << ">>>>>>>>>>>>>>>>>>>> Beggining of CLI Observer Update" << endl << endl;

        for (pair<string, vector<Reading_data>> reading_pair : this->get_server_controller()->get_reading_data()) {
            cout << endl << "\tSender ID: " << reading_pair.first << endl;

            for (Reading_data data : reading_pair.second) {
                cout << endl << "\t\tReading from " << data.get_reading_start_datetime() << " to " << data.get_reading_end_datetime() << endl << endl;

                for (Sensor * sensor : data.get_data()) {
                    cout << "\t\t\t[" << sensor->get_datetime() << "]" << sensor->to_string() << endl;
                }
            }

            cout << endl << "\tEnd of Sender ID: " << reading_pair.first << endl;
        }

        cout << endl << endl << "<<<<<<<<<<<<<<<<<<<< End of CLI Observer Update" << endl << endl;

    }

    CLI_observer::CLI_observer()
    {
    }


    CLI_observer::~CLI_observer()
    {
    }
}
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../RADS_common/Reading_data.h"
#include "File_writer_observer.h"
#include "Server_controller.h"

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

using Readings::Reading_data;

namespace RADS_server {
    File_writer_observer::File_writer_observer()
    {
    }


    File_writer_observer::~File_writer_observer()
    {
    }
    
    void File_writer_observer::update() {
        cout << endl << endl << "File Writer Observer: Writing to a file..." << endl << endl;

        for (pair<string, vector<Reading_data>> reading_pair : this->get_server_controller()->get_reading_data()) {
            // TODO: Create sender folder if it does not exist
            for (Reading_data data : reading_pair.second) {
                // TODO: Find readings that have no files in that folder and then create one

                //if (file_does_not_exist)
                    for (Sensor * sensor : data.get_data()) {
                        // TODO: Save readings in that file if file did not exist
                    }
                //}   
            }
        }

        cout << endl << endl << "File Writer Observer: Finished writing to the file." << endl << endl;
    }
}
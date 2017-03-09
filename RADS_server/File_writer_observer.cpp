#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Otherwise it will fail since we need winsocks later on
#define _WINSOCKAPI_
#include <windows.h>
#include <wchar.h>
#include <KnownFolders.h>
#include <shlobj.h>

#include "../RADS_common/Reading_data.h"
#include "File_writer_observer.h"
#include "Server_controller.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::pair;
using std::string;
using std::vector;
using std::ostringstream;
using std::wstring;
using std::wcout;

using Readings::Reading_data;

namespace RADS_server {
    File_writer_observer::File_writer_observer() {
        // Create or make sure that directory for the logs exists.
        this->create_rads_directory();
    }

    File_writer_observer::~File_writer_observer() {}

    void File_writer_observer::create_rads_directory() {
        // Get my documents path
        string directory = "";
        PWSTR path;
        HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &path);

        if (SUCCEEDED(hr)) {
            // Convert path to string (Might break if it contains Unicode characters).
            wstring ws(path);
            string ws_string(ws.begin(), ws.end());

            // Add RADS to the path
            ostringstream ss;
            ss << ws_string << "\\RADS";
            directory = ss.str();

            // Create or open RADS directory
            if (CreateDirectory(directory.c_str(), NULL) ||
                ERROR_ALREADY_EXISTS == GetLastError())
            {
                cout << "File writer observer: Using directory at " << directory << endl;
            }
            else
            {
                cout << "File writer observer: Not able to use " << directory << endl;
            }
        }

        CoTaskMemFree(path);

        this->root_path = directory;
    }

    string File_writer_observer::get_sender_directory(string sender_id) {
        ostringstream ss;
        ss << this->root_path << "\\" << sender_id;
        string sender_directory = ss.str();

        if (CreateDirectory(sender_directory.c_str(), NULL) ||
            ERROR_ALREADY_EXISTS == GetLastError())
        {
            return sender_directory;
        }
        else
        {
            cout << "File writer observer: Not able to use " << sender_directory << endl;
            return NULL;
        }
    }

    void File_writer_observer::update() {
        if (this->root_path.empty()) {
            cout << endl << endl << "File writer observer: File writer is switched off because could not create/open the directory." << endl << endl;
            return;
        }

        cout << endl << endl << "File Writer Observer: Writing to a file..." << endl << endl;

        for (pair<string, vector<Reading_data>> reading_pair : this->get_server_controller()->get_reading_data()) {
            // Add \\* to the sender directory.
            string sender_directory = this->get_sender_directory(reading_pair.first);
            ostringstream ss;
            ss << sender_directory << "\\*";
            sender_directory = ss.str();

            for (Reading_data data : reading_pair.second) {
                // Generate file name - {START_DATETIME}-{END_DATETIME}.log
                ostringstream reading_data_filename_s;
                reading_data_filename_s << data.get_reading_start_datetime() << "-" << data.get_reading_end_datetime() << ".log";

                // Find file for the particular reading.
                WIN32_FIND_DATAA find_data;
                HANDLE hFind;
                hFind = FindFirstFileA(sender_directory.c_str(), &find_data);

                // If the directory was found and everything went fine.
                if (hFind != INVALID_HANDLE_VALUE) {
                    bool found = false;

                    // Go through all the files in that directory.
                    do {
                        // Save filename to the string.
                        ostringstream filename_s;
                        filename_s << find_data.cFileName;

                        // Leave the loop and mark as found if the file for the current reading exists.
                        if (filename_s.str() == reading_data_filename_s.str()) {
                            found = true;
                            break;
                        }
                    } while (FindNextFile(hFind, &find_data));
                    FindClose(hFind);

                    // If file not found.
                    if (found == false) {
                        // Absolute path to the log file, e.g. C:\Users\User\Documents\12331132-321321132.log
                        ostringstream filepath_s;
                        filepath_s << sender_directory.substr(0, sender_directory.length() - 1) << reading_data_filename_s.str();

                        cout << "File writer observer: Creating file at " << filepath_s.str() << endl;

                        // Write to the file.
                        ofstream outfile;
                        outfile.open(filepath_s.str(), std::ios::out);

                        for (Sensor * sensor : data.get_data()) {
                            outfile << sensor->get_datetime() << "," << sensor->get_sensor_type_int() << "," << sensor->get_sensor_data() << endl;
                        }

                        outfile.close();
                    }
                }
            }
        }

        cout << endl << endl << "File Writer Observer: Finished writing to the file." << endl << endl;
    }
}

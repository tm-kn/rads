#pragma once

#include <map>
#include <string>
#include <vector>

#include "../RADS_common/Network_server.h"
#include "../RADS_common/Reading_data.h"

using std::map;
using std::string;
using std::vector;
using Readings::Reading_data;

// Please include Observer.h and Server_controller.h in all the files that want to use this class.

namespace RADS_server {
    // For cicular import sake.
    class Observer;

    class Server_controller
    {
    public:
        Server_controller();
        ~Server_controller();
        map<string, vector<Reading_data>> get_reading_data();
        map<string, time_t> get_last_reading_datetimes();
        void start_communication();
        void process_received_data(vector<Packet> packets);
    private:
        map<string, vector<Reading_data>> reading_data;
        vector<Observer*> observers;
        Network_server * network_server;
        map<string, time_t> last_reading_datetimes;
        void check_last_reading_datetimes();
        void notify_observers();
        void add_to_reading_data(string, Reading_data reading_data);
        void add_observer(Observer * observer);
        void update();
    };
}

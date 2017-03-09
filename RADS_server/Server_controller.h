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

    ///
    /// <summary>Manages server's business logic.</summary>
    ///
    class Server_controller
    {
    public:
        ///
        /// <summary>Instantiate the class.</summary>
        /// <param name="ip">IP address of the server.</param>
        /// <param name="port">Port number of the server.</param>
        /// <param name="observers">List of attached observers.</param>
        ///
        Server_controller(string ip, int port, vector<Observer*> observers);

        ~Server_controller();
        
        ///
        /// <summary>Get list of data for each of the clients.</summary>
        /// <returns>
        /// <see cref="map" /> of sender IDs that have <see cref="vector" /> of <see cref="Reading_data" /> assigned to them.
        /// </returns>
        ///
        map<string, vector<Reading_data>> get_reading_data();

        ///
        /// <summary>Get time of the last reading for each of the clients</summary>
        ///
        map<string, time_t> get_last_reading_datetimes();

        ///
        /// <summary>Start communicating.</summary>
        ///
        void start_communication();

        ///
        /// <summary>Callback for processing received data.</summary>
        /// <param name="packet"><see cref="vector" /> of <see cref="Packet" /> instances.</param>
        ///
        void process_received_data(vector<Packet> packets);
    private:
        ///
        /// <summary><see cref="map" /> containing reading data for each of the senders.</summary>
        ///
        map<string, vector<Reading_data>> reading_data;

        ///
        /// <summary><see cref="vector" /> of pointers to instances of classes derived from <see cref="Observer" />.</summary>
        ///
        vector<Observer*> observers;

        ///
        /// <summary>Pointer to <see cref="Network_server" /> instance used by the controller to manage networking.</summary>
        ///
        Network_server * network_server;

        ///
        /// <summary>Map containing last reading time for each of the clients.</summary>
        ///
        map<string, time_t> last_reading_datetimes;

        ///
        /// <summary>IP address of the server.</summary>
        ///
        string ip;

        ///
        /// <summary>Port number of the server.</summary>
        ///
        int port;

        ///
        /// <summary>Process last reading datetimes and raise alarm when approriate.</summary>
        ///
        void check_last_reading_datetimes();

        ///
        /// <summary>Notify attached observers about new data comming in.</summary>
        ///
        void notify_observers();

        ///
        /// <summary>Add new data to the reading data.</summary>
        /// <param name="sender_id">Sender ID</param>
        /// <param name="reading_data"><see cref"Reading_data" /> object.</param>
        ///
        void add_to_reading_data(string sender_id, Reading_data reading_data);

        ///
        /// <summary>Attach a new observer to the controller.</summary>
        /// <param name="observer">Pointer to instance of a class dervied from <see cref="Observer" />.</param>
        void add_observer(Observer * observer);

        ///
        /// <summary>Contains logic that is called on each iteration of the server loop.</summary>
        ///
        void update();
    };
}

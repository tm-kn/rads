#pragma once

#include <ctime>
#include <string>
#include <vector>

#include "../RADS_common/Network_client.h"
#include "../RADS_common/Reading_data.h"
#include "../RADS_common/Sensor_reader.h"

using std::string;
using std::time_t;

using std::vector;
using Readings::Reading_data;
using Readings::Sensor_reader;

///
/// <summary>Represents the client state.</summary>
///
enum Client_controller_state {
    ///
    /// <summary>Represents state of reading the sensors.</summary>
    ///
    READING,

    ///
    /// <summary>Represents state of connecting to the server.</summary>
    ///
    CONNECTING,

    ///
    /// <summary>Represents state of sending the data to the server.</summary>
    ///
    SENDING
};

namespace RADS_client {
    ///
    /// <summary>Manages all client's business logic.</summary>
    ///
    class Client_controller
    {
    public:
        ///
        /// <summary>Instantiate the class.</summary>
        ///
        Client_controller(string id, vector<Sensor_reader*> sensor_readers,
            int transmission_frequency, int data_hourly_limit, string ip, int port);

        ~Client_controller();

        ///
        /// <summary>Get client's identifier.</summary>
        /// <returns>String with the identifier.</returns>
        ///
        string get_id();

        ///
        /// <summary>Get related <see cref="Network_client" /> instance.</summary>
        /// <returns>Pointer to <see cref="Network_client" />.</returns>
        ///
        Network_client* get_network_client();

        ///
        /// <summary>Get currently read data.</summary>
        /// <returns>Pointer to <see cref="Reading_data" /> instance.</returns>
        ///
        Reading_data* get_reading_data();

        ///
        /// <summary>Get list of sensor readers attached to the client.</summary>
        /// <returns>Vector of pointers to classes dervied from <see cref="Sensor_reader" />.</returns>
        ///
        vector<Sensor_reader*> get_sensor_readers();

        ///
        /// <summary>Add number of bytes to currently set data to manage the data limiter.</summary>
        /// <param name="bytes">Number of bytes.</param>
        ///
        void add_bytes_sent(int bytes);

        ///
        /// <summary>Start communicating state in order to establish connection to the server.</summary>
        ///
        void start_communicating();

        ///
        /// <summary>Clean up data stored on the sensor readers.</summary>
        ///
        void clean_sensor_readers();

        ///
        /// <summary>Start reading sensors state in order to make sensors start reading.</summary>
        ///
        void start_reading();
    private:
        ///
        /// <summary>Number of bytes sent.</summary>
        ///
        int data_sent_bytes;

        ///
        /// <summary>Number of bytes that can be transfered within an hour.</summary>
        ///
        int data_hourly_limit;

        ///
        /// <summary>Time when the current data limited period started.</summary>
        ///
        time_t data_period_start_datetime;
        
        ///
        /// <summary>Client's identifier that is sent together with all the data.</summary>
        ///
        string id;

        ///
        /// <summary>IP address.</summary>
        ///
        string ip;

        ///
        /// <summary>Port number.</summary>
        ///
        int port;
        
        ///
        /// <summary>Number of seconds that determine how often client is able transmit data to the server.</summary>
        ///
        long int transmission_frequency;

        ///
        /// <summary>Time when the last transmission took place.</summary>
        ///
        time_t last_transmission;

        ///
        /// <summary>Perform logic of the current state.</summary>
        ///
        void perform();

        ///
        /// <summary>Set client's controller state.</summary>
        /// <example>After client's controller state has been set, you can call <see cref="perform" /> to execute its logic.</example>
        /// <param name="state">Current state. Needs to conform with <see cref="Client_controller_state" /> enumerable.</param>
        ///
        void set_state(Client_controller_state state);

        ///
        /// <summary>List of attached sensor readers.</summary>
        ///
        vector<Sensor_reader*> sensor_readers;

        ///
        /// <summary>State that the client is currently in.</summary>
        ///
        Client_controller_state current_state;
        
        ///
        /// <summary>Pointer to <see cref="Network_client" /> used by the client.</summary>
        ///
        Network_client* network_client;

        ///
        /// <summary>Check if data limits has already been reached or reset the throotling if the limited period ended.</summary>
        /// <returns>Returns 0 when client may transmit, 1 otherwise.</returns>
        ///
        int check_data_limitation();
    };
}

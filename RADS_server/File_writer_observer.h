#pragma once
#include "Observer.h"

namespace RADS_server {
    ///
    /// <summary>Writing new data to the files.</summary>
    /// <example>Stores data in structure of: {SENDER_ID}/{READING_START_DATETIME}-{READING_END_DATETIME}.log.</example>
    ///
    class File_writer_observer :
        public Observer
    {
    public:
        File_writer_observer();

        ~File_writer_observer();

        ///
        /// <summary>Write new data to the files.</summary>
        ///
        void update();
    private:
        ///
        /// <summary>
        /// Get path to the directory (create if it does not exist) where logs for a particular sender are stored.
        /// </summary>
        ///
        string get_sender_directory(string sender_id);

        ///
        /// <summary>Make sure directory "RADS" exists in "Documents".</summary>
        ///
        void create_rads_directory();

        ///
        /// <summary>Root path to the "RADS" directory.</summary>
        ///
        string root_path;
    };
}

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
    };
}
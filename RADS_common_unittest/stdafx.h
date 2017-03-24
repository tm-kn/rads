// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Headers for CppUnitTest
#include "CppUnitTest.h"

// TODO: reference additional headers your program requires here

#include <wchar.h>
#include "../RADS_common/Sensor.h"
using std::wstring;

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework
        {
            template<> static wstring ToString<Sensor_type>(const Sensor_type& sensor_type)
            {
                switch (sensor_type) {
                case GPS_POSITION_SENSOR:
                    return L"GPS";
                    break;
                case FUEL_LEVEL_SENSOR:
                    return L"FUEL";
                    break;
                case SPEED_SENSOR:
                    return L"SPEED";
                    break;
                case TEMPERATURE_SENSOR:
                    return L"TEMPERATURE";
                    break;
                default:
                    return L"UNKNOWN";
                };
            };
        }
    }
}
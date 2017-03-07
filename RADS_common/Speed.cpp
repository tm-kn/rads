#include <sstream>
#include <string>

#include "Speed.h"

using std::ostringstream;
using std::string;

namespace Readings {
    namespace Speed {
        Speed::Speed(float speed)
        {
            this->speed = speed;
        }


        Speed::~Speed()
        {
        }

        string Speed::to_string() {
            ostringstream stringStream;
            stringStream << "SPEED " << this->speed;
            return stringStream.str();
        }
    }
}

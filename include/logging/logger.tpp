
#include <sstream>

namespace logging {

template<typename T>
Logger& Logger::operator<<(const T input) {
    std::stringstream stream;
    stream << input;
    this->log(stream.str(), stream_level);
    return *this;
}

}

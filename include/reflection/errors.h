#pragma once

#include <stdexcept>

namespace reflect {

class reflection_error : public std::runtime_error {
protected:
    explicit reflection_error(const std::string &msg);
};

class invalid_size : public reflection_error {
public:
    explicit invalid_size(const std::string &msg);
};

class invalid_type : public reflection_error {
public:
    explicit invalid_type(const std::string &msg);
};

}

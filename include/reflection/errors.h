#pragma once

#include <stdexcept>

namespace reflect {

class reflection_error : public std::runtime_error {
protected:
    explicit reflection_error(const std::string& msg);
};

class invalid_size : public reflection_error {
public:
    explicit invalid_size(const std::string& msg);
};

class invalid_type : public reflection_error {
public:
    explicit invalid_type(const std::string& msg);
};

class invalid_instance : public reflection_error {
public:
    explicit invalid_instance(const std::string& msg);
};

class already_reflected : public reflection_error {
public:
    explicit already_reflected(const std::string& msg);
};

class variant_error : public reflection_error {
public:
    explicit variant_error(const std::string& msg);
};

}

#pragma once

#include <string>
#include <map>

#define FORMAT_HANDLER(type, name, size) __Handlers::handlers[type] = &name;\
    __Handlers::size[type] = size;

typedef std::string(*format_handler)(std::string, const void*);

class Formattable {
public:
    virtual std::string __format__(std::string spec) = 0;
};

class format_error : public std::runtime_error {
public:
    explicit format_error(const std::string &msg);
};

struct __Handlers {
    static std::map<char, format_handler> handlers;
    static std::map<char, char> size;
};

std::string format(const std::string& pattern, ...);

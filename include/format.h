#pragma once

#include <string>
#include <map>

// TODO: Make this in the util space?

typedef std::string(*format_handler)(std::string, const void*);

class Formattable {
public:
    virtual void __is_formattable__() const;
    virtual std::string __format__(std::string spec) const = 0;
};

class format_error : public std::runtime_error {
public:
    explicit format_error(const std::string &msg);
};

struct __Handlers {
    static std::map<char, format_handler> handlers;
    static std::map<char, size_t> size;
};

bool add_format_handler(char spec, format_handler handler, size_t size);

bool remove_format_handler(char spec);

std::string format(std::string pattern, ...);

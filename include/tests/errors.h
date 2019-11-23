#pragma once

#include <system_error>
#include <string>

namespace testing {

class test_error : public std::runtime_error {
protected:
    explicit test_error(const std::string& msg);
};

class assertion_failure : public test_error {
public:
    explicit assertion_failure(const std::string& msg);
};

class skip_test : public test_error {
public:
    skip_test();
    explicit skip_test(const std::string& msg);
};

}
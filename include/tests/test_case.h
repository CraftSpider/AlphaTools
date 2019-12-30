#pragma once

#include <string>
#include "utils/sfinae.h"

/**
 * \file test_case.h
 * \brief Internal systems for test cases
 */

namespace testing {

class TestCase {
protected:
    std::string name;
public:
    virtual ~TestCase() = default;
    virtual void run() = 0;
    std::string get_name();
};

template<typename T>
class __TestCase : public TestCase {
    
    T instance;

public:
    
    __TestCase(T inst, const std::string& name);
    ~__TestCase() override;
    
    template<typename C, std::enable_if_t<util::TypeFinder<C>::function, int> = 0>
    void __run();
    
    template<typename C, std::enable_if_t<util::TypeFinder<C>::pointer, int> = 0>
    void __run();
    
    template<typename C, std::enable_if_t<util::TypeFinder<C>::method, int> = 0>
    void __run();
    
    void run() override;
    
};

}

#include "test_case.tpp"

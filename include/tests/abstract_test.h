#pragma once

#include <string>

/**
 * \file abstract_test.h
 * \brief Abstracts for test classes to implement
 */

namespace testing {

/**
 * \brief Superclass for automated test handling
 *
 * A class that contains tests and any necessary boilerplate.
 * To delegate test methods, use the `TEST_METHOD(name)` macro
 * in the run() method definition.
 */
class AbstractTest {

public:
    
    bool delegated = false;
    
    virtual ~AbstractTest();
    
    virtual bool skip_class();
    virtual bool skip_test(std::string name);
    
    virtual void before_class();
    virtual void before_test(std::string name);
    virtual void run() = 0;
    virtual void after_test(std::string name);
    virtual void after_class();
};

}

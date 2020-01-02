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
    
    /**
     * Destructor for AbstractTest is virtual as it's an abstract class
     */
    virtual ~AbstractTest();
    
    /**
     * Whether to skip testing this whole class
     * \return Whether class testing is skipped
     */
    virtual bool skip_class();
    
    /**
     * Whether to skip testing a single test, given the name of the test
     * \param name Name of the next test to run
     * \return Whether to skip that test
     */
    virtual bool skip_test(std::string name);
    
    /**
     * Invoked before the entire class is tested, if the class isn't being skipped
     */
    virtual void before_class();
    
    /**
     * Invoked once before each test is run, given the name of the test
     * \param name Name of the next test to run
     */
    virtual void before_test(std::string name);
    
    /**
     * Function to override to implement the actual testing
     */
    virtual void run() = 0;
    
    /**
     * Invoked once after each test is run, given the name of the test
     * \param name Name of the next test to run
     */
    virtual void after_test(std::string name);
    
    /**
     * Invoked after the entire class is tested, if the class isn't being skipped
     */
    virtual void after_class();
};

}

#pragma once

#include <string>
#include "utils/sfinae.h"

/**
 * \file test_case.h
 * \brief Internal systems for test cases
 */

namespace testing {

/**
 * Abstract class representing a test to be run by the test system. Can be subclassed for extensions
 */
class TestCase {
protected:
    std::string name;
public:
    
    /**
     * Virtual destructor as this is an abstract class
     */
    virtual ~TestCase() = default;
    
    /**
     * Run this test case, actually executing the tests and associated setup/teardown code
     */
    virtual void run() = 0;
    
    /**
     * Get the name of this test as a string
     *
     * \return Name of the test
     */
    std::string get_name();
};

/**
 * \internal
 *
 * Implementation of TestCase for the builtin test running macros. Templated to allow both functions and classes to
 * use the same macro
 *
 * \tparam T Function/Class type to test
 */
template<typename T>
class __TestCase : public TestCase {
    
    T instance;

public:
    
    /**
     * Constructor a test case from an instance of the expected type + the name of the test
     *
     * \param inst Function/Class to test
     * \param name Name of the Function/Class
     */
    __TestCase(T inst, const std::string& name);
    
    /**
     * Destruct this TestCase. Ensures that the instance is correctly deleted
     */
    ~__TestCase() override;
    
    /**
     * \internal
     *
     * Specialization of the run function for if we are testing a function
     *
     * \tparam C Function type
     */
    template<typename C, std::enable_if_t<util::TypeFinder<C>::function, int> = 0>
    void __run();
    
    /**
     * \internal
     *
     * Specialization of the run function for if we are testing a class
     *
     * \tparam C Class pointer type
     */
    template<typename C, std::enable_if_t<util::TypeFinder<C>::pointer, int> = 0>
    void __run();
    
    /**
     * \internal
     *
     * Specialization of the run function for if we are testing a method (unused)
     *
     * \tparam C Method pointer type
     */
    template<typename C, std::enable_if_t<util::TypeFinder<C>::method, int> = 0>
    void __run();
    
    void run() override;
    
};

}

#include "test_case.tpp"

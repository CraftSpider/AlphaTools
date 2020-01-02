#pragma once

#include <stdexcept>
#include <string>

/**
 * \file errors.h
 * \brief Errors for testing operations
 */

namespace testing {

/**
 * Base class for test exceptions. Doesn't inherit exception to prevent accidentally catching assertions or skips
 */
class test_exception {
    
    std::string message;
    
protected:
    
    /**
     * Construct an exception with message. Protected so only subclasses can directly construct
     *
     * \param msg Message to construct exception with
     */
    explicit test_exception(const std::string& msg);
    
public:
    
    /**
     * Get the information contained in this exception, as a const char*
     *
     * \return Message in this exception
     */
    virtual const char* what() const noexcept;
    
};

/**
 * Exception for if an assertion fails
 */
class assertion_failure : public test_exception {
public:
    
    /**
     * Construct this assertion failure with the given message
     *
     * \param msg Message for this error
     */
    explicit assertion_failure(const std::string& msg);
    
};

/**
 * Exception for if a test is skipped by throw
 */
class skip_test : public test_exception {
public:
    
    /**
     * Construct this skip with no message
     */
    skip_test();
    
    /**
     * Construct this skip with the given message
     *
     * \param msg Message for this error
     */
    explicit skip_test(const std::string& msg);
    
};

}

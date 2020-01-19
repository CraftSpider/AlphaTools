#pragma once

#include <stdexcept>

/**
 * \file errors.h
 * \brief Errors for reflection operations
 */

namespace reflect {

/**
 * Base error for all reflection errors
 */
class reflection_error : public std::runtime_error {
protected:
    
    /**
     * Construct a new reflection_error from a message
     *
     * \param msg Error message
     */
    explicit reflection_error(const std::string& msg);
    
};

/**
 * Error thrown on attempt to retrieve a type that wasn't reflected
 */
class not_reflected : public reflection_error {
public:
    
    /**
     * Construct a new not_reflected from a message
     *
     * \param msg Error message
     */
    explicit not_reflected(const std::string& msg);
    
};

/**
 * Error thrown on attempt to reflect a type / function / data that was already reflected
 */
class already_reflected : public reflection_error {
public:
    
    /**
     * Construct a new already_reflected from a message
     *
     * \param msg Error message
     */
    explicit already_reflected(const std::string& msg);
};

/**
 * Error for if a parameter list is the wrong size
 */
class invalid_size : public reflection_error {
public:
    
    /**
     * Construct a new invalid_size from a message
     *
     * \param msg Error message
     */
    explicit invalid_size(const std::string& msg);
    
};

/**
 * Error for if an invalid type is passed to or retrieved from a method
 */
class invalid_type : public reflection_error {
public:
    
    /**
     * Construct a new invalid_type from a message
     *
     * \param msg Error message
     */
    explicit invalid_type(const std::string& msg);
    
};

/**
 * Error for if an invalid cast is performed, EG dynamic_cast on unrelated types
 */
class invalid_cast : public reflection_error {
public:
    
    /**
     * Cosntruct a new invalid_cast from a message
     *
     * \param msg Error message
     */
     explicit invalid_cast(const std::string& msg);
};

/**
 * Error for if a Variant is used in an invalid situation, EG taking ownership of a shared
 * pointer or trying to destruct a Variant holding an owned pointer
 */
class variant_error : public reflection_error {
public:
    
    /**
     * Construct a new variant_error from a message
     *
     * \param msg Error message
     */
    explicit variant_error(const std::string& msg);
    
};

}

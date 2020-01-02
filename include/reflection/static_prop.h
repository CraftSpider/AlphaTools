#pragma once

#include "type.h"
#include "variant.h"

/**
 * \file static_prop.h
 * \brief Reflection support for Static Properties
 */

namespace reflect {

/**
 * Generic type all static property get functions can be cast to
 */
typedef Variant(*StaticPropertyGetFuncRef)(void*);

/**
 * Generic type all static property set functions can be cast to
 */
typedef void(*StaticPropertySetFuncRef)(void*, Variant&);

/**
 * Class to generate type-safe and well-formed static data get/set
 *
 * \tparam Ret Type of the data
 */
template<typename Ret>
class StaticPropertyMeta {
public:
    
    /**
     * Get the data from a pointer to it
     *
     * \param ptr Pointer to data type
     * \return Retrieved data value
     */
    static Variant get(Ret* ptr);
    
    /**
     * Set data at a pointer
     *
     * \param ptr Pointer to data type
     * \param data Value to set it to
     * \return void
     */
    static void set(Ret* ptr, Variant& data);
    
    /**
     * Get the get func as a common type
     *
     * \return Get func pointer
     */
    static StaticPropertyGetFuncRef get_get_func();
    
    /**
     * Get the set func as a common type
     *
     * \return Set func pointer
     */
    static StaticPropertySetFuncRef get_set_func();
    
};

/**
 * Class that wraps a static property. Can be used to get and set that data
 */
class StaticProperty final {

    Type* type;
    Type* property_type;
    std::string name;
    
    void* ptr;
    StaticPropertyGetFuncRef get_ptr;
    StaticPropertySetFuncRef set_ptr;
    
    /**
     * Constructing new instances is managed by the library and is private
     *
     * \tparam Ret Type of the data
     * \param type Type the property is defined on
     * \param ptr Pointer to the data
     * \param name Name of the data
     */
    template<typename Ret>
    StaticProperty(Type* type, Ret* ptr, std::string name);
    
    /**
     * As StaticProperties have a static lifetime, prevent external things from
     * deleting them
     */
    ~StaticProperty() = default;
    
public:
    
    /**
     * StaticProperties should never be copied, they are singleton
     */
    StaticProperty(StaticProperty&) = delete;
    
    /**
     * StaticProperties should never be moved, they are singleton
     */
    StaticProperty(StaticProperty&&) = delete;
    
    /**
     * Get the StaticProperty associated with a given pointer to data and name
     *
     * \tparam T Associated type
     * \tparam Ret Type of the data
     * \param ptr Pointer to data
     * \param name Name of the data
     * \return Associated StaticProperty instance
     */
    template<typename T, typename Ret>
    static StaticProperty& from(Ret* ptr, std::string name);
    
    /**
     * Get the value of this property
     *
     * \return Property value
     */
    Variant get();
    
    /**
     * Set the value of this property
     *
     * \param data Value to set to
     */
    void set(Variant data);
    
    /**
     * Get the Type that is associated with this StaticProperty
     *
     * \return Associated type
     */
    Type* get_type();
    
    /**
     * Get the Type of the property associated with this StaticProperty
     *
     * \return Property type
     */
    Type* get_property_type();
    
    /**
     * Get the name of this StaticProperty
     *
     * \return Property name
     */
    std::string get_name();

};

}

#include "static_prop.tpp"

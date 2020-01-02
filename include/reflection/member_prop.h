#pragma once

#include "type.h"
#include "variant.h"

/**
 * \file member_prop.h
 * \brief Reflection support for Member Properties
 */

namespace reflect {

/**
 * Generic type all member get functions can be cast to
 */
typedef Variant(*MemberPropertyGetFuncRef)(void* ptr, Variant&);

/**
 * Generic type all member set functions can be cast to
 */
typedef void(*MemberPropertySetFuncRef)(void* ptr, Variant&, Variant&);

/**
 * \internal
 *
 * Class to generate type-safe and well-formed property get/set
 *
 * \tparam T Type property is on
 * \tparam Ret Type of the property
 */
template<typename T, typename Ret>
class MemberPropertyMeta {
public:
    
    /**
     * Get the data from an insstance of the class
     *
     * \param ptr Pointer to member data pointer
     * \param instance Instance to retrieve from
     * \return Retrieved data value
     */
    static Variant get(Ret T::** ptr, Variant& instance);
    
    /**
     * Set the data on an instance of the class
     *
     * \param ptr Pointer to member data pointer
     * \param instance Instance to set data on
     * \param data Value to set data to
     * \return void
     */
    static void set(Ret T::** ptr, Variant& instance, Variant& data);
    
    /**
     * Get the get func as a common type
     *
     * \return Get func pointer
     */
    static MemberPropertyGetFuncRef get_get_func();
    
    /**
     * Get the set func as a common type
     *
     * \return Set func pointer
     */
    static MemberPropertySetFuncRef get_set_func();

};

/**
 * Class that wraps a member property. Can be used to get and set that property on instances of the type
 */
class MemberProperty final {

    Type* type;
    Type* property_type;
    std::string name;
    
    void* ptr;
    MemberPropertyGetFuncRef get_ptr;
    MemberPropertySetFuncRef set_ptr;
    
    /**
     * Constructing new instances is managed by the library and is private
     *
     * \tparam T Type of the class
     * \tparam Ret Type of the property
     * \param ptr Pointer to member data
     * \param name Name of the property
     */
    template<typename T, typename Ret>
    MemberProperty(Ret T::* ptr, std::string name);
    
    /**
     * As MemberProperties have a static lifetime, prevent external things from
     * deleting them
     */
    ~MemberProperty() = default;
    
public:
    
    /**
     * MemberProperties should never be copied, they are singleton
     */
    MemberProperty(MemberProperty&) = delete;
    
    /**
     * MemberProperties should never be moved, they are singleton
     */
    MemberProperty(MemberProperty&&) = delete;
    
    /**
     * Get the MemberProperty associated with a given pointer to member data and name
     *
     * \tparam T Type of the class
     * \tparam Ret Type of the property
     * \param ptr Pointer to member data
     * \param name Name of the property
     * \return Associated MemberProperty instance
     */
    template<typename T, typename Ret>
    static MemberProperty& from(Ret T::* ptr, std::string name);
    
    /**
     * Get the value of this property on an instance of the associated type
     *
     * \param instance Type to retrieve from
     * \return Value of the property
     */
    Variant get(Variant instance);
    
    /**
     * Set the value of this property on an instance of the associated type
     *
     * \param instance Type to set on
     * \param value Value to set property to
     */
    void set(Variant instance, Variant value);
    
    /**
     * Get the Type that is associated with this MemberProperty
     *
     * \return Type property is on
     */
    Type* get_type();
    
    /**
     * Get the Type of the property associated with this MemberProperty
     *
     * \return Property type
     */
    Type* get_property_type();
    
    /**
     * Get the name of this MemberProperty
     *
     * \return Name of the property
     */
    std::string get_name();

};

}

#include "member_prop.tpp"

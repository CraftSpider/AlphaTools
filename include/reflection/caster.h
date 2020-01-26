#pragma once

#include "type.h"
#include "variant.h"

/**
 * \file caster.h
 * \brief Reflection support for type casting
 */

namespace reflect {

/**
 * Generic type all meta cast functions can be cast to
 */
typedef Variant(*CastFuncRef)(Variant&);

/**
 * Namespaced enum for different types of casting
 */
namespace CastType {

/**
 * Enum values
 */
enum type {
    DYNAMIC,
    REINTERPRET,
    STATIC,
    CONST,
    C
};

/**
 * Convert enum value to a string name
 *
 * \param t Enum value type
 * \return Associated enum name
 */
std::string to_string(type t);

}

/**
 * \internal
 *
 * Class to generate type-safe and well formed pointer addition and removal
 *
 * \tparam T Class to shift pointer status
 */
template<typename T>
class ShifterMeta {
public:
    
    /**
     * Get a pointer to the passed variant. The returned Variant is owned
     *
     * \param obj Object to get pointer to
     * \return Pointer to passed object
     */
    static Variant add_pointer(Variant& obj);
    
    /**
     * Dereference a pointer from the passed variant. The returned Variant is not owned
     * specialization for if the type can be dereferenced
     *
     * \tparam K Class to dereference
     * \param obj Object to dereference
     * \return Object pointed to by the passed object
     */
    template<typename K>
    static std::enable_if_t<std::is_pointer_v<K>, Variant> remove_pointer(Variant& obj);
    
    /**
     * Dereference a pointer from the passed variant. The returned Variant is not owned
     * Specialization for if the type can't be dereferenced. Always throws an invalid_type error
     *
     * \tparam K Class to dereference
     * \param obj Invalid object to dereference
     * \return Nothing
     */
    template<typename K>
    static std::enable_if_t<!std::is_pointer_v<K>, Variant> remove_pointer(Variant& obj);
    
    /**
     * Get the add_pointer func as a common type
     *
     * \return Add pointer function
     */
    static CastFuncRef get_add_pointer_func();
    
    /**
     * Get the remove_pointer func as a common type
     *
     * \return Remove pointer function
     */
    static CastFuncRef get_remove_pointer_func();
    
};

/**
 * \internal
 *
 * Class for checking whether different kinds of casts are supported between two types
 *
 * \tparam From Type being cast from
 * \tparam To Type being cast to
 */
template<typename From, typename To>
class __CastSupport {
    
    template<typename T, typename K, typename = decltype(dynamic_cast<K>(std::declval<T>()))>
    static std::true_type __test_dynamic(int) {return std::true_type();}
    
    template<typename, typename>
    static std::false_type __test_dynamic(...) {return std::false_type();}
    
    template<typename T, typename K, typename = decltype(reinterpret_cast<K>(std::declval<T>()))>
    static std::true_type __test_reinterpret(int) {return std::true_type();}
    
    template<typename, typename>
    static std::false_type __test_reinterpret(...) {return std::false_type();}
    
    template<typename T, typename K, typename = decltype(static_cast<K>(std::declval<T>()))>
    static std::true_type __test_static(int) {return std::true_type();}
    
    template<typename, typename>
    static std::false_type __test_static(...) {return std::false_type();}
    
    template<typename T, typename K, typename = decltype(const_cast<K>(std::declval<T>()))>
    static std::true_type __test_const(int) {return std::true_type();}
    
    template<typename, typename>
    static std::false_type __test_const(...) {return std::false_type();}
    
    template<typename T, typename K, typename = decltype((K)(std::declval<T>()))>
    static std::true_type __test_c(int) {return std::true_type();}
    
    template<typename, typename>
    static std::false_type __test_c(...) {return std::false_type();}
    
public:
    
    /**
     * CastSupport constant enum values
     */
    enum {
        support_dynamic = std::is_same<decltype(__test_dynamic<From, To>(0)), std::true_type>::value,
        support_reinterpret = std::is_same<decltype(__test_reinterpret<From, To>(0)), std::true_type>::value,
        support_static = std::is_same<decltype(__test_static<From, To>(0)), std::true_type>::value,
        support_const = std::is_same<decltype(__test_const<From, To>(0)), std::true_type>::value,
        support_c = std::is_same<decltype(__test_c<From, To>(0)), std::true_type>::value,
    };
};

/**
 * \internal
 *
 * Class to generate type-safe and well formed casts from type A to type B
 *
 * \tparam T Type to cast from
 * \tparam K Type to cast to
 */
template<typename T, typename K>
class CasterMeta {
    
    using CastCheck = __CastSupport<T, K>;
    
public:
    
    /**
     * Perform a dynamic cast between two types, specialization for if the cast is supported
     *
     * \tparam T1 From type
     * \tparam K1 To type
     * \param obj Object to cast
     * \return Result of cast
     */
    template<typename T1, typename K1>
    static std::enable_if_t<__CastSupport<T1, K1>::support_dynamic, Variant> cast_dynamic(Variant& obj);
    
    /**
     * Perform a dynamic cast between two types, specialization for if the cast is unsupported
     *
     * \tparam T1 From type
     * \tparam K1 To type
     * \param obj Object to cast
     * \return Void variant
     */
    template<typename T1, typename K1>
    static std::enable_if_t<!__CastSupport<T1, K1>::support_dynamic, Variant> cast_dynamic(Variant& obj);
    
    /**
     * Perform a reinterpret cast between two types, specialization for if the cast is supported
     *
     * \tparam T1 From type
     * \tparam K1 To type
     * \param obj Object to cast
     * \return Result of cast
     */
    template<typename T1, typename K1>
    static std::enable_if_t<__CastSupport<T1, K1>::support_reinterpret, Variant> cast_reinterpret(Variant& obj);
    
    /**
     * Perform a reinterpret cast between two types, specialization for if the cast is unsupported
     *
     * \tparam T1 From type
     * \tparam K1 To type
     * \param obj Object to cast
     * \return Void variant
     */
    template<typename T1, typename K1>
    static std::enable_if_t<!__CastSupport<T1, K1>::support_reinterpret, Variant> cast_reinterpret(Variant& obj);
    
    /**
     * Perform a static cast between two types, specialization for if the cast is supported
     *
     * \tparam T1 From type
     * \tparam K1 To type
     * \param obj Object to cast
     * \return Result of cast
     */
    template<typename T1, typename K1>
    static std::enable_if_t<__CastSupport<T1, K1>::support_static, Variant> cast_static(Variant& obj);
    
    /**
     * Perform a static cast between two types, specialization for if the cast is unsupported
     *
     * \tparam T1 From type
     * \tparam K1 To type
     * \param obj Object to cast
     * \return Void variant
     */
    template<typename T1, typename K1>
    static std::enable_if_t<!__CastSupport<T1, K1>::support_static, Variant> cast_static(Variant& obj);
    
    /**
     * Perform a const cast between two types, specialization for if the cast is supported
     *
     * \tparam T1 From type
     * \tparam K1 To type
     * \param obj Object to cast
     * \return Result of cast
     */
    template<typename T1, typename K1>
    static std::enable_if_t<__CastSupport<T1, K1>::support_const, Variant> cast_const(Variant& obj);
    
    /**
     * Perform a const cast between two types, specialization for if the cast is unsupported
     *
     * \tparam T1 From type
     * \tparam K1 To type
     * \param obj Object to cast
     * \return Void variant
     */
    template<typename T1, typename K1>
    static std::enable_if_t<!__CastSupport<T1, K1>::support_const, Variant> cast_const(Variant& obj);
    
    /**
     * Perform a c-style cast between two types, specialization for if the cast is supported
     *
     * \tparam T1 From type
     * \tparam K1 To type
     * \param obj Object to cast
     * \return Result of cast
     */
    template<typename T1, typename K1>
    static std::enable_if_t<__CastSupport<T1, K1>::support_c, Variant> cast_c(Variant& obj);
    
    /**
     * Perform a c-style cast between two types, specialization for if the cast is unsupported
     *
     * \tparam T1 From type
     * \tparam K1 To type
     * \param obj Object to cast
     * \return Void variant
     */
    template<typename T1, typename K1>
    static std::enable_if_t<!__CastSupport<T1, K1>::support_c, Variant> cast_c(Variant& obj);
    
    /**
     * Get the cast_dynamic func as a common type
     *
     * \return Dynamic cast function
     */
    static CastFuncRef get_cast_dynamic_func();
    
    /**
     * Get the cast_reinterpret func as a common type
     *
     * \return Reinterpret cast function
     */
    static CastFuncRef get_cast_reinterpret_func();
    
    /**
     * Get the cast_static func as a common type
     *
     * \return Static cast function
     */
    static CastFuncRef get_cast_static_func();
    
    /**
     * Get the cast_const func as a common type
     *
     * \return Const cast function
     */
    static CastFuncRef get_cast_const_func();
    
    /**
     * Get the cast_c func as a common type
     *
     * \return C-style cast function
     */
    static CastFuncRef get_cast_c_func();
    
};

/**
 * Class that wraps type-casting operations. Can be used to type-cast instances of that type to another type.
 */
class TypeCaster final {
    
    CastFuncRef dynamic_ptr, reinterpret_ptr, static_ptr, const_ptr, c_ptr;
    
    Type* from_type;
    Type* to_type;
    
    /**
     * Constructing new instances is managed by the library and is private
     *
     * \tparam T Type to cast from
     * \tparam K Type to cast to
     */
    template<typename T, typename K>
    explicit TypeCaster(CasterMeta<T, K>);
    
    /**
     * As TypeCasters have a static lifetime, prevent external things from
     * deleting them
     */
    ~TypeCaster() = default;
    
public:
    
    /**
     * TypeCasters should never be copied, they are singleton
     */
    TypeCaster(TypeCaster&) = delete;
    
    /**
     * TypeCasters should never be moved, they are singleton
     */
    TypeCaster(TypeCaster&&) = delete;
    
    /**
     * Get the TypeCaster associated with a given to and from type
     *
     * \tparam T Type to cast from
     * \tparam K Type to cast to
     * \return TypeCaster instance for that set of types
     */
    template<typename T, typename K>
    static TypeCaster& from();
    
    /**
     * Perform a cast on a variant, with an optionally provided cast type to use.
     * Raises an invalid_cast error if the chosen cast type can't be used between the two types
     *
     * \param variant Object to cast
     * \param type Type of cast to perform
     * \return Result of cast
     */
    Variant cast(Variant& variant, CastType::type type = CastType::C);
    
    /**
     * Get the type this TypeCaster casts from
     *
     * \return Type cast from
     */
    Type* get_from_type();
    
    /**
     * Get the type this TypeCaster casts to
     *
     * \return Type cast to
     */
    Type* get_to_type();
    
};

/**
 * Class that wraps all forms of casting operations on a class. Can be used to perform any kind of cast,
 * including pointer referencing and dereferencing
 */
class Caster final {
    
    CastFuncRef add_ptr, remove_ptr;
    
    Type* type;
    
    std::map<Type*, TypeCaster*> registered_casts;
    
    /**
     * Constructing new instances is managed by the library and is private
     *
     * \tparam T Type to support casting
     */
    template<typename T>
    explicit Caster(ShifterMeta<T>);
    
    /**
     * As Casters have a static lifetime, prevent external things from
     * deleting them
     */
    ~Caster() = default;

public:
    
    /**
     * Casters should never be copied, they are singleton
     */
    Caster(Caster&) = delete;
    
    /**
     * Casters should never be moved, they are singleton
     */
    Caster(Caster&&) = delete;
    
    /**
     * Get the caster associated with a given type
     *
     * \tparam T Type to support casting
     * \return Caster instance for that type
     */
    template<typename T>
    static Caster& from();
    
    /**
     * \internal
     *
     * Add support for casting void this type to another type
     *
     * \tparam T Type to cast from
     * \tparam K Type to cast to
     */
    template<typename T, typename K>
    void __add_cast();
    
    /**
     * Get a pointer to an instance of this type
     *
     * \param variant Object to get pointer to
     * \return Pointer to object, as an owned variant
     */
    Variant add_pointer(Variant variant);
    
    /**
     * Get the result of dereferencing a pointer of this type
     * If the type isn't a pointer type, throws invalid_type
     *
     * \param variant Object to get the pointed value
     * \return Pointer to value, as an unowned variant
     */
    Variant remove_pointer(Variant variant);
    
    /**
     * Cast from this type to some other type. Only support types that have been registered
     * through the reflection system. If the type hasn't been registered, throws invalid_type.
     * If the cast type isn't supported, throws invalid_cast.
     *
     * \param type Type to cast to
     * \param variant Instance to cast
     * \param cast Type of casting to use
     * \return Result of casting
     */
    Variant cast(Type* type, Variant variant, CastType::type cast = CastType::C);
    
    /**
     * Get the type associated with this Caster
     *
     * \return Associated type
     */
    Type* get_type();
    
};

}

#include "caster.tpp"

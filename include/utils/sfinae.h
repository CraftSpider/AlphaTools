#pragma once

#include <type_traits>
#include "types.h"

/**
 * \file sfinae.h
 * \brief Various SFINAE utilities
 */

namespace util {

template<typename T>
struct DerefPointer;

/**
 * Class that provides compile-time determination of a type. Seperates into numeric, array, class, function, member
 * data, or member function. Pointers will be maximally de-referenced, getting the 'underlying' type
 * \tparam T Type to determine classification of
 */
template<typename T>
class TypeFinder {

    typedef const char _numeric[1];
    typedef const char _array[2];
    typedef const char _class[3];
    
    typedef const char _function[4];
    
    typedef const char _memberdata[5];
    typedef const char _memberfunc[6];
    
    template<typename C, std::enable_if_t<std::is_integral<C>::value || std::is_floating_point<C>::value, int> = 0>
    static _numeric& test() {return "";}
    
    template<typename C, std::enable_if_t<std::is_array<C>::value, int> = 0>
    static _array& test() {return "a";}

    template<typename C, std::enable_if_t<std::is_class<C>::value, int> = 0>
    static _class& test() {return "cc";}
    
    template<typename C, std::enable_if_t<std::is_function<C>::value, int> = 0>
    static _function& test() {return "fff";}
    
    template<typename C, std::enable_if_t<std::is_member_object_pointer<C>::value, int> = 0>
    static _memberdata& test() {return "mdmd";}

    template<typename C, std::enable_if_t<std::is_member_function_pointer<C>::value, int> = 0>
    static _memberfunc& test() {return "mfmfm";}
    
    static const size_t _result = sizeof(test<typename DerefPointer<typename std::remove_reference<T>::type>::type>());

public:
    
    /**
     * TypeFinder constant enum values
     */
    enum {
        numeric = _result == sizeof(_numeric),
        array = _result == sizeof(_array),
        cls = _result == sizeof(_class),
        function = _result == sizeof(_function),
        member_data = _result == sizeof(_memberdata),
        member_func = _result == sizeof(_memberfunc),
    };
    
};

/**
 * \internal
 *
 * Implementation of MakePtr, for if the type is already a pointer
 *
 * \tparam T Type to make into a pointer
 */
template<typename T, bool = std::is_pointer<T>::value>
struct __MakePtr {
    
    /**
     * Unchanged type, it's already a pointer
     */
    typedef T type;

    /**
     * Take a pointer and return it unchanged.
     *
     * \param val Reference to return
     * \return Same pointer
     */
    static T make_ptr(const T& val);
};

/**
 * \internal
 *
 * Implementation of MakePtr, for if the type is not a pointer
 *
 * \tparam T Type to make into a pointer
 */
template<typename T>
struct __MakePtr<T, false> {
    
    /**
     * Type with added pointer
     */
    typedef T* type;

    /**
     * Runtime convert a reference to the type into a pointer to that reference.
     *
     * \param val Reference to convert
     * \return Pointer to reference
     */
    static T* make_ptr(T& val);
};

/**
 * Class that converts a type into a pointer, if it's not already a pointer type
 * For example, `int` becomes `int*`, but `int*` remains `int*`.
 * Also contains a method `make_ptr` for runtime conversion.
 *
 * \tparam T Type to conditionally convert
 */
template<typename T>
struct MakePtr : public __MakePtr<T> {};

/**
 * \internal
 *
 * Implementation of DerefPointer, for if the type is not a pointer type
 *
 * \tparam T Type to deref
 * \tparam U Derefed form of T
 */
template<typename T, typename U>
struct __DerefPointer {
    
    /**
     * Fully de-referenced type
     */
    typedef T type;
    
    /**
     * How many times the type was de-referenced
     */
    static constexpr size_t depth = 0;
    
};

/**
 * \internal
 *
 * Implementation of DerefPointer, for if the type is a pointer type
 *
 * \tparam T Type to deref
 * \tparam U Derefed form of T
 */
template<typename T, typename U>
struct __DerefPointer<T, U*> {
    
    /**
     * Fully de-referenced type
     */
    typedef typename __DerefPointer<U, U>::type type;
    
    /**
     * How many times the type was de-referenced
     */
    static constexpr size_t depth = __DerefPointer<U, U>::depth + 1;
    
};

/**
 * Get the most possibly de-referenced form of a pointer. `int` stays the same, `int**` will become `int`.
 *
 * \tparam T Type to dereference
 */
template<typename T>
struct DerefPointer : public __DerefPointer<T, T> {};

/**
 * Get information about a function type. Specialization for if the type isn't a function.
 */
template<typename>
struct FunctionTraits {
    
    /**
     * FunctionTrait constant enum values
     */
    enum {
        /// Whether the type is a valid function type
        valid = 0,
        /// Whether the type is not a valid function type
        invalid = 1
    };
    
};

/**
 * Get information about a function type. Specialization for if the type is a function.
 *
 * \tparam Ret Return type of the function
 * \tparam Args Variadic pack of argument types to the function
 */
template<typename Ret, typename... Args>
struct FunctionTraits<Ret(Args...)> {
    
    /**
     * Return type of the function
     */
    typedef Ret return_type;
    
    /**
     * Non-pointer function type
     */
    typedef Ret(raw_type)(Args...);
    
    /**
     * Equivalent function pointer type
     */
    typedef Ret(*pointer_type)(Args...);
    
    /**
     * Number of arguments to this function
     */
    static constexpr size_t num_args = sizeof...(Args);
    
    /**
     * FunctionTraits constant enum values
     */
    enum {
        /// Whether the type is a valid function type
        valid = 1,
        /// Whether the type is not a valid function type
        invalid = 0
    };
    
};

/**
 * Get information about a function type. Specialization for if the type is a pointer to a function.
 *
 * \tparam Ret Return type of the function
 * \tparam Args Variadic pack of argument types to the function
 */
template<typename Ret, typename... Args>
struct FunctionTraits<Ret(*)(Args...)> {
    
    /**
     * Return type of the function
     */
    typedef Ret return_type;
    
    /**
     * Equivalent non-pointer function type
     */
    typedef Ret(raw_type)(Args...);
    
    /**
     * Function pointer type
     */
    typedef Ret(*pointer_type)(Args...);
    
    /**
     * Number of arguments to this function
     */
    static constexpr size_t num_args = sizeof...(Args);
    
    /**
     * FunctionTraits constant enum values
     */
    enum {
        /// Whether the type is a valid function type
        valid = 1,
        /// Whether the type is not a valid function type
        invalid = 0
    };
    
};

/**
 * Get information about a member data type. Specialization for if the type isn't a pointer to member data.
 */
template<typename>
struct MemberTraits {
    
    /**
     * Void type for invalid type
     */
    typedef void class_type;
    
    /**
     * MemberTraits constant enum values
     */
    enum {
        /// Whether the type is a valid member type
        valid = 0,
        /// Whether the type is not a valid member type
        invalid = 1
    };
    
};

/**
 * Get information about a member data type. Specialization for if the type is a pointer to member data.
 *
 * \tparam Val Type of the data pointed to
 * \tparam Cls Type of the containing class
 */
template<typename Val, typename Cls>
struct MemberTraits<Val Cls::*> {
    
    /**
     * Class type of the member
     */
    typedef Cls class_type;
    
    /**
     * Value type of the member
     */
    typedef Val member_type;
    
    /**
     * MemberTraits constant enum values
     */
    enum {
        /// Whether the type is a valid member type
        valid = 1,
        /// Whether the type is not a valid member type
        invalid = 0
    };
    
};

/**
 * Get information about a member function type. Specialization for if the type isn't a pointer to a member func
 */
template<typename>
struct MethodTraits {
    
    /**
     * Void type for invalid type
     */
    typedef void class_type;
    
    /**
     * MethodTraits constant enum values
     */
    enum {
        /// Whether the type is a valid method type
        valid = 0,
        /// Whether the type is not a valid method type
        invalid = 1
    };
    
};

/**
 * Get information about a member function type. Specialization for if the type is a pointer to a member func
 *
 * \tparam Ret Return type of the method
 * \tparam Cls Type of the containing class
 * \tparam Args Variadic pack of argument types to the method
 */
template<typename Ret, typename Cls, typename... Args>
struct MethodTraits<Ret(Cls::*)(Args...)> {
    
    /**
     * Return type of the method
     */
    typedef Ret return_type;
    
    /**
     * Class type of the method
     */
    typedef Cls class_type;
    
    /**
     * Number of arguments to the method
     */
    static constexpr size_t num_args = sizeof...(Args);
    
    /**
     * MethodTraits constant enum values
     */
    enum {
        /// Whether the type is a valid method type
        valid = 1,
        /// Whether the type is not a valid method type
        invalid = 0
    };
    
};

/**
 * Access to the raw data of a type as any other type/types.
 * Note that this type does not take ownership, and is only valid for the lifetime of its backing instance.
 *
 * \tparam T Type to access raw data of
 */
template<typename T>
class RawData {
    
    uchar* data;
    
public:
    
    static constexpr size_t size = sizeof(T);
    
    /**
     * Construct this RawData from a pointer to an instance
     *
     * \param obj Object to access the raw data of
     */
    explicit RawData(T& obj);
    
    /**
     * Construct this RawData from a reference to an instance
     *
     * \param obj Object to access the raw data of
     */
    explicit RawData(T* obj);
    
    /**
     * Access into the object as if it was a uchar array, with bounds checking
     *
     * \param pos Index to access
     * \return Character value at that index
     */
    uchar& operator[](size_t pos);
    
    /**
     * Access into the object as if it was an array of type U, with bounds checking
     *
     * \tparam U Type to access
     * \param pos Index to access at (byte-aligned)
     * \return U value at index
     */
    template<typename U>
    U& get_value(size_t pos);
    
    /**
     * Set a value in the object as if it was an array of type U, with bounds checking
     *
     * \tparam U Type to set as
     * \param pos Index to set at (byte-aligned)
     * \param val value to set at location
     */
    template<typename U>
    void set_value(size_t pos, const U& val);
    
};

/**
 * Type representing a Templated compile-time integer range
 * Take as an argument, and then one can use I in variadic unpacking for a guaranteed range
 *
 * \tparam I Variadic pack of integer values
 */
template<size_t... I>
struct TemplateRange {};

/**
 * \brief Helper for creating various instances of TemplateRange
 *
 * Provides RangeBuilder, and in the future possibly other ways to generate TemplateRange instances.
 */
namespace VariadicRangeBuilder {
    
    /**
     * RangeBuilder base. Takes a minimum value, a maximum value, and a pack of the result.
     *
     * \tparam MIN Value to start range at
     * \tparam N Current count value of the builder
     * \tparam I Variadic pack of integer values
     */
    template<size_t MIN, size_t N, size_t... I>
    struct RangeBuilder;
    
    /**
     * RangeBuilder specialization for when the range is fully built (N == MIN). Returns the finalized TemplateRange
     *
     * \tparam MIN Value to start at
     * \tparam I Finished value pack
     */
    template<size_t MIN, size_t... I>
    struct RangeBuilder<MIN, MIN, I...> {
        
        /**
         * Final constructed TemplateRange, with full range
         */
        typedef TemplateRange<I...> range;
        
    };
    
    /**
     * RangeBuilder specialization for when the range is still being built. Adds the next value to the pack,
     * and decrements N.
     *
     * \tparam MIN Value to start at
     * \tparam N Current count value of the builder
     * \tparam I Variadic pack of values
     */
    template<size_t MIN, size_t N, size_t... I>
    struct RangeBuilder : public RangeBuilder<MIN, N - 1, N - 1, I...> {};
    
}

/**
 * Alias for a VariadicRangeBuilder that counts from [0, sizeof...(Args)).
 * Useful for indexing an array based on a variadic template
 */
template<typename... Args>
using VariadicRange = typename VariadicRangeBuilder::RangeBuilder<0, sizeof...(Args)>::range;

}

#include "sfinae.tpp"

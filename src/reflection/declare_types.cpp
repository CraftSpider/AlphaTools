
#include "reflection/declare_types.h"

// Declare reflected types

// Special Case

_AT_DECLARE_VOID()

// Integral Types

//  Default

AT_DECLARE_TYPE(char)

AT_DECLARE_TYPE(short)

AT_DECLARE_TYPE(int)

AT_DECLARE_TYPE(long)

AT_DECLARE_TYPE(long long)

//  Signed

AT_DECLARE_TYPE(signed char)

//  Unsigned

AT_DECLARE_TYPE(unsigned char)

AT_DECLARE_TYPE(unsigned short)

AT_DECLARE_TYPE(unsigned int)

AT_DECLARE_TYPE(unsigned long)

AT_DECLARE_TYPE(unsigned long long)

// Common Builtin Types

AT_DECLARE_TYPE(bool)

AT_DECLARE_TYPE(wchar_t)

AT_DECLARE_TYPE(float)

AT_DECLARE_TYPE(double)

AT_DECLARE_TYPE(long double)

AT_DECLARE_TYPE(nullptr_t)

// Common Pointer Types

AT_DECLARE_TYPE(void*)

AT_DECLARE_TYPE(char*)

AT_DECLARE_TYPE(unsigned char*)

// Stdlib

AT_DECLARE_TYPE(std::string)
AT_DECLARE_CONSTRUCTOR(std::string, std::string&, size_t, size_t)
AT_DECLARE_CONSTRUCTOR(std::string, const char*)
AT_DECLARE_CONSTRUCTOR(std::string, const char*, size_t)
AT_DECLARE_CONSTRUCTOR(std::string, size_t, char)

AT_DECLARE_MEMBER_FUNC_OVERLOAD(std::string, assign, std::string&, size_t, char)
AT_DECLARE_MEMBER_FUNC_OVERLOAD(std::string, assign, std::string&, const std::string&)
AT_DECLARE_MEMBER_FUNC(std::string, at)

AT_DECLARE_TYPE(std::exception)

AT_DECLARE_TYPE(std::runtime_error)
AT_DECLARE_CONSTRUCTOR(std::runtime_error, std::string)
AT_DECLARE_PARENT(std::runtime_error, std::exception)

AT_DECLARE_TYPE(std::vector<reflect::Type*>)
AT_DECLARE_TYPE(std::vector<reflect::Variant>)
AT_DECLARE_TYPE(std::vector<reflect::Constructor*>)
AT_DECLARE_TYPE(std::vector<reflect::MemberProperty*>)
AT_DECLARE_TYPE(std::vector<reflect::MemberFunction*>)
AT_DECLARE_TYPE(std::vector<reflect::StaticProperty*>)
AT_DECLARE_TYPE(std::vector<reflect::StaticFunction*>)

// Self

AT_DECLARE_TYPE(reflect::Type)
AT_DECLARE_TYPE(reflect::Type*)

AT_DECLARE_STATIC_FUNC(reflect::Type, from_name)

AT_DECLARE_MEMBER_FUNC(reflect::Type, get_name)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_constructors)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_constructor)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_default_constructor)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_copy_constructor)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_move_constructor)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_property)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_properties)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_functions)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_function)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_static_property)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_static_properties)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_static_functions)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_static_function)
AT_DECLARE_MEMBER_FUNC(reflect::Type, get_destructor)

AT_DECLARE_TYPE(reflect::Variant)
AT_DECLARE_TYPE(reflect::Variant*)

AT_DECLARE_STATIC_FUNC(reflect::Variant, from_type)
AT_DECLARE_STATIC_FUNC(reflect::Variant, from_pair)
AT_DECLARE_STATIC_FUNC(reflect::Variant, from_pair_owned)

AT_DECLARE_CONST_MEMBER_FUNC(reflect::Variant, get_type)
AT_DECLARE_MEMBER_FUNC(reflect::Variant, get_value_unsafe)
AT_DECLARE_MEMBER_FUNC(reflect::Variant, take_value_unsafe)
AT_DECLARE_CONST_MEMBER_FUNC(reflect::Variant, get_owned)

AT_DECLARE_TYPE(reflect::Constructor)
AT_DECLARE_TYPE(reflect::Constructor*)

AT_DECLARE_MEMBER_FUNC_NOARG(reflect::Constructor, construct, reflect::Variant)
AT_DECLARE_MEMBER_FUNC_OVERLOAD(reflect::Constructor, construct, reflect::Variant, std::vector<reflect::Variant>)
AT_DECLARE_MEMBER_FUNC(reflect::Constructor, construct_unsafe)
AT_DECLARE_MEMBER_FUNC(reflect::Constructor, get_type)
AT_DECLARE_MEMBER_FUNC(reflect::Constructor, get_arg_types)
AT_DECLARE_MEMBER_FUNC(reflect::Constructor, get_num_args)

AT_DECLARE_TYPE(reflect::MemberProperty)
AT_DECLARE_TYPE(reflect::MemberProperty*)

AT_DECLARE_MEMBER_FUNC(reflect::MemberProperty, get)
AT_DECLARE_MEMBER_FUNC(reflect::MemberProperty, set)
AT_DECLARE_MEMBER_FUNC(reflect::MemberProperty, get_type)
AT_DECLARE_MEMBER_FUNC(reflect::MemberProperty, get_property_type)
AT_DECLARE_MEMBER_FUNC(reflect::MemberProperty, get_name)

AT_DECLARE_TYPE(reflect::MemberFunction)
AT_DECLARE_TYPE(reflect::MemberFunction*)

AT_DECLARE_MEMBER_FUNC_OVERLOAD(reflect::MemberFunction, invoke, reflect::Variant, reflect::Variant)
AT_DECLARE_MEMBER_FUNC_OVERLOAD(reflect::MemberFunction, invoke, reflect::Variant, reflect::Variant, std::vector<reflect::Variant>)
AT_DECLARE_MEMBER_FUNC(reflect::MemberFunction, get_type)
AT_DECLARE_MEMBER_FUNC(reflect::MemberFunction, get_return_type)
AT_DECLARE_MEMBER_FUNC(reflect::MemberFunction, get_arg_types)
AT_DECLARE_MEMBER_FUNC(reflect::MemberFunction, get_num_args)
AT_DECLARE_MEMBER_FUNC(reflect::MemberFunction, get_name)

AT_DECLARE_TYPE(reflect::StaticProperty)
AT_DECLARE_TYPE(reflect::StaticProperty*)

AT_DECLARE_MEMBER_FUNC(reflect::StaticProperty, get)
AT_DECLARE_MEMBER_FUNC(reflect::StaticProperty, set)
AT_DECLARE_MEMBER_FUNC(reflect::StaticProperty, get_type)
AT_DECLARE_MEMBER_FUNC(reflect::StaticProperty, get_property_type)
AT_DECLARE_MEMBER_FUNC(reflect::StaticProperty, get_name)

AT_DECLARE_TYPE(reflect::StaticFunction)
AT_DECLARE_TYPE(reflect::StaticFunction*)

AT_DECLARE_MEMBER_FUNC_NOARG(reflect::StaticFunction, invoke, reflect::Variant)
AT_DECLARE_MEMBER_FUNC_OVERLOAD(reflect::StaticFunction, invoke, reflect::Variant, std::vector<reflect::Variant>)
AT_DECLARE_MEMBER_FUNC(reflect::StaticFunction, get_type)
AT_DECLARE_MEMBER_FUNC(reflect::StaticFunction, get_return_type)
AT_DECLARE_MEMBER_FUNC(reflect::StaticFunction, get_arg_types)
AT_DECLARE_MEMBER_FUNC(reflect::StaticFunction, get_num_args)
AT_DECLARE_MEMBER_FUNC(reflect::StaticFunction, get_name)

AT_DECLARE_TYPE(reflect::Destructor)
AT_DECLARE_TYPE(reflect::Destructor*)

AT_DECLARE_MEMBER_FUNC(reflect::Destructor, destruct)
AT_DECLARE_MEMBER_FUNC(reflect::Destructor, unsafe_destruct)
AT_DECLARE_MEMBER_FUNC(reflect::Destructor, get_type)

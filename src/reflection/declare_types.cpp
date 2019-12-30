
#include "reflection/declare_types.h"

// Declare reflected types

// Special Case

DECLARE_VOID()

// Integral Types

//  Default

DECLARE_TYPE(char)

DECLARE_TYPE(short)

DECLARE_TYPE(int)

DECLARE_TYPE(long)

DECLARE_TYPE(long long)

//  Signed

DECLARE_TYPE(signed char)

//  Unsigned

DECLARE_TYPE(unsigned char)

DECLARE_TYPE(unsigned short)

DECLARE_TYPE(unsigned int)

DECLARE_TYPE(unsigned long)

DECLARE_TYPE(unsigned long long)

// Common Builtin Types

DECLARE_TYPE(bool)

DECLARE_TYPE(wchar_t)

DECLARE_TYPE(float)

DECLARE_TYPE(double)

DECLARE_TYPE(long double)

DECLARE_TYPE(nullptr_t)

// Common Pointer Types

DECLARE_TYPE(void*)

DECLARE_TYPE(char*)

DECLARE_TYPE(unsigned char*)

// Stdlib

DECLARE_TYPE(std::string)
DECLARE_CONSTRUCTOR(std::string, std::string&, size_t, size_t)
DECLARE_CONSTRUCTOR(std::string, const char*)
DECLARE_CONSTRUCTOR(std::string, const char*, size_t)
DECLARE_CONSTRUCTOR(std::string, size_t, char)

DECLARE_MEMBER_FUNC_OVERLOAD(std::string, assign, std::string&, size_t, char)
DECLARE_MEMBER_FUNC_OVERLOAD(std::string, assign, std::string&, const std::string&)
DECLARE_MEMBER_FUNC(std::string, at)

DECLARE_TYPE(std::runtime_error)
DECLARE_CONSTRUCTOR(std::runtime_error, std::string)

DECLARE_TYPE(std::vector<reflect::Type*>)
DECLARE_TYPE(std::vector<reflect::Variant>)
DECLARE_TYPE(std::vector<reflect::Constructor*>)
DECLARE_TYPE(std::vector<reflect::MemberProperty*>)
DECLARE_TYPE(std::vector<reflect::MemberFunction*>)
DECLARE_TYPE(std::vector<reflect::StaticProperty*>)
DECLARE_TYPE(std::vector<reflect::StaticFunction*>)

// Self

DECLARE_TYPE(reflect::Type)
DECLARE_TYPE(reflect::Type*)

DECLARE_STATIC_FUNC(reflect::Type, from_name)

DECLARE_MEMBER_FUNC(reflect::Type, get_name)
DECLARE_MEMBER_FUNC(reflect::Type, get_constructors)
DECLARE_MEMBER_FUNC(reflect::Type, get_constructor)
DECLARE_MEMBER_FUNC(reflect::Type, get_default_constructor)
DECLARE_MEMBER_FUNC(reflect::Type, get_copy_constructor)
DECLARE_MEMBER_FUNC(reflect::Type, get_move_constructor)
DECLARE_MEMBER_FUNC(reflect::Type, get_property)
DECLARE_MEMBER_FUNC(reflect::Type, get_properties)
DECLARE_MEMBER_FUNC(reflect::Type, get_functions)
DECLARE_MEMBER_FUNC(reflect::Type, get_function)
DECLARE_MEMBER_FUNC(reflect::Type, get_static_property)
DECLARE_MEMBER_FUNC(reflect::Type, get_static_properties)
DECLARE_MEMBER_FUNC(reflect::Type, get_static_functions)
DECLARE_MEMBER_FUNC(reflect::Type, get_static_function)
DECLARE_MEMBER_FUNC(reflect::Type, get_destructor)

DECLARE_TYPE(reflect::Variant)
DECLARE_TYPE(reflect::Variant*)

DECLARE_STATIC_FUNC(reflect::Variant, from_type)
DECLARE_STATIC_FUNC(reflect::Variant, from_pair)
DECLARE_STATIC_FUNC(reflect::Variant, from_pair_owned)

DECLARE_MEMBER_FUNC(reflect::Variant, get_type)
DECLARE_MEMBER_FUNC(reflect::Variant, get_value_unsafe)
DECLARE_MEMBER_FUNC(reflect::Variant, take_value_unsafe)
DECLARE_MEMBER_FUNC(reflect::Variant, get_owned)

DECLARE_TYPE(reflect::Constructor)
DECLARE_TYPE(reflect::Constructor*)

DECLARE_MEMBER_FUNC_NOARG(reflect::Constructor, construct, reflect::Variant)
DECLARE_MEMBER_FUNC_OVERLOAD(reflect::Constructor, construct, reflect::Variant, std::vector<reflect::Variant>)
DECLARE_MEMBER_FUNC(reflect::Constructor, construct_unsafe)
DECLARE_MEMBER_FUNC(reflect::Constructor, get_type)
DECLARE_MEMBER_FUNC(reflect::Constructor, get_arg_types)
DECLARE_MEMBER_FUNC(reflect::Constructor, get_num_args)

DECLARE_TYPE(reflect::MemberProperty)
DECLARE_TYPE(reflect::MemberProperty*)

DECLARE_MEMBER_FUNC(reflect::MemberProperty, get)
DECLARE_MEMBER_FUNC(reflect::MemberProperty, set)
DECLARE_MEMBER_FUNC(reflect::MemberProperty, get_type)
DECLARE_MEMBER_FUNC(reflect::MemberProperty, get_property_type)
DECLARE_MEMBER_FUNC(reflect::MemberProperty, get_name)

DECLARE_TYPE(reflect::MemberFunction)
DECLARE_TYPE(reflect::MemberFunction*)

DECLARE_MEMBER_FUNC_OVERLOAD(reflect::MemberFunction, invoke, reflect::Variant, reflect::Variant)
DECLARE_MEMBER_FUNC_OVERLOAD(reflect::MemberFunction, invoke, reflect::Variant, reflect::Variant, std::vector<reflect::Variant>)
DECLARE_MEMBER_FUNC(reflect::MemberFunction, get_type)
DECLARE_MEMBER_FUNC(reflect::MemberFunction, get_return_type)
DECLARE_MEMBER_FUNC(reflect::MemberFunction, get_arg_types)
DECLARE_MEMBER_FUNC(reflect::MemberFunction, get_num_args)
DECLARE_MEMBER_FUNC(reflect::MemberFunction, get_name)

DECLARE_TYPE(reflect::StaticProperty)
DECLARE_TYPE(reflect::StaticProperty*)

DECLARE_MEMBER_FUNC(reflect::StaticProperty, get)
DECLARE_MEMBER_FUNC(reflect::StaticProperty, set)
DECLARE_MEMBER_FUNC(reflect::StaticProperty, get_type)
DECLARE_MEMBER_FUNC(reflect::StaticProperty, get_property_type)
DECLARE_MEMBER_FUNC(reflect::StaticProperty, get_name)

DECLARE_TYPE(reflect::StaticFunction)
DECLARE_TYPE(reflect::StaticFunction*)

DECLARE_MEMBER_FUNC_NOARG(reflect::StaticFunction, invoke, reflect::Variant)
DECLARE_MEMBER_FUNC_OVERLOAD(reflect::StaticFunction, invoke, reflect::Variant, std::vector<reflect::Variant>)
DECLARE_MEMBER_FUNC(reflect::StaticFunction, get_type)
DECLARE_MEMBER_FUNC(reflect::StaticFunction, get_return_type)
DECLARE_MEMBER_FUNC(reflect::StaticFunction, get_arg_types)
DECLARE_MEMBER_FUNC(reflect::StaticFunction, get_num_args)
DECLARE_MEMBER_FUNC(reflect::StaticFunction, get_name)

DECLARE_TYPE(reflect::Destructor)
DECLARE_TYPE(reflect::Destructor*)

DECLARE_MEMBER_FUNC(reflect::Destructor, destruct)
DECLARE_MEMBER_FUNC(reflect::Destructor, unsafe_destruct)
DECLARE_MEMBER_FUNC(reflect::Destructor, get_type)

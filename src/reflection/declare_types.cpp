
#include "reflection/declare_types.h"

// Declare reflected types

// Special Case

DECLARE_VOID()

// Integral Types

//  Signed

DECLARE_TYPE(char)

DECLARE_TYPE(short)

DECLARE_TYPE(int)

DECLARE_TYPE(long)

DECLARE_TYPE(long long)

// Signed

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

DECLARE_TYPE(char*)

DECLARE_TYPE(unsigned char*)

// Stdlib

DECLARE_TYPE(std::string)
DECLARE_CONSTRUCTOR(std::string, std::string&, size_t, size_t)
DECLARE_CONSTRUCTOR(std::string, const char*)
DECLARE_CONSTRUCTOR(std::string, const char*, size_t)
DECLARE_CONSTRUCTOR(std::string, size_t, char)

// TODO: Reference Variants
//DECLARE_MEMBER_FUNC_OVERLOAD(std::string, assign, std::string&, size_t, char)
//DECLARE_MEMBER_FUNC_OVERLOAD(std::string, assign, std::string&, const std::string&)
//DECLARE_MEMBER_FUNC(std::string, at)

DECLARE_TYPE(std::runtime_error)
DECLARE_CONSTRUCTOR(std::runtime_error, std::string)

// Self

DECLARE_TYPE(reflect::Type)

DECLARE_TYPE(reflect::Variant)

DECLARE_TYPE(reflect::Constructor)

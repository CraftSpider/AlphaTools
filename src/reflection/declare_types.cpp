
#include "reflection/declare_types.h"

// Declare reflected types

// Integral Types

//  Signed

DECLARE_TYPE(char)
DECLARE_DEFAULT_CONSTRUCTOR(char)

DECLARE_TYPE(short)
DECLARE_DEFAULT_CONSTRUCTOR(short)

DECLARE_TYPE(int)
DECLARE_DEFAULT_CONSTRUCTOR(int)

DECLARE_TYPE(long)
DECLARE_DEFAULT_CONSTRUCTOR(long)

DECLARE_TYPE(long long)
DECLARE_DEFAULT_CONSTRUCTOR(long long)

//  Unsigned

DECLARE_TYPE(unsigned char)
DECLARE_DEFAULT_CONSTRUCTOR(unsigned char)

DECLARE_TYPE(unsigned short)
DECLARE_DEFAULT_CONSTRUCTOR(unsigned short)

DECLARE_TYPE(unsigned int)
DECLARE_DEFAULT_CONSTRUCTOR(unsigned int)

DECLARE_TYPE(unsigned long)
DECLARE_DEFAULT_CONSTRUCTOR(unsigned long)

DECLARE_TYPE(unsigned long long)
DECLARE_DEFAULT_CONSTRUCTOR(unsigned long long)


// Common Builtin Types

DECLARE_TYPE(bool)
DECLARE_DEFAULT_CONSTRUCTOR(bool)

DECLARE_TYPE(float)
DECLARE_DEFAULT_CONSTRUCTOR(float)

DECLARE_TYPE(double)
DECLARE_DEFAULT_CONSTRUCTOR(double)

DECLARE_TYPE(nullptr_t)
DECLARE_DEFAULT_CONSTRUCTOR(nullptr_t)

// Common Pointer Types

DECLARE_TYPE(char*)
DECLARE_DEFAULT_CONSTRUCTOR(char*)

DECLARE_TYPE(unsigned char*)
DECLARE_DEFAULT_CONSTRUCTOR(unsigned char*)

// Stdlib

DECLARE_TYPE(std::string)
DECLARE_DEFAULT_CONSTRUCTOR(std::string)
DECLARE_CONSTRUCTOR(std::string, std::string&)
DECLARE_CONSTRUCTOR(std::string, std::string&, size_t, size_t)
DECLARE_CONSTRUCTOR(std::string, const char*)
DECLARE_CONSTRUCTOR(std::string, const char*, size_t)
DECLARE_CONSTRUCTOR(std::string, size_t, char)

DECLARE_TYPE(std::runtime_error)
DECLARE_CONSTRUCTOR(std::runtime_error, std::string)

// Self

DECLARE_TYPE(reflect::Type)

DECLARE_TYPE(reflect::Variant)

DECLARE_TYPE(reflect::Constructor)

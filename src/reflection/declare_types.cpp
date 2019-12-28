
#include "reflection/declare_types.h"

// Integral Types
//  Signed
DECLARE_TYPE(char)
DECLARE_TYPE(short)
DECLARE_TYPE(int)
DECLARE_TYPE(long)
DECLARE_TYPE(long long)
//  Unsigned
DECLARE_TYPE(unsigned char)
DECLARE_TYPE(unsigned short)
DECLARE_TYPE(unsigned int)
DECLARE_TYPE(unsigned long)
DECLARE_TYPE(unsigned long long)
// Common Builtin Types
DECLARE_TYPE(bool)
DECLARE_TYPE(float)
DECLARE_TYPE(double)
DECLARE_TYPE(decltype(nullptr))
// Common Pointer Types
DECLARE_TYPE(char*)
DECLARE_TYPE(const char*)
DECLARE_TYPE(unsigned char*)
DECLARE_TYPE(const unsigned char*)
// Stdlib
DECLARE_TYPE(std::string)
DECLARE_TYPE(std::runtime_error)
// Self
DECLARE_TYPE(reflect::Type)
DECLARE_TYPE(reflect::Variant)
DECLARE_TYPE(reflect::Constructor)

DECLARE_DEFAULT_CONSTRUCTOR(std::string)
//DECLARE_CONSTRUCTOR(std::string, std::string&)
//DECLARE_CONSTRUCTOR(std::string, std::string&, size_t, size_t)
DECLARE_CONSTRUCTOR(std::string, const char*)
DECLARE_CONSTRUCTOR(std::string, const char*, size_t)
DECLARE_CONSTRUCTOR(std::string, size_t, char)

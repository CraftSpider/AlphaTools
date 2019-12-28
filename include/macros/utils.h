#pragma once

#define AT_CONCATENATE(a, b) a##b
#define AT_EXPAND_CONCAT(a, b) AT_CONCATENATE(a, b)

#ifdef __COUNTER__
#define AT_UNIQUE_IDENT(prefix) AT_EXPAND_CONCAT(prefix, __COUNTER__)
#else
#define AT_UNIQUE_IDENT(prefix) AT_EXPAND_CONCAT(prefix, __LINE__)
#endif

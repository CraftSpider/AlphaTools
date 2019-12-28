#pragma once

#include "macros/utils.h"

#define AT_STATIC_IMPL2(varname, funcname) \
static void funcname(); \
static int varname = (funcname(), 0); \
static void funcname()

#define AT_STATIC_IMPL1(id) AT_STATIC_IMPL2(AT_CONCATENATE(id, _VAR), AT_CONCATENATE(id, _FUNC))

#define static_block AT_STATIC_IMPL1(AT_UNIQUE_IDENT(AT_STATIC_))

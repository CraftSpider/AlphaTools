#pragma once

#include "macros/utils.h"

/**
 * \file static_block.h
 * \brief Top-level static code execution
 *
 * The static_block macro provides a way to run code before the main() function
 * of an executable. It can only be used at the top level, and only in cpp files
 */

#define AT_STATIC_IMPL2(varname, funcname) \
static void funcname() noexcept; \
static int varname = (funcname(), 0); \
static void funcname() noexcept

#define AT_STATIC_IMPL1(id) AT_STATIC_IMPL2(AT_CONCATENATE(id, _VAR), AT_CONCATENATE(id, _FUNC))

#define static_block AT_STATIC_IMPL1(AT_UNIQUE_IDENT(AT_STATIC_))

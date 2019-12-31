#pragma once

#include "macros/utils.h"

/**
 * \file static_block.h
 * \brief Top-level static code execution
 *
 * The static_block macro provides a way to run code before the main() function
 * of an executable. It can only be used at the top level, and only in cpp files
 */

/**
 * \internal
 *
 * Second level implementation call for static_block, actually expands to the resulting static code
 */
#define AT_STATIC_IMPL2(varname, funcname) \
static void funcname() noexcept; \
static int varname = (funcname(), 0); \
static void funcname() noexcept

/**
 * \internal
 *
 * First level implementation call for static_block, generates variable and function names from
 * identifier
 */
#define AT_STATIC_IMPL1(id) AT_STATIC_IMPL2(AT_CONCATENATE(id, _VAR), AT_CONCATENATE(id, _FUNC))

/**
 * \brief Run blocks of code at top level before `main()`
 *
 * Provides a standard portable way to run blocks of code before the main function of a program.
 * This has several caveats: It can only be used in cpp files to prevent multiple-compilation, and
 * can only be used at the top level of a file. Also note that any variables defined in the block will
 * not be global, they will be scoped to the block.
 *
 * It is the user's responsibility to avoid issues due to undefined static run order, don't expect the block
 * to always run in the same order.
 *
 * Usage:
 * ```
 * static_block {
 *     do_setup();
 *     int a = 1;
 *     call_func(&a);
 * }
 * ```
 */
#define static_block AT_STATIC_IMPL1(AT_UNIQUE_IDENT(_AT_STATIC_))

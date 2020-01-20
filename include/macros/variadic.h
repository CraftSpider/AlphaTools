#pragma once

/**
 * \file variadic.h
 * \brief System for macros with variable numbers of arguments
 *
 * This macros allow one to switch what macro is expanded based on the number
 * of arguments to a variadic macro. The usage is slightly complex due to expansion
 * rules, as it stands there is no generic way (that I know) to make it prettier.
 *
 * Usage Example:
 *
 * ```
 * #define NEW_MACRO(...) AT_EXPAND(AT_VARIADIC_TWO(__VA_ARGS__, _TWO_ARGS(__VA_ARGS__), _ONE_ARG(__VA_ARGS__), AT_FILLER))
 *
 * #define NEW_MACRO(...) AT_EXPAND(AT_VARIADIC_THREE(__VA_ARGS__, _THREE_ARGS(__VA_ARGS__), AT_FILLER, _ONE_ARG(__VA_ARGS__), AT_FILLER))
 * ```
 */
 
/**
 * Filler to be used for argument numbers without macros, and as the last value in the list
 */
#define AT_FILLER INVALID_ARG_NUM

/**
 * Variadic for macros with a max of two arguments
 */
#define AT_VARIADIC_TWO(A, B, FUNC, ...) FUNC

/**
 * Variadic for macros with a max of three arguments
 */
#define AT_VARIADIC_THREE(A, B, C, FUNC, ...) FUNC

/**
 * Variadic for macros with a max of four arguments
 */
#define AT_VARIADIC_FOUR(A, B, C, D, FUNC, ...) FUNC

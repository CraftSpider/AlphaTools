#pragma once

/**
 * \file utils.h
 * \brief Common utility macros
 *
 * Various utility macros, for common operations at the pre-processing step.
 * Includes stuff like concatenation, unique identifiers, and token operations.
 */

/**
 * \brief Concatenate two tokens unexpanded
 *
 * Macro to concatenate two tokens, without expanding them. Generally not useful on its own
 */
#define AT_CONCATENATE(a, b) a##b
/**
 * \brief Expand then concatenate two tokens
 *
 * Macro to expand and then concatenate two tokens. Internally, just calls concatenate.
 * This ensures expansion due to C macro evaluation rules.
 */
#define AT_EXPAND_CONCAT(a, b) AT_CONCATENATE(a, b)

/**
 * \brief Generate a unique variable/function name
 *
 * Macro to generate a unique identifier. It's not impossible to generate a collision, so
 * make sure to choose uncommon prefixes.
 * Should work across compilers.
 */
#ifdef __COUNTER__
#define AT_UNIQUE_IDENT(prefix) AT_EXPAND_CONCAT(prefix, __COUNTER__)
#else
#define AT_UNIQUE_IDENT(prefix) AT_EXPAND_CONCAT(prefix, __LINE__)
#endif

/**
 * \internal
 *
 * Actually stringifies the token
 */
#define _AT_STRINGIFY(token) #token

/**
 * \brief Converts macro expansion to a string
 *
 * Convert a token to a string, including the result of another macro expansion
 */
#define AT_STRINGIFY(token) _AT_STRINGIFY(token)

/**
 * \brief Force expansion
 *
 * Expands the contained values before the next step of macro resolution,
 * useful for forcing __VA_ARGS__ in MSVC to work more like you would expect
 */
#define AT_EXPAND(token) token

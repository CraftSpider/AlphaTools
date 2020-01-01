#pragma once

#include <string>
#include "tests/test.h"
#include "macros/utils.h"
#include "macros/variadic.h"

/**
 * \file assertion.h
 * \brief Assertion support for tests, optionally with macros
 */

/**
 * \internal
 *
 * Macro for if only one value is passed to ASSERT()
 */
#define _AT_ASSERT_1(expr) testing::assert(expr, std::string("Expression \"") + #expr + "\" on line " AT_STRINGIFY(__LINE__) " failed assertion")

/**
 * \internal
 *
 * Macro for if two values are passed to ASSERT()
 */
#define _AT_ASSERT_2(expr, msg) testing::assert(expr, msg)

/**
 * \internal
 *
 * Macro for if two values are passed to ASSERT_EQ()
 */
#define _AT_ASSERT_EQ_2(expr1, expr2) testing::assert_equal(expr1, expr2, std::string("Expression \"") + #expr1 + "\" not equal to \"" + #expr2 + "\" on line " AT_STRINGIFY(__LINE__))

/**
 * \internal
 *
 * Macro for if three values are passed to ASSERT_EQ()
 */
#define _AT_ASSERT_EQ_3(expr1, expr2, msg) testing::assert_equal(expr1, expr2, msg)

/**
 * \internal
 *
 * Macro for if two values are passed to ASSERT_NEQ()
 */
#define _AT_ASSERT_NEQ_2(expr1, expr2) testing::assert_not_equal(expr1, expr2, std::string("Expression \"") + #expr1 + "\" equal to \"" + #expr2 + "\" on line " AT_STRINGIFY(__LINE__))

/**
 * \internal
 *
 * Macro for if three values are passed to ASSERT_NEQ()
 */
#define _AT_ASSERT_NEQ_3(expr1, expr2, msg) testing::assert_not_equal(expr1, expr2, msg)

/**
 * \internal
 *
 * Macro for if two values are passed to ASSERT_THROWS()
 */
#define _AT_ASSERT_THROWS_2(type, ref) testing::assert_throws<type>(ref, std::string("Function/Functor \"") + #ref + "\" failed to throw expected error of type \"" + #type + "\" on line " AT_STRINGIFY(__LINE__))

/**
 * \internal
 *
 * Macro for if three values are passed to ASSERT_THROWS()
 */
#define _AT_ASSERT_THROWS_3(type, ref, msg) testing::assert_throws<type>(ref, msg)

/**
 * Macro for assert statements. Can be passed either one or two arguments
 *
 * With one argument, the argument represents the statement to assert, and the message will be auto-generated.
 * With two arguments, the first argument is the statement to assert, and the second argument is the message if the
 * assertion fails.
 */
#define AT_ASSERT(...) AT_VARIADIC_TWO(,##__VA_ARGS__, _AT_ASSERT_2(__VA_ARGS__), _AT_ASSERT_1(__VA_ARGS__), AT_FILLER)

/**
 * Macro for asserting two things as equal. Can be passed either two or three arguments
 *
 * With two arguments, the two are the things to be checked equal, and the message will be auto-generated.
 * With three arguments, the first two are the things to be checked equal, and the third argument is the message if the
 * assertion fails
 */
#define AT_ASSERT_EQ(...) AT_VARIADIC_THREE(,##__VA_ARGS__, _AT_ASSERT_EQ_3(__VA_ARGS__), _AT_ASSERT_EQ_2(__VA_ARGS__), AT_FILLER)

/**
 * Macro for asserting two things as not equal. Can be passed either two or three arguments
 *
 * With two arguments, the two are the things to be checked not equal, and the message will be auto-generated.
 * With three arguments, the first two are the things to be checked not equal, and the third argument is the message if
 * the assertion fails
 */
#define AT_ASSERT_NEQ(...) AT_VARIADIC_THREE(,##__VA_ARGS__, _AT_ASSERT_NEQ_3(__VA_ARGS__), _AT_ASSERT_NEQ_2(__VA_ARGS__), AT_FILLER)

/**
 * Macro for asserting that a function call throws an error. Can be passed either two or three arguments.
 *
 * With two arguments, the first argument is the type of error expected, and the second argument is the function to call
 * (with no arguments). The message will be auto-generated.
 * With three arguments, the first argument is the type of error expected, the second argument is the function to call,
 * and the third argument is the message if the assertion fails
 */
#define AT_ASSERT_THROWS(...) AT_VARIADIC_THREE(,##__VA_ARGS__, _AT_ASSERT_THROWS_3(__VA_ARGS__), _AT_ASSERT_THROWS_2(__VA_ARGS__), AT_FILLER)

/**
 * Immediately fail the test with the given message.
 */
#define AT_FAIL(msg) testing::fail(msg);


#ifndef _AT_TESTS_NO_MACRO

/**
 * Alias for AT_ASSERT
 */
#define ASSERT(...) AT_ASSERT(__VA_ARGS__)

/**
 * Alias for AT_ASSERT_EQ
 */
#define ASSERT_EQ(...) AT_ASSERT_EQ(__VA_ARGS__)

/**
 * Alias for AT_ASSERT_NEQ
 */
#define ASSERT_NEQ(...) AT_ASSERT_NEQ(__VA_ARGS__)

/**
 * Alias for AT_ASSERT_THROWS
 */
#define ASSERT_THROWS(...) AT_ASSERT_THROWS(__VA_ARGS__)

/**
 * Alias for AT_FAIL
 */
#define FAIL(msg) AT_FAIL(msg)
#endif

namespace testing {

void assert(bool statement, std::string message = "");

template<typename T>
void assert_equal(T first, T second, std::string message = "");

template<typename T>
void assert_equal(T* first, T* second, std::string message = "");

template<typename T>
void assert_not_equal(T first, T second, std::string message = "");

template<typename T>
void assert_not_equal(T* first, T* second, std::string message = "");

template<typename T, typename U>
void assert_files_equal(T& first, U& second, std::string message = "");

template<typename T, typename U>
void assert_files_not_equal(T& first, U& second, std::string message = "");

void fail(std::string message = "");

template<typename T, typename ...Args, typename K>
void assert_throws(K callable, Args... args);

template<typename T, typename ...Args, typename K>
void assert_throws(std::string message, K callable, Args... args);

}

#include "assertion.tpp"

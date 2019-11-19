#pragma once

#include <string>
#include "tests/test.h"

#ifndef _AT_TESTS_NO_MACRO

#define _AT_ASSERT_1(expr) testing::assert(expr, std::string("Expression \"") + #expr + "\" failed assertion")
#define _AT_ASSERT_2(expr, msg) testing::assert(expr, msg)
#define _AT_ASSERT_X(x, A, B, FUNC, ...) FUNC

#define _AT_ASSERT_EQ_1(expr1, expr2) testing::assert_equal(expr1, expr2, std::string("Expression \"") + #expr1 + "\" not equal to \"" + #expr2 + "\"")
#define _AT_ASSERT_EQ_2(expr1, expr2, msg) testing::assert_equal(expr1, expr2, msg)
#define _AT_ASSERT_EQ_X(x, A, B, C, FUNC, ...) FUNC

#define _AT_ASSERT_NEQ_1(expr1, expr2) testing::assert_not_equal(expr1, expr2, std::string("Expression \"") + #expr1 + "\" equal to \"" + #expr2 + "\"")
#define _AT_ASSERT_NEQ_2(expr1, expr2, msg) testing::assert_not_equal(expr1, expr2, msg)
#define _AT_ASSERT_NEQ_X(x, A, B, C, FUNC, ...) FUNC

#define _AT_ASSERT_THROWS_1(type, ref) testing::assert_throws<type>(ref, std::string("Function/Functor \"") + #ref + "\" failed to throw expected error of type \"" + #type + "\"")
#define _AT_ASSERT_THROWS_2(type, ref, msg) testing::assert_throws<type>(ref, msg)
#define _AT_ASSERT_THROWS_X(x, A, B, C, FUNC, ...) FUNC

#define ASSERT(...) _AT_ASSERT_X(,##__VA_ARGS__, _AT_ASSERT_2(__VA_ARGS__), _AT_ASSERT_1(__VA_ARGS__), FILLER)
#define ASSERT_EQ(...) _AT_ASSERT_EQ_X(,##__VA_ARGS__, _AT_ASSERT_EQ_2(__VA_ARGS__), _AT_ASSERT_EQ_1(__VA_ARGS__), FILLER)
#define ASSERT_NEQ(...) _AT_ASSERT_NEQ_X(,##__VA_ARGS__, _AT_ASSERT_NEQ_2(__VA_ARGS__), _AT_ASSERT_NEQ_1(__VA_ARGS__), FILLER)
#define ASSERT_THROWS(...) _AT_ASSERT_THROWS_X(,##__VA_ARGS__, _AT_ASSERT_THROWS_2(__VA_ARGS__), _AT_ASSERT_THROWS_1(__VA_ARGS__), FILLER)

#define FAIL(msg) testing::fail(msg);

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

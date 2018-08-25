cmake_minimum_required(VERSION 3.12)
project(alpha_utils)

set(CMAKE_CXX_STANDARD 17)

include_directories(./src)
include_directories(./src/utils)

set(HEADERS
        src/utils/alpha_utils
        src/utils/types.h
        src/utils/arrays.h
        src/utils/io.h
        src/utils/strings.h
        src/utils/bytes.h
        src/utils/algorithms.h)

set(SOURCES
        src/utils/arrays.cpp
        src/utils/strings.cpp
        src/utils/bytes.cpp
        src/utils/algorithms.cpp)

set(TEMPLATES
        src/utils/arrays.tpp
        src/utils/io.tpp
        src/utils/bytes.tpp)

set(TEST_HEADERS
        tests/test.h
        tests/test_bytes.h
        tests/test_arrays.h)

set(TEST_SOURCES
        tests/main.cpp
        tests/test.cpp
        tests/test_bytes.cpp
        tests/test_arrays.cpp)

set(TEST_TEMPLATES)

set(ALL_CODE ${HEADERS} ${TEMPLATES} ${SOURCES})

set(ALL_TEST ${TEST_HEADERS} ${TEST_TEMPLATES} ${TEST_SOURCES})

add_library(${PROJECT_NAME} ${ALL_CODE})

add_executable(test_${PROJECT_NAME} ${ALL_CODE} ${ALL_TEST})
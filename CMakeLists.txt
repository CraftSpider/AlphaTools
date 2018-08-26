cmake_minimum_required(VERSION 3.12)
project(alpha_utils)

set(CMAKE_CXX_STANDARD 17)

include_directories(./include)
include_directories(./include/utils)
include_directories(./include/logging)

set(HEADERS
        include/a_utils
        include/a_logging
        include/a_tests
        include/argparser.h
        include/utils/types.h
        include/utils/arrays.h
        include/utils/io.h
        include/utils/strmanip.h
        include/utils/bytes.h
        include/utils/algorithms.h
        include/tests/test.h
        include/logging/logging.h include/logging/level.h include/logging/logger.h)

set(SOURCES
        src/argparser.cpp
        src/utils/arrays.cpp
        src/utils/strmanip.cpp
        src/utils/bytes.cpp
        src/utils/algorithms.cpp
        src/tests/test.cpp
        src/logging/logging.cpp src/logging/level.cpp include/logging/handler.h src/logging/handler.cpp src/logging/logger.cpp)

set(TEMPLATES
        include/utils/arrays.tpp
        include/utils/io.tpp
        include/utils/bytes.tpp)

set(TEST_HEADERS
        tests/test_bytes.h
        tests/test_arrays.h
        tests/test_strmanip.h
        tests/test_algorithms.h)

set(TEST_SOURCES
        tests/main.cpp
        tests/test_bytes.cpp
        tests/test_arrays.cpp
        tests/test_strmanip.cpp
        tests/test_algorithms.cpp)

set(TEST_TEMPLATES)

set(ALL_CODE ${HEADERS} ${TEMPLATES} ${SOURCES})

set(ALL_TEST ${TEST_HEADERS} ${TEST_TEMPLATES} ${TEST_SOURCES})

add_library(${PROJECT_NAME} ${ALL_CODE})

add_executable(test_${PROJECT_NAME} ${ALL_CODE} ${ALL_TEST})
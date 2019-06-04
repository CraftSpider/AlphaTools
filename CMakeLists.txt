cmake_minimum_required(VERSION 3.10)
project(alpha_tools)

set(CMAKE_CXX_STANDARD 17)

include_directories(./include)

if(MSVC)
    add_definitions(-W4)
    add_compile_definitions(_CRT_NO_VA_START_VALIDATION)
else()
    add_definitions(-Wall -Wextra -pedantic)
endif()

set(HEADERS
        include/at_utils
        include/at_logging
        include/at_tests
        include/argparser.h
        include/types.h
        include/console.h
        include/format.h
        include/generic.h
        include/utils/arrays.h
        include/utils/io.h
        include/utils/strmanip.h
        include/utils/bytes.h
        include/utils/algorithms.h
        include/tests/test.h
        include/tests/abstract_test.h
        include/tests/assertion.h
        include/logging/handler.h
        include/logging/logging.h
        include/logging/level.h
        include/logging/logger.h
        include/network/socket.h include/math/vector.h include/math/sphere.h)

set(SOURCES
        src/argparser.cpp
        src/console.cpp
        src/format.cpp
        src/generic.cpp
        src/utils/arrays.cpp
        src/utils/strmanip.cpp
        src/utils/bytes.cpp
        src/utils/algorithms.cpp
        src/tests/abstract_test.cpp
        src/tests/test.cpp
        src/tests/assertion.cpp
        src/logging/logging.cpp
        src/logging/level.cpp
        src/logging/handler.cpp
        src/logging/logger.cpp
        src/network/socket.cpp src/math/vector.cpp src/math/sphere.cpp)

set(TEMPLATES
        include/utils/arrays.tpp
        include/utils/io.tpp
        include/utils/bytes.tpp
        include/utils/strmanip.tpp
        include/tests/assertion.tpp
        include/logging/logger.tpp)

set(TEST_HEADERS
        tests/test_bytes.h
        tests/test_arrays.h
        tests/test_strmanip.h
        tests/test_algorithms.h
        tests/test_logging.h
        tests/test_format.h
        tests/test_console.h
        tests/test_test.h
        tests/test_io.h)

set(TEST_SOURCES
        tests/main.cpp
        tests/test_bytes.cpp
        tests/test_arrays.cpp
        tests/test_strmanip.cpp
        tests/test_algorithms.cpp
        tests/test_logging.cpp
        tests/test_format.cpp
        tests/test_console.cpp
        tests/test_test.cpp
        tests/test_io.cpp)

set(TEST_TEMPLATES)

set(ALL_CODE ${HEADERS} ${TEMPLATES} ${SOURCES})

set(ALL_TEST ${TEST_HEADERS} ${TEST_TEMPLATES} ${TEST_SOURCES} tests/test_test.cpp)

add_library(${PROJECT_NAME} STATIC ${ALL_CODE})

if(WIN32 OR CYGWIN)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .lib)
endif()

add_executable(test_${PROJECT_NAME} ${ALL_CODE} ${ALL_TEST})

if(MSVC)
    target_link_libraries(${PROJECT_NAME} ws2_32)
    target_link_libraries(test_${PROJECT_NAME} ws2_32)
endif()

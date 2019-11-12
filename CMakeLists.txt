cmake_minimum_required(VERSION 3.10)
project(alpha_tools)

set(CMAKE_CXX_STANDARD 17)

include_directories(./include)

if(MSVC)
    add_definitions(-W4)
    # C4003: Macro 'too many' or 'too few' warnings
    # C4458: Declaration shadows class member
    # C4611: Interaction between 'setjmp' and C++ object destruction is non-portable
    add_definitions(-wd4003 -wd4458 -wd4611)
    add_compile_definitions(_CRT_NO_VA_START_VALIDATION)
else()
    add_definitions(-Wall -Wextra -pedantic)
endif()

file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE TEMPLATES include/*.tpp)

file(GLOB_RECURSE TEST_HEADERS tests/*.h)
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
file(GLOB_RECURSE TEST_TEMPLATES tests/*.tpp)

set(ALL_CODE ${HEADERS} ${TEMPLATES} ${SOURCES})
set(ALL_TEST ${TEST_HEADERS} ${TEST_TEMPLATES} ${TEST_SOURCES})

add_library(${PROJECT_NAME} STATIC ${ALL_CODE})

if(WIN32 OR CYGWIN)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .lib)
endif()

add_executable(test_${PROJECT_NAME} ${ALL_CODE} ${ALL_TEST})

if(MSVC)
    target_link_libraries(${PROJECT_NAME} ws2_32)
    target_link_libraries(test_${PROJECT_NAME} ws2_32)
endif()

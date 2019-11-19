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

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/*.h include/at_*)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE TEMPLATES CONFIGURE_DEPENDS include/*.tpp)

file(GLOB_RECURSE TEST_HEADERS CONFIGURE_DEPENDS tests/*.h)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)
file(GLOB_RECURSE TEST_TEMPLATES CONFIGURE_DEPENDS tests/*.tpp)

set(ALL_CODE ${HEADERS} ${TEMPLATES} ${SOURCES})
set(ALL_TEST ${TEST_HEADERS} ${TEST_TEMPLATES} ${TEST_SOURCES})

add_library(${PROJECT_NAME} STATIC ${ALL_CODE})

if(WIN32 OR CYGWIN)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .lib)
endif()

add_executable(test_${PROJECT_NAME} ${ALL_CODE} ${ALL_TEST})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
if(MSVC)
    target_link_libraries(${PROJECT_NAME} ws2_32 dbghelp)
    target_link_libraries(test_${PROJECT_NAME} ws2_32 dbghelp)
endif()

if(WIN32)
    file(TO_NATIVE_PATH ${CMAKE_BINARY_DIR} BINARY_DIR)
    file(TO_NATIVE_PATH ${CMAKE_SOURCE_DIR} SOURCE_DIR)
    add_custom_command(TARGET test_${PROJECT_NAME} POST_BUILD
            COMMAND del /f /s /q ${BINARY_DIR}\\resource 1>nul
            COMMAND if exist \"${BINARY_DIR}\\resources\\\" rmdir /s /q ${BINARY_DIR}\\resources 2>nul
            COMMAND mkdir ${BINARY_DIR}\\resources
            COMMAND copy ${SOURCE_DIR}\\tests\\resources\\ ${BINARY_DIR}\\resources\\)
    unset(BINARY_DIR)
    unset(SOURCE_DIR)
else()
    add_custom_command(TARGET test_${PROJECT_NAME} POST_BUILD
            COMMAND rm -rf ${CMAKE_BINARY_DIR}/resources
            COMMAND mkdir -p ${CMAKE_BINARY_DIR}/resources
            COMMAND cp -r ${CMAKE_SOURCE_DIR}/tests/resources/ ${CMAKE_BINARY_DIR}/)
endif()

cmake_minimum_required(VERSION 3.10)
project(alpha_tools)

include(AlphaTest.cmake)

set(CMAKE_CXX_STANDARD 17)
set(TEST_PROJECT_NAME test_${PROJECT_NAME})

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

# Uncomment these following lines to run the compile with libubsan, which will print at runtime any undefined behavior used.
#    set(SANITIZE_FLAGS "-fsanitize=undefined -fsanitize=address -fsanitize=leak -fsanitize=shift -fsanitize=integer-divide-by-zero -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=null -fsanitize=return -fsanitize=bounds -fsanitize=bounds-strict -fsanitize=alignment -fsanitize=object-size -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=nonnull-attribute -fsanitize=returns-nonnull-attribute -fsanitize=bool -fsanitize=enum -fsanitize=vptr")
#    add_definitions(${SANITIZE_FLAGS})
#    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZE_FLAGS}")
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

add_executable(${TEST_PROJECT_NAME} ${ALL_CODE} ${ALL_TEST})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${TEST_PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
if(MSVC)
    target_link_libraries(${PROJECT_NAME} ws2_32 dbghelp)
    target_link_libraries(${TEST_PROJECT_NAME} ws2_32 dbghelp)
endif()

copy_test_resources(${TEST_PROJECT_NAME})

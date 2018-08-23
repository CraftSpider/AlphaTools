cmake_minimum_required(VERSION 3.12)
project(alpha_utils)

set(CMAKE_CXX_STANDARD 17)

set(HEADERS
    alpha_utils
    types.h
    arrays.h
    io.h)

set(SOURCES
    arrays.cpp
    io.cpp)

add_library(alpha_utils ${SOURCES} ${HEADERS})
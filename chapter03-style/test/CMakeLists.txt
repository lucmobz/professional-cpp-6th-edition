cmake_minimum_required(VERSION 3.29.2)

project(examples)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello)
target_sources(hello PUBLIC src/hello.cpp)

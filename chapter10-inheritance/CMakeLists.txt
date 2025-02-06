cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(questions)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

file(COPY $ENV{VCToolsInstallDir}/modules/std.ixx DESTINATION ${PROJECT_BINARY_DIR}/std)

add_executable(10-1)
target_sources(10-1 PRIVATE 10-1/main.cpp 10-1/Person.cpp)
target_sources(10-1 PRIVATE FILE_SET CXX_MODULES FILES 10-1/Person.ixx ${PROJECT_BINARY_DIR}/std/std.ixx)

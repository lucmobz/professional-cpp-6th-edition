cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(questions)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

file(COPY $ENV{VCToolsInstallDir}/modules/std.ixx DESTINATION ${PROJECT_BINARY_DIR}/std)

add_executable(virtual-overloads)
target_sources(virtual-overloads PRIVATE virtual-overloads/main.cpp)
target_sources(virtual-overloads PRIVATE FILE_SET CXX_MODULES FILES ${PROJECT_BINARY_DIR}/std/std.ixx)

add_executable(virtual-base-init)
target_sources(virtual-base-init PRIVATE virtual-base-init/main.cpp)
target_sources(virtual-base-init PRIVATE FILE_SET CXX_MODULES FILES virtual-base-init/Zoo.ixx ${PROJECT_BINARY_DIR}/std/std.ixx)

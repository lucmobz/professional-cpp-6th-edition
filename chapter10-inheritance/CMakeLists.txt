cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

file(COPY $ENV{VCToolsInstallDir}/modules/std.ixx DESTINATION ${PROJECT_BINARY_DIR}/std)

add_subdirectory(10-1)
add_subdirectory(10-2)
add_subdirectory(10-3)
add_subdirectory(10-4)

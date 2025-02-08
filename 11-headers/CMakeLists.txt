cmake_minimum_required(VERSION 3.29.5 FATAL_ERROR)

project(11)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

file(COPY $ENV{VCToolsInstallDir}/modules/std.ixx DESTINATION ${PROJECT_BINARY_DIR}/std)

add_subdirectory(${PROJECT_NAME}-1)
add_subdirectory(${PROJECT_NAME}-2)
add_subdirectory(${PROJECT_NAME}-3)
add_subdirectory(${PROJECT_NAME}-4)
add_subdirectory(${PROJECT_NAME}-5)

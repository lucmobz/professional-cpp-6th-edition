cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(exercises09)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

file(COPY $ENV{VCToolsInstallDir}/modules/std.ixx DESTINATION ${PROJECT_BINARY_DIR}/std)

add_executable(09-1)
target_sources(09-1 PRIVATE 09-1/main.cpp)
target_sources(09-1 PRIVATE FILE_SET CXX_MODULES FILES ${PROJECT_SOURCE_DIR}/09-1/Person.ixx ${PROJECT_BINARY_DIR}/std/std.ixx)

add_executable(09-2)
target_sources(09-2 PRIVATE 09-2/main.cpp)
target_sources(09-2 PRIVATE FILE_SET CXX_MODULES FILES ${PROJECT_SOURCE_DIR}/09-2/Person.ixx ${PROJECT_BINARY_DIR}/std/std.ixx)

add_executable(09-3)
target_sources(09-3 PRIVATE 09-3/main.cpp)
target_sources(09-3 PRIVATE FILE_SET CXX_MODULES FILES ${PROJECT_SOURCE_DIR}/09-3/Person.ixx ${PROJECT_BINARY_DIR}/std/std.ixx)

add_executable(09-4)
target_sources(09-4 PRIVATE 09-4/main.cpp 09-4/Person.cpp)
target_sources(09-4 PRIVATE FILE_SET CXX_MODULES FILES ${PROJECT_SOURCE_DIR}/09-4/Person.ixx ${PROJECT_BINARY_DIR}/std/std.ixx)

add_executable(09-5)
target_sources(09-5 PRIVATE 09-5/main.cpp)
target_sources(09-5 PRIVATE FILE_SET CXX_MODULES FILES ${PROJECT_SOURCE_DIR}/09-5/Person.ixx ${PROJECT_BINARY_DIR}/std/std.ixx)

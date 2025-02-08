cmake_minimum_required(VERSION 3.29.2)

project(memory-management)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This seems to be required for intellisense in VS 2022 version 17.2
set(STD_IXX_FILE "C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Tools\\MSVC\\14.42.34433\\modules\\std.ixx")

add_executable(unique-ptr)
target_sources(unique-ptr PRIVATE "src/unique_ptr.cpp" ${STD_IXX_FILE})

add_executable(shared-ptr)
target_sources(shared-ptr PRIVATE "src/shared_ptr.cpp" ${STD_IXX_FILE})

add_executable(weak-ptr)
target_sources(weak-ptr PRIVATE "src/weak_ptr.cpp" ${STD_IXX_FILE})

add_executable(enabled-shared-from-this)
target_sources(enabled-shared-from-this PRIVATE "src/enabled_shared_from_this.cpp" ${STD_IXX_FILE})

add_executable(inout-ptr)
target_sources(inout-ptr PRIVATE "src/inout_ptr.cpp" ${STD_IXX_FILE})

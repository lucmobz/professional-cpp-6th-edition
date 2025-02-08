cmake_minimum_required(VERSION 3.29.2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(STD_IXX_FILE $ENV{VCToolsInstallDir}\\modules\\std.ixx)

# There are errors in the code as per exercise logic
add_executable(07-1)
target_sources(07-1 PRIVATE 07-1/main.cpp)
target_sources(07-1 PRIVATE ${STD_IXX_FILE})

add_executable(07-2)
target_sources(07-2 PRIVATE 07-2/main.cpp)
target_sources(07-2 PRIVATE ${STD_IXX_FILE})

add_executable(07-3)
target_sources(07-3 PRIVATE 07-3/main.cpp)
target_sources(07-3 PRIVATE ${STD_IXX_FILE})

add_executable(07-4)
target_sources(07-4 PRIVATE 07-4/main.cpp)
target_sources(07-4 PRIVATE ${STD_IXX_FILE})
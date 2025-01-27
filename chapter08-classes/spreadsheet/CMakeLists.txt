cmake_minimum_required(VERSION 3.29.2)

project(spreadsheet)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_executable(spreadsheet-test)
target_include_directories(spreadsheet-test PRIVATE src)
file(GLOB SRCS src/*.cpp)
file(GLOB MODS src/*.ixx)
target_sources(spreadsheet-test PRIVATE ${SRCS})
# This is added for intellisense, but forces constant recompilation, so comment it out for the true modules feel
target_sources(spreadsheet-test PRIVATE $ENV{VCToolsInstallDir}\\modules\\std.ixx)
target_sources(spreadsheet-test PRIVATE
    FILE_SET CXX_MODULES
    FILES ${MODS})

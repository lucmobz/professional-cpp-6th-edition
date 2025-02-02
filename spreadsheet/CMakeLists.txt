cmake_minimum_required(VERSION 3.29)

project(spreadsheet)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_SCAN_FOR_MODULES ON) # Possibly not needed

add_executable(spreadsheet-test)
target_include_directories(spreadsheet-test PRIVATE src)

file(GLOB CPP_SOURCES src/*.cpp)
file(GLOB IXX_SOURCES src/*.ixx)

target_sources(spreadsheet-test PRIVATE ${CPP_SOURCES})
target_sources(spreadsheet-test PRIVATE $ENV{VCToolsInstallDir}\\modules\\std.ixx) # This is added for intellisense, but forces constant recompilation
target_sources(spreadsheet-test PRIVATE FILE_SET CXX_MODULES FILES ${IXX_SOURCES})

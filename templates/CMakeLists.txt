cmake_minimum_required(VERSION 3.29.5 FATAL_ERROR)

project(templates)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

file(COPY $ENV{VCToolsInstallDir}/modules/std.ixx DESTINATION ${PROJECT_BINARY_DIR}/std)

set(EXE game-board)
file(GLOB IXX_FILES src/*.ixx)

add_executable(${EXE})
target_sources(${EXE} PRIVATE src/main.cpp)
target_sources(${EXE} PRIVATE FILE_SET CXX_MODULES 
    BASE_DIRS ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src
    FILES ${IXX_FILES} ${PROJECT_BINARY_DIR}/std/std.ixx
)

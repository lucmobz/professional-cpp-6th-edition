cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME EXE)
string(REPLACE " " "_" EXE ${EXE})

file(GLOB CPP_FILES *.cpp)
file(GLOB IXX_FILES *.ixx)

add_executable(${EXE})
target_sources(${EXE} PRIVATE ${CPP_FILES})
target_sources(${EXE} PRIVATE FILE_SET CXX_MODULES 
    BASE_DIRS ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} 
    FILES ${IXX_FILES} ${PROJECT_BINARY_DIR}/std/std.ixx
 "simulator.ixx")

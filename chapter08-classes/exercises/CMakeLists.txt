cmake_minimum_required(VERSION 3.29.2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(STD_IXX_FILE $ENV{VCToolsInstallDir}\\modules\\std.ixx)

add_executable(08-1)
target_sources(08-1 PRIVATE 08-1/main.cpp ${STD_IXX_FILE}
	PRIVATE FILE_SET CXX_MODULES BASE_DIRS 08-1 
	FILES 08-1/Person.ixx) 

add_executable(08-2)
target_sources(08-2 PRIVATE 08-2/main.cpp ${STD_IXX_FILE}
	PRIVATE FILE_SET CXX_MODULES BASE_DIRS 08-2 
	FILES 08-2/Person.ixx) 

add_executable(08-3)
target_sources(08-3 PRIVATE 08-3/main.cpp ${STD_IXX_FILE}
	PRIVATE FILE_SET CXX_MODULES BASE_DIRS 08-3 
	FILES 08-3/Person.ixx) 

add_executable(08-4)
target_sources(08-4 PRIVATE 08-4/main.cpp ${STD_IXX_FILE}
	PRIVATE FILE_SET CXX_MODULES BASE_DIRS 08-4 
	FILES 08-4/Person.ixx) 

		
		
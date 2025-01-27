cmake_minimum_required(VERSION 3.30)

project(xbox_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/exec)

set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/boost/1.86.0" CACHE PATH "Path to Boost")

find_package(Boost REQUIRED COMPONENTS iostreams)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_subdirectory(src)
endif()

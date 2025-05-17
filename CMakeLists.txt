cmake_minimum_required(VERSION 3.30)

project(xbox_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/exec)

# set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/boost/1.87.0" CACHE PATH "Path to Boost")

find_package(Boost REQUIRED CONFIG COMPONENTS iostreams)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(~/libs/dbg-macro)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_subdirectory(src)
	# add_subdirectory(tests)
	add_subdirectory(manual_test)
endif()

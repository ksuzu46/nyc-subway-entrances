cmake_minimum_required(VERSION 3.12)
project(NYCSubwayEntrances)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -Wextra")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR} "../bin")

file(GLOB_RECURSE NYCSubwayEntrances_SOURCES "src/*.cpp")
file(GLOB_RECURSE NYCSubwayEntrances_HEADERS "src/*.h")


set (NYCTreeInfo_INCLUDE_DIRS "")
foreach (_headerFile ${NYCSubwayEntrances_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND NYCSubwayEntrances_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES NYCSubwayEntrances_INCLUDE_DIRS)

add_executable (NYCSubwayEntrancesExe ${NYCSubwayEntrances_SOURCES})



cmake_minimum_required(VERSION 3.12)
project(sw3)


set(CMAKE_CXX_STANDARD 11)


include_directories(PUBLIC ${Tests})
include_directories(PRIVATE ${Command})
include_directories(PRIVATE ${GPS})
include_directories(PRIVATE ${HashItem})
include_directories(PRIVATE ${HashTable})
include_directories(PRIVATE ${SubwayPortal})
include_directories(PRIVATE ${SubwayRoute})
include_directories(PRIVATE ${SubwayStation})
include_directories(PRIVATE ${SubwaySystem})

set(SOURCES main.cpp Command/command.cpp HashItem/_hash_item.cpp
        HashTable/hash_table.cpp
        GPS/gps.cpp SubwaySystem/subway_system.cpp
        SubwayPortal/subway_portal.cpp
        SubwayStation/subway_station.cpp SubwayRoute/subway_route.cpp
        )

add_executable(sw3 ${SOURCES})

add_library(subways ${SOURCES})

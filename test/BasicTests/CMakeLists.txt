include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})


add_executable(BasicTests basic_check.cpp)

target_link_libraries(BasicTests gtest gtest_main)
target_link_libraries(BasicTests gmock gmock_main)
target_link_libraries(BasicTests subways)

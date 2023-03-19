cmake_minimum_required(VERSION 3.21)

project(Google_tests)
enable_testing()
include_directories(${PROJECT_NAME} PUBLIC ../include)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
        ${PROJECT_NAME}
        InverterIndexTest.cpp
        SearchServerTest.cpp
        ../src/InvertedIndex.cpp
        ../src/SearchServer.cpp
)
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
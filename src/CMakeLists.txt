cmake_minimum_required(VERSION 3.21)
set(Src
        "ConverterJSON.cpp"
        "SearchServer.cpp"
        "InvertedIndex.cpp"
        "main.cpp"
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(SearchServer ${Src})

target_link_libraries(SearchServer nlohmann_json::nlohmann_json)
target_include_directories(SearchServer PUBLIC ${MY_INCLUDE_DIR})

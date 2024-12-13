cmake_minimum_required(VERSION 3.27)
project(mario)

set(CMAKE_CXX_STANDARD 23)

include(cmake/CPM.cmake)
CPMAddPackage("gh:raysan5/raylib#5.5")
CPMAddPackage("gh:baylej/tmx#tmx_1.10.0")

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE tmx/src)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib tmx)

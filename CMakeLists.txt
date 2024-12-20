cmake_minimum_required(VERSION 3.27)
project(mario)

set(CMAKE_CXX_STANDARD 23)

include(cmake/CPM.cmake)
CPMAddPackage("gh:raysan5/raylib#5.5")
CPMAddPackage("gh:baylej/tmx#tmx_1.10.0")

add_executable(${PROJECT_NAME} src/main.cpp
        src/Menu.cpp
        src/Menu.h
        src/Button.cpp
        src/Button.h
        src/Game.h
        src/Game.cpp
        src/IDrawable.h
        src/TextureBackground.cpp
        src/TextureBackground.h
        src/UIText.cpp
        src/UIText.h
        src/UIFrame.cpp
        src/UIFrame.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib tmx)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_CURRENT_BINARY_DIR}/Resources
)

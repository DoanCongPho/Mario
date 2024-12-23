cmake_minimum_required(VERSION 3.27)
project(mario)

set(CMAKE_CXX_STANDARD 23)

include(cmake/CPM.cmake)
CPMAddPackage("gh:raysan5/raylib#5.5")
CPMAddPackage("gh:baylej/tmx#tmx_1.10.0")

add_executable(${PROJECT_NAME} src/main.cpp
        src/Block.cpp
        src/Block.hpp
        src/Button.cpp
        src/Button.h
        src/CollisionBox.hpp
        src/config.hpp
        src/Game.h
        src/Game.cpp
        src/IDrawable.h
        src/Map.cpp
        src/Map.hpp
        src/Player.cpp
        src/Player.hpp
        src/TextureBackground.cpp
        src/TextureBackground.h
        src/ResourcesManager.cpp
        src/ResourcesManager.hpp
        src/Sprite.hpp
        src/Sprite.cpp
        src/UIText.cpp
        src/UIText.h
        src/UIFrame.cpp
        src/UIFrame.h
        src/baddies/Baddie.cpp
        src/baddies/Baddie.h
        src/SpriteState.h
        src/baddies/BanzaiBill.cpp
        src/baddies/BanzaiBill.h
        src/CollisionType.h
        src/CollisionProbe.cpp
        src/CollisionProbe.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib tmx)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_CURRENT_BINARY_DIR}/Resources
)

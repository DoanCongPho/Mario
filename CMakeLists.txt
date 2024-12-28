cmake_minimum_required(VERSION 3.27)
project(mario)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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
        src/ResourcesManager.hpp
        src/ResourcesManager.cpp
        src/Sound.cpp
        src/Sound.h
        src/Map.hpp
        src/Map.cpp
        src/Fireball.cpp
        src/Fireball.hpp
        src/app_config.h
        src/button.cpp
        src/button.h
        src/layout.cpp
        src/layout.h
        src/background.cpp
        src/background.h
        src/baddies/Baddie.cpp
        src/baddies/Baddie.h
        src/SpriteState.h
        src/baddies/BanzaiBill.cpp
        src/baddies/BanzaiBill.h
        src/CollisionType.h
        src/CollisionProbe.cpp
        src/CollisionProbe.h
        src/baddies/BlueKoopaTroopa.cpp
        src/baddies/BlueKoopaTroopa.h
        src/baddies/BobOmb.cpp
        src/baddies/BobOmb.h
        src/baddies/BuzzyBeetle.cpp
        src/baddies/BuzzyBeetle.h
        src/baddies/BulletBill.cpp
        src/baddies/BulletBill.h
        src/baddies/Rex.cpp
        src/baddies/Rex.h
        src/baddies/FlyingGoomba.cpp
        src/baddies/FlyingGoomba.h
        src/baddies/Goomba.cpp
        src/baddies/Goomba.h
        src/baddies/GreenKoopaTroopa.cpp
        src/baddies/GreenKoopaTroopa.h
        src/baddies/JumpingPiranhaPlant.cpp
        src/baddies/JumpingPiranhaPlant.h
        src/baddies/MontyMole.cpp
        src/baddies/MontyMole.h
        src/baddies/MummyBeetle.cpp
        src/baddies/MummyBeetle.h
        src/baddies/Muncher.cpp
        src/baddies/Muncher.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib tmx)
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_CURRENT_BINARY_DIR}/Resources
)


/*
#include <stdlib.h>
#include <iostream>
#include "raylib.h"
#include "tmx.h"
#include "ResourcesManager.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include <vector>
#define TILE_SIZE 32
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800



int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Game");
    loadAllAnimations();
    vector<Texture2D> walkingTextures = ResourcesManager::getInstance().getA("smallMario");
    vector<Texture2D> jumpingTextures = ResourcesManager::getInstance() .getA("smallMarioJump");
    vector<Texture2D> runningTextures= ResourcesManager::getInstance().getA("smallMarioRun");
    vector<Texture2D> tranfomationTextures = ResourcesManager::getInstance().getA("transToSuper");
    vector<Texture2D> superMarioWalk = ResourcesManager::getInstance().getA("superMario");
    vector<Texture2D> superMarioRun = ResourcesManager::getInstance().getA("superMarioRun");
    vector<Texture2D> superMarioJump =ResourcesManager::getInstance().getA("superMarioJump");
    vector<Texture2D> fireballs = ResourcesManager::getInstance().getA("fireballs");

    Player player({100.0f, 100.0f}, walkingTextures, jumpingTextures,runningTextures, tranfomationTextures, fireballs);
    Map map1("Resources/Map1.tmx", "Collision");
    Map map2("Resources/Map2.tmx", "Collision");
    Camera2D camera;
    camera.target = {
        player.position.x + player.size.x / 2.0f,
        player.position.y + player.size.y / 2.0f
    };
    camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0;
    camera.zoom = 1.0;
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        if(IsKeyPressed(KEY_T)){
            player.StartTransformation(superMarioWalk, superMarioJump, superMarioRun);
        }
        if(IsKeyPressed(KEY_R)){
            if(player.fireballsActive == false)
                player.ActivateFireballs();
            else
                player.DeactivateFireballs();
        }
        player.Update(delta, map2.GetCollisionBoxes());
        camera.target = {player.position.x + player.size.x / 2.0f, player.position.y + player.size.y / 2.0f};

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        map2.Render();
        player.Draw();
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
*/

/*#include "raylib.h"
#include "Game.h"

int main()
{
    InitWindow(640, 480, "Mario");
    Game game;
    game.Run();
    return 0;
}*/

#include "raylib.h"
#include <string>
#include <vector>
#include <algorithm>

#include "app_config.h"
#include "button.h"
#include "layout.h"
#include "background.h"

int main() {
    Config config;
    config.backgroundColor = DARKGRAY;
    config.fontSize = 20;
    config.baseFontSize = 20.0f;
    config.baseScreenWidth = 640;
    config.baseScreenHeight = 480;

    int screenWidth = config.baseScreenWidth;
    int screenHeight = config.baseScreenHeight;
    InitWindow(screenWidth, screenHeight, "Dynamic Background & Text");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    Texture2D background1 = LoadTexture("../Resources/images/menu/menu.png");
    Texture2D background2 = LoadTexture("../Resources/images/menu/Option.png");

    if (background1.id == 0) {
        background1 = LoadTextureFromImage(GenImageColor(screenWidth, screenHeight, DARKGRAY));
    }
    if (background2.id == 0) {
        background2 = LoadTextureFromImage(GenImageColor(screenWidth, screenHeight, DARKGRAY));
    }

    Texture2D currentBackground = background1;

    std::vector<Button> buttons;
    CreateButtons(buttons, config, currentBackground);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        int currentScreenWidth = GetScreenWidth();
        int currentScreenHeight = GetScreenHeight();

        for (auto &button: buttons) {
            button.UpdateButton(config);
        }

         HandleButtonClicks(buttons, currentBackground, background1, background2, config);

        if (currentScreenWidth != screenWidth || currentScreenHeight != screenHeight) {
            UpdateLayout(buttons, config, currentScreenWidth, currentScreenHeight);
            screenWidth = currentScreenWidth;
            screenHeight = currentScreenHeight;
        }

        BeginDrawing();
        ClearBackground(config.backgroundColor);

        float scaleX = (float) currentScreenWidth / config.baseScreenWidth;
        float scaleY = (float) currentScreenHeight / config.baseScreenHeight;
        float scale = std::min(scaleX, scaleY);

        float scaledWidth = currentBackground.width * scale;
        float scaledHeight = currentBackground.height * scale;
        float offsetX = (currentScreenWidth - scaledWidth) / 2;
        float offsetY = (currentScreenHeight - scaledHeight) / 2;

        config.fontSize = config.baseFontSize * std::min(scaleX,scaleY);

        DrawTextureEx(currentBackground, Vector2{offsetX, offsetY}, 0.0f, scale, WHITE);

        for (auto &button: buttons) {
            button.DrawButton(config);
        }
        EndDrawing();
    }

    UnloadTexture(background1);
    UnloadTexture(background2);
    CloseWindow();
    return 0;
}

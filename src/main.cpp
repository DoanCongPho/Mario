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
    loadMusic();
    int screenWidth = config.baseScreenWidth;
    int screenHeight = config.baseScreenHeight;
    InitWindow(screenWidth, screenHeight, "Dynamic Background & Text");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    Texture2D background1 = LoadTexture("Resources/images/menu/menu.png");
    Texture2D background2 = LoadTexture("Resources/images/menu/Option.png");

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
    SoundManager::getInstance().playMapMusic("INTRO");
    while (!WindowShouldClose()) {
        SoundManager::getInstance().updateMusic();
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

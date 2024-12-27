/*
#include "Game.h"

#include <iostream>
#include <ostream>

#include "UIText.h"


Game::Game() : frame("../Resources/images/menu/Untitled.png") {}

Game::~Game()
{
    CloseWindow();
}

void Game::LoadGame() {
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(60);
}

void Game::Run() {
    LoadGame();
    while (!WindowShouldClose()) {
        HandleInput();
        DrawScene();
    }
}

void Game::HandleInput(){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        frame.clearElements();
        if (frame.getBackgroundByPath("../Resources/images/menu/Untitled.png"))
        {
            frame.addElement(new UIText("PLAY GAME", { 270, 270 }, 25));
            auto *option = new UIText("OPTION", { 270, 315 }, 25);
            frame.addElement(option);
            frame.addElement(new UIText("EXIT", { 270, 345 }, 25));

            frame.addElement(new UIText("x 00", { 240, 30 }, 25,false));
            frame.addElement(new UIText("000000", { 55, 30 }, 25,false));
            frame.addElement(new UIText("1 - 1", { 390, 30 }, 25,false));

            frame.addElement(new UIText("MARIO", { 55, 10 }, 25,false));
            frame.addElement(new UIText("WORLD", { 365, 10 }, 25,false));
            frame.addElement(new UIText("TIME", { 505, 10 }, 25, false));
        }
        else
        {
            frame.addElement(new UIText("Text 1 - Background 1", { 100, 100 }, 20));
            frame.addElement(new UIText("Text 2 - Background 1", { 100, 200 }, 20));
        }
    }
    frame.updateHoverStatus();
}
void Game::DrawScene() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    frame.draw();
    EndDrawing();
}


Camera2D initCamera(Player &player){
    Camera2D camera;
    camera.target = {
        player.position.x + player.size.x / 2.0f,
        player.position.y + player.size.y / 2.0f
    };
    camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0;
    camera.zoom = 1.0;
    return camera;
}


void RunGame(Player& player, Map& map, Camera2D& camera) {
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        // Handle input
        /*if (IsKeyPressed(KEY_T)) {
            player.StartTransformation(
                ResourcesManager::getInstance().getA("superMario"),
                ResourcesManager::getInstance().getA("superMarioJump"),
                ResourcesManager::getInstance().getA("superMarioRun")
            );
        }#1#
        if (IsKeyPressed(KEY_R)) {
            if (player.fireballsActive)
                player.DeactivateFireballs();
            else
                player.ActivateFireballs();
        }

        // Update game state
        player.Update(delta, map.GetCollisionBoxes());
        camera.target = {
            player.position.x + player.size.x / 2.0f,
            player.position.y + player.size.y / 2.0f
        };

        // Render the frame
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        map.Render();
        player.Draw();
        EndMode2D();
        EndDrawing();
    }
}
*/

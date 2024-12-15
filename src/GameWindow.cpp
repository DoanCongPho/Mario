//
// Created by nhatk on 12/15/2024.
//

#include "GameWindow.h"
#include <vector>
#include <string>
#include "Menu.h"
GameWindow::GameWindow()
{
    InitWindow(640, 480, "Mario");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    const std::vector<std::string> menuText = {"PLAY","OPTIONS", "EXIT"};
    Menu background("../Resources/images/menu/Untitled.png", menuText);


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        background.draw();
        EndDrawing();
    }

    CloseWindow();
}

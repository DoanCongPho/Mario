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

    frame.addElement(new UIText("PLAY GAME", { 270, 285 }, 25));
    UIText* option = new UIText("OPTION", { 270, 315 }, 25);
    frame.addElement(option);
    frame.addElement(new UIText("EXIT", { 270, 345 }, 25));

    frame.addElement(new UIText("x 00", { 240, 30 }, 25,false));
    frame.addElement(new UIText("000000", { 55, 30 }, 25,false));
    frame.addElement(new UIText("1 - 1", { 390, 30 }, 25,false));

    frame.addElement(new UIText("MARIO", { 55, 10 }, 25,false));
    frame.addElement(new UIText("WORLD", { 365, 10 }, 25,false));
    frame.addElement(new UIText("TIME", { 505, 10 }, 25, false));

    SetTargetFPS(60);
    option->setClicked(true);
    if (option->isClickedOn())
    {
        changeBackground = !changeBackground;
    }
}

void Game::Run() {
    LoadGame();
    while (!WindowShouldClose()) {
        DrawScene();
        HandleInput();
    }
}

void Game::HandleInput(){

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        frame.clearElements();
        changeBackground = !changeBackground;
        if(changeBackground)
        {
            frame.changeBackground("../Resources/images/menu/menu.png");
            frame.addElement(new UIText("Text 1 - Background 1", { 100, 100 }, 20));
            frame.addElement(new UIText("Text 2 - Background 1", { 100, 200 }, 20));
        }
        else
        {
            std::cout << "abc" <<'\n';
            frame.changeBackground("../Resources/images/menu/Untitled.png");
            frame.addElement(new UIText("PLAY GAME", { 270, 285 }, 25));
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
    }
    frame.updateHoverStatus();
}
void Game::DrawScene() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    frame.draw();
    EndDrawing();
}
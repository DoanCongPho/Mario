#include "Game.h"

int main() {
    const int screenWidth = 640;
    const int screenHeight = 480;
    InitWindow(screenWidth, screenHeight, "Mario Game");
    Game game;
    game.Run();
    return 0;
}
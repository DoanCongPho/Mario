#ifndef GAME_H
#define GAME_H

#include "UIFrame.h"
#include <raylib.h>
#include "Player.hpp"
#include "Sound.h"
#include "Map.hpp"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

class Game {
private:
    UIFrame frame;
    bool changeBackground = true;
public:
    Game();
    ~Game();
    void LoadGame();
    void Run();
    void HandleInput();
    void DrawScene();
    void AddMainMenuElements();
};

Camera2D initCamera(Player &player);
void RunGame(Player& player, Map& map, Camera2D& camera);


#endif

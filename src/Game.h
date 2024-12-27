#ifndef GAME_H
#define GAME_H

#include "UIFrame.h"
#include <raylib.h>
#include "Player.hpp"
#include "Map.hpp"
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

class Game {
private:
    UIFrame frame;
public:
    Game();
    ~Game();
    void LoadGame();
    void Run();
    void HandleInput();
    void DrawScene();
};

Camera2D initCamera(Player &player); 
void RunGame(Player& player, Map& map, Camera2D& camera); 


#endif

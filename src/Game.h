#ifndef GAME_H
#define GAME_H

#include "UIFrame.h"


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

#endif
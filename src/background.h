#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "raylib.h"
#include <vector>
#include "button.h"
#include "app_config.h"
#include "Game.h"
#include "Sound.h"
#include <iostream>
#include "raylib.h"
#include "tmx.h"
#include "ResourcesManager.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include <vector>
#define TILE_SIZE 32
#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 800
using namespace std;

void HandleButtonClicks(std::vector<Button>& buttons, Texture2D& currentBackground, Texture2D background1, Texture2D background2, const Config& config);
void CreateButtons(std::vector<Button>& buttons, const Config& config, Texture2D currentBackground);


#endif

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "raylib.h"
#include <vector>
#include "button.h"
#include "app_config.h"


void HandleButtonClicks(std::vector<Button>& buttons, Texture2D& currentBackground, Texture2D background1, Texture2D background2, const Config& config);
void CreateButtons(std::vector<Button>& buttons, const Config& config, Texture2D currentBackground);


#endif
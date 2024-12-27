#ifndef LAYOUT_H
#define LAYOUT_H

#include "raylib.h"
#include <vector>
#include "button.h"
#include "app_config.h"

void UpdateLayout(std::vector<Button>& buttons, Config& config, int screenWidth, int screenHeight);

#endif
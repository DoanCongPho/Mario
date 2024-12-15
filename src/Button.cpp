//
// Created by nhatk on 12/15/2024.
//

#include "Button.h"


Button::Button(const char* imagePath, Vector2 position)
{
    buttonTexture = LoadTexture(imagePath);
    this->position = position;
}
Button::~Button()
{
    UnloadTexture(buttonTexture);
}

void Button::Draw()
{
    DrawTextureV(buttonTexture, position, WHITE);
}


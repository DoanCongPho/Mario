//
// Created by nhatk on 12/15/2024.
//

#ifndef BUTTON_H
#define BUTTON_H


#include "raylib.h"

class Button {
public:
    Button() : buttonTexture({0}), position( {0}) {};
    Button(const char* imagePath, Vector2 position);
    ~Button();
    void Draw();
private:
    Texture2D buttonTexture;
    Vector2 position;
};

#endif //BUTTON_H

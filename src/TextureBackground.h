#ifndef TEXTUREBACKGROUND_H
#define TEXTUREBACKGROUND_H

#include "raylib.h"
#include "IDrawable.h"

class TextureBackground : public IDrawable {
private:
    Texture2D texture;
public:
    TextureBackground(const char* path);
    ~TextureBackground() override;
    void draw() override;
    void changeTexture(const char* path);
    int originalWidth;
    int originalHeight;
};

#endif
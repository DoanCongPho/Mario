#ifndef TEXTUREBACKGROUND_H
#define TEXTUREBACKGROUND_H

#include <string>

#include "raylib.h"
#include "IDrawable.h"

class TextureBackground : public IDrawable {
private:
    Texture2D texture;
    std::string texturePath;
public:
    TextureBackground(const char* path);
    ~TextureBackground() override;
    void draw() override;
    void changeTexture(const char* path);
    int originalWidth;
    int originalHeight;
    std::string getTexturePath();
};

#endif
#include "TextureBackground.h"

TextureBackground::TextureBackground(const char* path)
{
    texture = LoadTexture(path);
    if (texture.id == 0) {
        TraceLog(LOG_ERROR, "ERROR: Texture could not be loaded");
    }
    originalWidth = texture.width;
    originalHeight = texture.height;
}

TextureBackground::~TextureBackground()
{
    UnloadTexture(texture);
}

void TextureBackground::draw()
{
    DrawTexture(texture, 0, 0, WHITE);
    Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    float scaleX = (float)GetScreenWidth() / (float)originalWidth;
    float scaleY = (float)GetScreenHeight() / (float)originalHeight;
    Rectangle destRec = { 0.0f, 0.0f, (float)originalWidth * scaleX, (float)originalHeight * scaleY };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(texture,sourceRec,destRec,origin,0.0f,WHITE);
}

void TextureBackground::changeTexture(const char* path)
{
    UnloadTexture(texture);
    texture = LoadTexture(path);
    if (texture.id == 0) {
        TraceLog(LOG_ERROR, "ERROR: Texture could not be loaded");
    }
    originalWidth = texture.width;
    originalHeight = texture.height;
}
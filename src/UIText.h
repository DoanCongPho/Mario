#ifndef UITEXT_H
#define UITEXT_H

#include "raylib.h"
#include "IDrawable.h"
#include <string>

class UIText : public IDrawable
{
private:
    std::string text;
    Vector2 originalPosition;
    int fontSize;
    float scaleX;
    float scaleY;
    bool isHovered;
    Rectangle bounds;
public:
    UIText(const std::string& text, Vector2 position, int fontSize);
    void draw() override;
    void setScale(float scaleX, float scaleY);
    bool isMouseOver();
    void setHover(bool isHovered);
};

#endif
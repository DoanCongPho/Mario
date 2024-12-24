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
    bool canPress;
    bool isClicked;
    Rectangle bounds;
    Color textColor = WHITE;

public:
    UIText(std::string  text, Vector2 position, int fontSize,bool canPress = true);
    void draw() override;
    void setScale(float scaleX, float scaleY);
    bool isMouseOver();
    void setHover(bool isHovered);
    bool isClickedOn();
    void setClicked(bool isClicked);
    std::string getText();
};

#endif
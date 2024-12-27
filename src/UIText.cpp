#include "UIText.h"

#include <iostream>
#include <utility>

UIText::UIText(std::string text, Vector2 position, int fontSize, bool canPress)
    : text(std::move(text)), originalPosition(position), fontSize(fontSize)
    , scaleX(1.0f), scaleY(1.0f), isHovered(false), canPress(canPress), isClicked(false) {}

void UIText::draw()
{
    textColor = (canPress && isHovered) ? YELLOW : WHITE;
    DrawText(text.c_str(), originalPosition.x * scaleX, originalPosition.y * scaleY, fontSize * scaleY, textColor);

    int textWidth = MeasureText(text.c_str(), fontSize);
    bounds = { originalPosition.x * scaleX, originalPosition.y * scaleY, (float)textWidth * scaleX, (float)fontSize * scaleY };
}

void UIText::setScale(float scaleX, float scaleY)
{
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}

bool UIText::isMouseOver()
{
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, bounds);
}

void UIText::setHover(bool isHovered)
{
    this->isHovered = isHovered;
}


void UIText::setClicked(bool isClicked)
{
    this->isClicked = isClicked;
}

bool UIText::isClickedOn()
{
    return isClicked;
}
std::string UIText::getText()
{
    return text;
}
#include "UIText.h"

UIText::UIText(const std::string& text, Vector2 position, int fontSize)
: text(text), originalPosition(position), fontSize(fontSize)
, scaleX(1.0f),scaleY(1.0f), isHovered(false) {}

void UIText::draw()
{
    Color textColor = isHovered ? YELLOW : WHITE;
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
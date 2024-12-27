#include "button.h"

#include <iostream>
#include <utility>
#include "app_config.h"
#include "raylib.h"


Button::Button(std::string text, Vector2 position, bool canClick) : text(std::move(text)), basePosition(position), canClick(canClick)
{
    baseBounds.x = position.x;
    baseBounds.y = position.y;
    baseBounds.width = 0;
    baseBounds.height =0;
    UpdateBounds();
    newPosition = basePosition;
}

void Button::UpdateBounds()
{
    Vector2 measure = MeasureTextEx(GetFontDefault(), text.c_str(), 20, 0);
    baseBounds.width = measure.x;
    baseBounds.height = measure.y;
    bounds = baseBounds;
}


void Button::DrawButton(const Config& config)
{
    DrawText(text.c_str(),newPosition.x,newPosition.y,config.fontSize,textColor);
}

Rectangle Button::getBounds()
{
    return baseBounds;
}

void Button::setBounds(const Rectangle& updateBounds)
{
    bounds = updateBounds;
}


void Button::UpdateButton(const Config& config)
{
    Vector2 mousePos = GetMousePosition();
    if (CheckCollisionPointRec(mousePos, bounds) && canClick) {
        textColor = hoverColor;
        if (IsMouseButtonPressed(0)) {
            clicked = true;
            textColor = clickColor;
        }
    } else {
        textColor = WHITE;
    }
}

bool Button::IsClicked()
{
    return clicked;
}

std::string Button::GetText()
{
     return text;
}

void Button::setClicked(bool clicked)
{
    this->clicked = clicked;
}

void Button::setSize(const float& size)
{
    baseFontSize = size;
}

Vector2 Button::GetOriginalPosition()
{
    return basePosition;
}


void Button::setPosition(const Vector2& updatePosition )
{
    newPosition = updatePosition;
}





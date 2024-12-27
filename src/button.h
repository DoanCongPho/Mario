#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "raylib.h"
#include "app_config.h"

class Button
{
private:
    std::string text;
    Vector2 basePosition;
    Vector2 newPosition;
    Color textColor = WHITE;
    Color hoverColor = YELLOW;
    Color clickColor = BLUE;
    bool clicked = false;
    bool canClick;
    float baseFontSize;
    Rectangle baseBounds;
    Rectangle bounds;
public:
    Button(std::string text, Vector2 position, bool canClick = true);
    void DrawButton(const Config& config);
    void UpdateButton(const Config& config);
    bool IsClicked();
    std::string GetText();
    void setClicked(bool clicked);
    void setSize(const float& size);
    Vector2 GetOriginalPosition();
    void setPosition(const Vector2& updatePosition);
    Rectangle getBounds();
    void setBounds(const Rectangle& updateBounds);
    void UpdateBounds();
};




#endif
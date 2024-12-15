#include "Menu.h"
#include "raylib.h"

Menu::Menu(const char* imagePath) {
    texture = LoadTexture(imagePath);
}

Menu::Menu(const char* imagePath, const std::vector<Button>& buttons, const std::vector<std::string>& text_strings_)
    : buttons(buttons), text_strings_(text_strings_) {
    texture = LoadTexture(imagePath);
}

Menu::~Menu() {
    UnloadTexture(texture);
}

Menu::Menu(const char* imagePath, const std::vector<std::string>& text_strings_) : text_strings_(text_strings_)
{
    texture = LoadTexture(imagePath);
}


void Menu::draw()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    DrawTexturePro(
        texture,
        Rectangle { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) },
        Rectangle { 0.0f, 0.0f, static_cast<float>(screenWidth), static_cast<float>(screenHeight) },
        Vector2{0.0f,0.0f},
        0.0f,
        WHITE
    );

    // Vẽ các buttons
    for (auto& button : buttons) {
        button.Draw();
    }

    // Vẽ các text (ví dụ, mỗi text một dòng)
    int fontSize = screenHeight / 20;
    int textY = screenHeight * 7 / 12;
    for (const auto& str : text_strings_) {
        int textWidth = MeasureText(str.c_str(), fontSize);
        int textX = (screenWidth - textWidth) / 2;
        DrawText(str.c_str(), textX, textY, fontSize, WHITE);
        textY += fontSize * 1.5;
    }
}

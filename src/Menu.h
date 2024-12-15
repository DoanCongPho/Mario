// Created by nhatk on 12/15/2024.
//

#ifndef MENU_H
#define MENU_H
#include <string>
#include <vector>

#include "Button.h"
#include "raylib.h"

class Menu {
private:
    Texture2D texture{};
    std::vector<Button> buttons;
    std::vector<std::string> text_strings_;

public:
    Menu() : texture() {};

    explicit Menu(const char* imagePath);

    Menu(const char* imagePath, const std::vector<Button>& buttons, const std::vector<std::string>& text_strings_);
    Menu(const char* imagePath, const std::vector<std::string>& text_strings_);
    ~Menu();

    void draw();
};

#endif //MENU_H
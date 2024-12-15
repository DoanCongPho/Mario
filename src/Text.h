//
// Created by nhatk on 12/15/2024.
//

#ifndef TEXT_H
#define TEXT_H
#include <string>
#include "../cmake-build-debug/_deps/raylib-src/src/raylib.h"


class Text {
    std::string text_string_;
    Vector2 position_;
    Color color_;
    bool canPress;
    int size_;
    public:
    Text();
    ~Text();
};



#endif //TEXT_H

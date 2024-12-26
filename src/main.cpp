
//
//#include <stdlib.h>
//#include <iostream>
//#include "raylib.h"
//#include "tmx.h"
//#include "ResourcesManager.hpp"
//#include "Map.hpp"
//#include "Player.hpp"
//#include <vector>
//#include "Game.h"
//#define TILE_SIZE 32
//#define SCREEN_WIDTH 1200
//#define SCREEN_HEIGHT 800


//int main() {
//    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Game");
//    loadAllAnimations();
//    vector<Texture2D> walkingTextures = ResourcesManager::getInstance().getA("smallMario");
//    vector<Texture2D> jumpingTextures = ResourcesManager::getInstance() .getA("smallMarioJump");
//    vector<Texture2D> runningTextures= ResourcesManager::getInstance().getA("smallMarioRun");
//    vector<Texture2D> tranfomationTextures = ResourcesManager::getInstance().getA("transToSuper");
//    vector<Texture2D> superMarioWalk = ResourcesManager::getInstance().getA("superMario");
//    vector<Texture2D> superMarioRun = ResourcesManager::getInstance().getA("superMarioRun");
//    vector<Texture2D> superMarioJump =ResourcesManager::getInstance().getA("superMarioJump");
//    vector<Texture2D> fireballs = ResourcesManager::getInstance().getA("fireballs");
//    Player player({100.0f, 100.0f}, walkingTextures, jumpingTextures,runningTextures, tranfomationTextures, fireballs);
//    Camera2D camera = initCamera(player);
//    Map map1("Resources/Map1.tmx", "Collision");
//    Map map2("Resources/Map2.tmx", "Collision");
//    SetTargetFPS(60);
//    RunGame(player, map2, camera);
//    CloseWindow();
//    return 0;
//}

//
//
/*#include "raylib.h"
#include "Game.h"

int main()
{
    InitWindow(640, 480, "Mario");
    Game game;
    game.Run();
    return 0;
}*/

#include "raylib.h"

#include <iostream>
#include <string>
#include <vector>

struct TextButton {
    Rectangle bounds;  // Vị trí và kích thước nút
    std::string text;  // Nội dung text
    Color textColor;   // Màu chữ mặc định
    Color hoverColor;  // Màu chữ khi hover
    Color backgroundColor; // Màu nền
    bool isHovering;   // Kiểm tra hover
};

void DrawTextButton(const TextButton& button) {

    // Vẽ nền
    DrawRectangleRec(button.bounds, button.backgroundColor);

    // Chọn màu text
    Color color = button.isHovering ? button.hoverColor : button.textColor;

    // Vẽ text căn giữa
    int textWidth = MeasureText(button.text.c_str(), 20);
    int x = button.bounds.x + (button.bounds.width - textWidth) / 2;
    int y = button.bounds.y + (button.bounds.height - 20) / 2;
    DrawText(button.text.c_str(), x, y, 20, color);
}

// Hàm kiểm tra xem chuột có nằm trong nút không
bool IsMouseInButton(const TextButton& button) {
    return CheckCollisionPointRec(GetMousePosition(), button.bounds);
}

// Hàm so sánh hai màu
bool ColorEquals(Color c1, Color c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}


int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Multiple Text Buttons");

    // Tạo danh sách các nút text
    std::vector<TextButton> buttons = {
       {{100, 100, 200, 50}, "Button 1", BLACK, BLUE, LIGHTGRAY, false},
       {{100, 200, 200, 50}, "Button 2", BLACK, GREEN, LIGHTGRAY, false},
       {{100, 300, 200, 50}, "Button 3", BLACK, RED,   LIGHTGRAY, false},
    };

    Color backgroundColor = WHITE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        // Xử lý hover và click cho từng nút
        for(auto& button : buttons){
            // Xử lý hover
            button.isHovering = IsMouseInButton(button);

             // Xử lý click
            if(button.isHovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               // Thay đổi logic click nếu cần
               backgroundColor = ColorEquals(backgroundColor, WHITE) ? DARKGRAY : WHITE;
            }
        }

        BeginDrawing();
            ClearBackground(backgroundColor);

            // Vẽ từng nút
             for(const auto& button : buttons){
                  DrawTextButton(button);
             }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

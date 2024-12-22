
#include <stdlib.h>
#include <iostream>
#include "raylib.h"
#include "tmx.h"
#include "ResourcesManager.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include <vector>
#define TILE_SIZE 32
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600




int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Game");
    loadAllAnimations();
    vector<Texture2D> walkingTextures = ResourcesManager::getInstance().getA("smallMario");
    vector<Texture2D> jumpingTextures = ResourcesManager::getInstance() .getA("smallMarioJump");
    Player player({100.0f, 100.0f}, walkingTextures, jumpingTextures);
    Map map("Resources/Map2.tmx", "Collision");
    
    Camera2D camera;
    camera.target = {
        player.position.x + player.size.x / 2.0f,
        player.position.y + player.size.y / 2.0f
    };
    camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0;
    camera.zoom = 1.0;
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        player.Update(delta, map.GetCollisionBoxes());
        camera.target = {player.position.x + player.size.x / 2.0f, player.position.y + player.size.y / 2.0f};
       
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        map.Render();
        player.Draw();
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

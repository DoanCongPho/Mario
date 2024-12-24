
#include <stdlib.h>
#include <iostream>
#include "raylib.h"
#include "tmx.h"
#include "ResourcesManager.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include <vector>
#define TILE_SIZE 32
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800



int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Game");
    loadAllAnimations();
    vector<Texture2D> walkingTextures = ResourcesManager::getInstance().getA("smallMario");
    vector<Texture2D> jumpingTextures = ResourcesManager::getInstance() .getA("smallMarioJump");
    vector<Texture2D> runningTextures= ResourcesManager::getInstance().getA("smallMarioRun");
    vector<Texture2D> tranfomationTextures = ResourcesManager::getInstance().getA("transToSuper");
    vector<Texture2D> superMarioWalk = ResourcesManager::getInstance().getA("superMario");
    vector<Texture2D> superMarioRun = ResourcesManager::getInstance().getA("superMarioRun");
    vector<Texture2D> superMarioJump =ResourcesManager::getInstance().getA("superMarioJump");
    vector<Texture2D> fireballs = ResourcesManager::getInstance().getA("fireballs");
    
    Player player({100.0f, 100.0f}, walkingTextures, jumpingTextures,runningTextures, tranfomationTextures, fireballs);
    Map map1("Resources/Map1.tmx", "Collision");
    Map map2("Resources/Map2.tmx", "Collision");
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
        if(IsKeyPressed(KEY_T)){
            player.StartTransformation(superMarioWalk, superMarioJump, superMarioRun);
        }
        if(IsKeyPressed(KEY_R)){
            if(player.fireballsActive == false)
                player.ActivateFireballs();
            else
                player.DeactivateFireballs();
        }
        player.Update(delta, map2.GetCollisionBoxes());
        camera.target = {player.position.x + player.size.x / 2.0f, player.position.y + player.size.y / 2.0f};
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        map2.Render();
        player.Draw();
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

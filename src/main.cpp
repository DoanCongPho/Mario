/*******************************************************************************************
 *
 *   raylib [texture] example - Import and display of Tiled map editor map
 *
 *   This example has been created using raylib 2.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2017 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/
#include <stdlib.h>
#include <iostream>
#include "raylib.h"
#include "tmx.h"
#include "ResourcesManager.hpp"
#include <vector>
#define TILE_SIZE 32
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 200.0f
constexpr float GRAVITY = 1200.0f; // Pixels per second^2
constexpr float JUMP_VELOCITY = 600.0f; // Pixels per second




typedef struct Player {
    Vector2 position;
    Vector2 velocity;
    bool onGround;
    Vector2 spawnPoint;
    Vector2 size;
} Player;


struct CollisionBox {
    Rectangle rect;
};

std::vector<CollisionBox> LoadCollisionData(const char* tmxFile, const char* objectGroupName) {
    std::vector<CollisionBox> collisionBoxes;
    
    tmx_map* map = tmx_load(tmxFile);
    if (!map) {
        std::cerr << "Failed to load TMX file: " << tmx_strerr() << std::endl;
        return collisionBoxes;
    }
    tmx_layer* layer = map->ly_head;
    while (layer) {
        if (layer->type == L_OBJGR && strcmp(layer->name, objectGroupName) == 0) {
            tmx_object* obj = layer->content.objgr->head;
            while (obj) {
                float x = obj->x;
                float y = obj->y;
                float width = obj->width;
                float height = obj->height;
                
                collisionBoxes.push_back({Rectangle{x, y, width, height}});
                obj = obj->next;
            }
        }
        layer = layer->next;
    }
    tmx_map_free(map);
    
    return collisionBoxes;
}



bool IsTileCollidable(tmx_layer *layer, tmx_map *map, int x, int y);
bool CheckCollisionWithMap(Player *player, tmx_map *map, tmx_layer *collisionLayer);
RenderTexture2D mapFrameBuffer;
Rectangle GetPlayerCollisionBox(const Player& player) {
    return Rectangle{player.position.x, player.position.y, player.size.x, player.size.y};
}


int main()
{
    std::vector<CollisionBox> collisionBoxes = LoadCollisionData("Resources/Map1.tmx", "Terrain");
    int screenWidth = 800;
    int screenHeight = 640;
    Player player = {
        .position = {100.0f, 100.0f},
        .velocity = {0.0f, 0.0f},
        .onGround = false,
        .spawnPoint = {100.0f, 100.0f},
        .size = {32.0f, 32.0f}
    };
    Camera2D camera;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");
    RenderTmxMapToFramebuf("Resources/Map1.tmx", &mapFrameBuffer);
    camera.target = (Vector2){ player.position.x, player.position.y };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0;
    camera.zoom = 1.0;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float delta = GetFrameTime();
        
        // Apply gravity
        if (!player.onGround) {
            player.velocity.y += GRAVITY * delta;
        }
        
        // Handle horizontal movement
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            player.velocity.x = 600.0f; // Move right
        } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            player.velocity.x = -600.0f; // Move left
        } else {
            player.velocity.x *= 0.8f;
            if (fabs(player.velocity.x) < 0.1f) {
                player.velocity.x = 0.0f;
            }
        }
      
        if (IsKeyPressed(KEY_SPACE) && player.onGround) {
            player.velocity.y = -JUMP_VELOCITY;
            player.onGround = false;
        }
     
        Vector2 nextPosition = {
            player.position.x + player.velocity.x * delta,
            player.position.y + player.velocity.y * delta
        };
        
        Rectangle playerBox = {nextPosition.x, player.position.y, player.size.x, player.size.y};
        bool collisionDetected = false;
        bool groundCollisionDetected = false;
 
        for (const auto& collider : collisionBoxes) {
            if (CheckCollisionRecs(playerBox, collider.rect)) {
                if (player.velocity.x > 0) {
                    nextPosition.x = collider.rect.x - player.size.x;
                } else if (player.velocity.x < 0) {
                    nextPosition.x = collider.rect.x + collider.rect.width;
                }
                player.velocity.x = 0;
                collisionDetected = true;
            }
        }
        player.position.x = nextPosition.x;
        playerBox = {player.position.x, nextPosition.y, player.size.x, player.size.y};
        for (const auto& collider : collisionBoxes) {
            if (CheckCollisionRecs(playerBox, collider.rect)) {
                if (player.velocity.y > 0) {
                    nextPosition.y = collider.rect.y - player.size.y;
                    player.onGround = true;
             
                } else if (player.velocity.y < 0) {
                    nextPosition.y = collider.rect.y + collider.rect.height;
                }
                player.velocity.y = 0;
                collisionDetected = true;
            }
                groundCollisionDetected = true;
        }
        if (!groundCollisionDetected) {
            player.onGround = false;
        }
        player.position.y = nextPosition.y;
        camera.target = (Vector2){
            player.position.x + player.size.x / 2.0f,
            player.position.y + player.size.y / 2.0f
        };
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        DrawTextureRec(
            mapFrameBuffer.texture,
            (Rectangle){0.0f, 0.0f, static_cast<float>(mapFrameBuffer.texture.width), static_cast<float>(-mapFrameBuffer.texture.height)},
            (Vector2){0.0, 0.0},
            WHITE);
        DrawRectangle(
            player.position.x,
            player.position.y,
            player.size.x,
            player.size.y,
            BLUE);
        for (const auto& collider : collisionBoxes) {
            DrawRectangleLines(collider.rect.x, collider.rect.y, collider.rect.width, collider.rect.height, RED);
        }
        EndMode2D();
        EndDrawing();
    }
    UnloadRenderTexture(mapFrameBuffer);
    CloseWindow();
    return 0;
}




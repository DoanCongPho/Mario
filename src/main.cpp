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

// Function to load collision boxes from a TMX file
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
    
    // Free the map when done
    tmx_map_free(map);
    
    return collisionBoxes;
}



bool IsTileCollidable(tmx_layer *layer, tmx_map *map, int x, int y);
bool CheckCollisionWithMap(Player *player, tmx_map *map, tmx_layer *collisionLayer);

Texture2D *LoadMapTexture(const char *fileName);

void UnloadMapTexture(Texture2D *tex);

void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf);
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
        .spawnPoint = {100.0f, 100.0f}, // Where the player spawns
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
        
        // Handle jumping
        if (IsKeyPressed(KEY_SPACE) && player.onGround) {
            player.velocity.y = -JUMP_VELOCITY;
            player.onGround = false;
        }
        
        // Calculate next position
        Vector2 nextPosition = {
            player.position.x + player.velocity.x * delta,
            player.position.y + player.velocity.y * delta
        };
        
        // Handle collisions
        Rectangle playerBox = {nextPosition.x, player.position.y, player.size.x, player.size.y};
        bool collisionDetected = false;
        bool groundCollisionDetected = false;
        
        // Check horizontal collisions
        for (const auto& collider : collisionBoxes) {
            if (CheckCollisionRecs(playerBox, collider.rect)) {
                if (player.velocity.x > 0) {
                    nextPosition.x = collider.rect.x - player.size.x;
                    player.onGround = false;
                    break;
                } else if (player.velocity.x < 0) {
                    nextPosition.x = collider.rect.x + collider.rect.width;
                    
                }
                player.velocity.x = 0;
                collisionDetected = true;
            }
        }
     
        // Update player position after horizontal collision check
        player.position.x = nextPosition.x;
        
        // Check vertical collisions
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
        
        // Update player position after vertical collision check
        player.position.y = nextPosition.y;
        
        // Update camera target
        camera.target = (Vector2){
            player.position.x + player.size.x / 2.0f,
            player.position.y + player.size.y / 2.0f
        };
        
        // Render
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
    
//    while (!WindowShouldClose())
//    {
//        const float delta = GetFrameTime();
//        if (!player.onGround) {
//            player.velocity.y += GRAVITY * GetFrameTime();
//        }
//        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
//            player.velocity.x = 600.0f; // Move right
//        }
//        else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
//            player.velocity.x = -600.0f; // Move left
//        }
//        else {
//            player.velocity.x *= 0.8f;
//            if (fabs(player.velocity.x) < 0.1f) {
//                player.velocity.x = 0.0f;
//            }
//        }
//
//        if (IsKeyPressed(KEY_SPACE) && player.onGround) {
//            player.velocity.y = -JUMP_VELOCITY;
//            player.onGround = false;
//        }
//        Vector2 nextPosition = {
//            player.position.x + player.velocity.x * GetFrameTime(),
//            player.position.y + player.velocity.y * GetFrameTime()
//        };
//        Rectangle playerBox = {nextPosition.x, nextPosition.y, player.size.x, player.size.y};
//
//        bool collisionDetected = false;
//        bool groundCollisionDetected = false;  // Mark ground collision
//        for (const auto& collider : collisionBoxes) {
//            if ((player.velocity.y) > 0 && CheckCollisionRecs(playerBox, collider.rect)) {
//                // Player is falling and hits the ground
//                player.velocity.y = 0; // Stop downward movement
//                nextPosition.y = collider.rect.y - player.size.y; // Place the player above the ground
//                player.onGround = true; // Set onGround to true
//                groundCollisionDetected = true; // Mark ground collision
//            }
//            else if (player.velocity.y < 0 && CheckCollisionRecs(playerBox, collider.rect)) {
//                // Player is jumping and hits a ceiling
//                player.velocity.y = GRAVITY*GetFrameTime(); // Stop upward movement
//                nextPosition.y = collider.rect.y + collider.rect.height; // Place the player below the ceiling
//                collisionDetected = true; // Detect collision but not on the ground
//            }
//
//        }
//        if (!groundCollisionDetected) {
//            player.onGround = false;
//        }
//        player.position = nextPosition;
//
//        camera.target = (Vector2){
//            player.position.x + player.size.x / 2.0f,
//            player.position.y + player.size.y / 2.0f
//        };
//
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//        BeginMode2D(camera);
//        DrawTextureRec(
//                       mapFrameBuffer.texture,
//                       (Rectangle){0.0f, 0.0f, static_cast<float>(mapFrameBuffer.texture.width), static_cast<float>(-mapFrameBuffer.texture.height)},
//                       (Vector2){0.0, 0.0},
//                       WHITE);
//        DrawRectangle(
//                      player.position.x,
//                      player.position.y,
//                      player.size.x,
//                      player.size.y,
//                      BLUE);
//        for (const auto& collider : collisionBoxes) {
//            DrawRectangleLines(collider.rect.x, collider.rect.y, collider.rect.width, collider.rect.height, RED);
//        }
//        EndMode2D();
//        EndDrawing();
//    }
    UnloadRenderTexture(mapFrameBuffer);
    CloseWindow();
    return 0;
}




Texture2D *LoadMapTexture(const char *fileName)
{
    Texture2D *tex = (Texture2D *)malloc(sizeof(Texture2D));
    if (tex != NULL)
    {
        *tex = LoadTexture(fileName);
        TraceLog(LOG_INFO, "TMX texture loaded from %s", fileName);
        return tex;
    }
    return NULL;
}
void UnloadMapTexture(Texture2D *tex)
{
    if (tex != NULL)
    {
        UnloadTexture(*tex);
        free(tex);
    }
}
void DrawTmxLayer(tmx_map *map, tmx_layer *layer)
{
    unsigned long row, col;
    unsigned int gid;
    unsigned int flip;
    tmx_tile *tile;
    unsigned int tile_width;
    unsigned int tile_height;
    Rectangle sourceRect;
    Rectangle destRect;
    Texture2D *tsTexture; // tileset texture
    float rotation = 0.0;
    Vector2 origin = {0.0, 0.0};
    
    for (row = 0; row < map->height; row++)
    {
        for (col = 0; col < map->width; col++)
        {
            gid = layer->content.gids[(row * map->width) + col];
            flip = gid & ~TMX_FLIP_BITS_REMOVAL;    // get flip operations from GID
            gid = gid & TMX_FLIP_BITS_REMOVAL;      // remove flip operations from GID to get tile ID
            tile = map->tiles[gid];
            if (tile != NULL)
            {

                if (tile->image != NULL)
                {
                    tsTexture = (Texture2D *)tile->image->resource_image;
                    tile_width = tile->image->width;
                    tile_height = tile->image->height;
                }
                else
                {
                    tsTexture = (Texture2D *)tile->tileset->image->resource_image;
                    tile_width = tile->tileset->tile_width;
                    tile_height = tile->tileset->tile_height;
                }
                
                sourceRect.x = tile->ul_x;
                sourceRect.y = tile->ul_y;
                sourceRect.width = destRect.width = tile_width;
                sourceRect.height = destRect.height = tile_height;
                destRect.x = col * tile_width;
                destRect.y = row * tile_height;
                // Deal with flips
                origin.x = 0.0;
                origin.y = 0.0;
                rotation = 0.0;
                switch(flip)
                {
                    case TMX_FLIPPED_DIAGONALLY:
                    {
                        sourceRect.height = -1 * sourceRect.height;
                        rotation = 90.0;
                    } break;
                    case TMX_FLIPPED_VERTICALLY:
                    {
                        sourceRect.height = -1 * sourceRect.height;
                    } break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        rotation = -90.0;
                    } break;
                    case TMX_FLIPPED_HORIZONTALLY:
                    {
                        sourceRect.width = -1 * sourceRect.width;
                    } break;
                    case  TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_HORIZONTALLY:
                    {
                        rotation = 90.0;
                    } break;
                    case TMX_FLIPPED_HORIZONTALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        rotation = 180.0;
                    } break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_HORIZONTALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        sourceRect.width = -1 * sourceRect.width;
                        rotation = 90.0;
                    } break;
                    default:
                    {
                        origin.x = 0.0;
                        origin.y = 0.0;
                        rotation = 0.0;
                    } break;
                }
                if (rotation != 0.0)
                {
                    origin.x = tile_width / 2;
                    origin.y = tile_height / 2;
                    destRect.x += tile_width / 2;
                    destRect.y += tile_height / 2;
                }
                DrawTexturePro(*tsTexture, sourceRect, destRect, origin, rotation, WHITE);
            }
        }
    }
}
void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf)
{
    tmx_layer *layer = NULL;
    tmx_img_load_func = (void *(*)(const char *))LoadMapTexture;
    tmx_img_free_func = (void (*)(void *))UnloadMapTexture;
    tmx_map *mapTmx = tmx_load(mapFileName);
    if (mapTmx == NULL) {
        tmx_perror("tmx_load");
        return;
    }
    *buf = LoadRenderTexture(mapTmx->width * mapTmx->tile_width, mapTmx->height * mapTmx->tile_height);
   
    
    BeginTextureMode(*buf);
    ClearBackground(SKYBLUE);

    layer = mapTmx->ly_head;
    while(layer)
    {
        if (layer->visible)
        {
            switch(layer->type)
            {
                case L_LAYER:
                {
                    TraceLog(LOG_INFO, "Render TMX layer \"%s\"", layer->name);
                    DrawTmxLayer(mapTmx, layer);
                } break;
                case L_GROUP:
                case L_OBJGR:
                case L_IMAGE:
                    
                case L_NONE:
                default:
                    break;
            }
        }
        layer = layer->next;
    }
    EndTextureMode();
    
    tmx_map_free(mapTmx);
}


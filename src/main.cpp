
#include <stdlib.h>
#include <iostream>
#include "raylib.h"
#include "tmx.h"
#include "ResourcesManager.hpp"
#include <vector>
#define TILE_SIZE 32
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 600.0f
constexpr float GRAVITY = 1200.0f;
constexpr float JUMP_VELOCITY = 600.0f;

typedef struct Player {
    Vector2 position;
    Vector2 velocity;
    bool onGround;
    Vector2 spawnPoint;
    Vector2 size;
    int currentFrame; // Current animation frame
    float frameTime;  // Time per frame
    float frameCounter; // Accumulated frame time
    bool faceRight;
} Player;

enum PlayerState {
    WALKING,
    RUNNING,
    JUMPING,
    STANDING
};
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
    int screenWidth = 800;
    int screenHeight = 640;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");
    loadAllAnimations();
    vector<Texture2D> runningTex = ResourcesManager::getInstance().getA("smallMarioRun");
    vector<Texture2D> walkingTex = ResourcesManager::getInstance().getA("smallMario");
    vector<Texture2D> jumpingTex = ResourcesManager::getInstance().getA("smallMarioJump");
    std::vector<CollisionBox> collisionBoxes = LoadCollisionData("Resources/Map1.tmx", "Collison");
    
    Player player = {
        .position = {100.0f, 100.0f},
        .velocity = {0.0f, 0.0f},
        .onGround = false,
        .spawnPoint = {100.0f, 100.0f},
        .size = {static_cast<float>(walkingTex[0].width), static_cast<float>(walkingTex[0].height)},
        .currentFrame = 0,
        .frameTime = 0.1f,
        .frameCounter = 0.0f,
        .faceRight = true
    };
    
    
    PlayerState playerState = WALKING;
    
    Camera2D camera;
    
    
    RenderTmxMapToFramebuf("Resources/Map1.tmx", &mapFrameBuffer);
    camera.target = (Vector2){ player.position.x, player.position.y };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0;
    camera.zoom = 1.0;
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        const float delta = GetFrameTime();

        // Apply gravity if not on the ground
       
       
        // Handle horizontal movement
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            player.velocity.x = 300.0f;
                playerState = WALKING;
            player.faceRight = true;
        } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            player.velocity.x = -300.0f;
            if (player.onGround)
                playerState = WALKING;
            player.faceRight = false;
        } else {
            player.velocity.x *= 0.8f; // Apply friction
            if (fabs(player.velocity.x) < 0.1f) {
                player.velocity.x = 0.0f;
                if (player.onGround)
                    playerState = STANDING;
                player.currentFrame = 0;
            }
        }

        // Handle jumping
        if ((IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_SPACE)) && player.onGround) {
            player.velocity.y = -JUMP_VELOCITY;
            player.onGround = false;
        }
        if (!player.onGround) {
            playerState = JUMPING;
            player.velocity.y += GRAVITY * delta;
        }
        // Update player frame based on state
        player.frameCounter += delta;
        if (player.frameCounter >= player.frameTime) {
            player.frameCounter = 0.0f;
            if (playerState == WALKING) {
                player.currentFrame = (player.currentFrame + 1) % walkingTex.size();
                player.size = {static_cast<float>(walkingTex[0].width), static_cast<float>(walkingTex[0].height)};
            } else if (playerState == JUMPING) {
                player.currentFrame = (player.currentFrame + 1) % jumpingTex.size();
                player.size = {static_cast<float>(jumpingTex[0].width), static_cast<float>(jumpingTex[0].height)};
            }
        }
        
        // Predict next position
        Vector2 nextPosition = {
            player.position.x + player.velocity.x * delta,
            player.position.y + player.velocity.y * delta
        };

        // Handle vertical collisions
        Rectangle verticalBox = {player.position.x, nextPosition.y, player.size.x, player.size.y};
        bool groundCollisionDetected = false;
         
        
        for (const auto& collider : collisionBoxes) {
            if (CheckCollisionRecs(verticalBox, collider.rect)) {
                if (player.velocity.y > 0) { // Falling
                    nextPosition.y = collider.rect.y - player.size.y; // Place player on top of the collider
                    player.onGround = true;
                    groundCollisionDetected = true;
                    if (fabs(player.velocity.x) < 0.1f) {
                        playerState = STANDING; // Stop walking if horizontal velocity is small
                    } else {
                        playerState = WALKING;
                    }
                }
                else if (player.velocity.y < 0) { // Jumping
                    nextPosition.y = collider.rect.y + collider.rect.height;
                    player.velocity.y = 0;
                }
            }
        }
        if (!groundCollisionDetected) {
            player.onGround = false;
        }

        player.position.y = nextPosition.y;

        // Handle horizontal collisions
        Rectangle horizontalBox = {nextPosition.x, player.position.y, player.size.x, player.size.y};

        for (const auto& collider : collisionBoxes) {
            if (CheckCollisionRecs(horizontalBox, collider.rect)) {
                if (player.velocity.x > 0) { // Moving right
                    nextPosition.x = collider.rect.x - player.size.x;
                } else if (player.velocity.x < 0) { // Moving left
                    nextPosition.x = collider.rect.x + collider.rect.width;
                }
                player.velocity.x = 0;
                break;
            }
        }

        // Update player position
        player.position.x = nextPosition.x;

        // Update camera position
        camera.target = (Vector2){
            player.position.x + player.size.x / 2.0f,
            player.position.y + player.size.y / 2.0f
        };

        // Rendering
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);

        // Draw map
        DrawTextureRec(
            mapFrameBuffer.texture,
            (Rectangle){0.0f, 0.0f, (float)mapFrameBuffer.texture.width, (float)-mapFrameBuffer.texture.height},
            (Vector2){0.0f, 0.0f},
            WHITE
        );

        // Select appropriate texture for the player
        Texture2D currentTexture;
        if(playerState == WALKING){
            currentTexture = walkingTex[player.currentFrame];
        }else if(playerState == STANDING){
            currentTexture = walkingTex[0];
        }else
            currentTexture  = jumpingTex[player.currentFrame];
        Rectangle sourceRect = {
            0.0f, 0.0f,
            (float)(player.faceRight ? currentTexture.width : -currentTexture.width),
            (float)currentTexture.height
        };

        // Draw player
        DrawTextureRec(
            currentTexture,
            sourceRect,
            player.position,
            WHITE
        );

        // Draw collision boxes for debugging
        for (const auto& collider : collisionBoxes) {
            DrawRectangleLines(
                (int)collider.rect.x,
                (int)collider.rect.y,
                (int)collider.rect.width,
                (int)collider.rect.height,
                RED
            );
        }

        EndMode2D();
        EndDrawing();
    }

    UnloadRenderTexture(mapFrameBuffer);
    CloseWindow();
    return 0;
}




#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <raylib.h>
#include "CollisionBox.hpp"

class Player {
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration; // New acceleration vector
    bool onGround;
    Vector2 size;
    int currentFrame;
    float frameTime;
    float frameCounter;
    bool faceRight;
    
    enum State {
        WALKING,
        RUNNING,
        JUMPING,
        STANDING,
        TRANSFORMING
    };
    void StartTransformation(std::vector<Texture2D>& newWalkingTextures, std::vector<Texture2D>& newJumpingTextures,  std::vector<Texture2D>& newRunningTextures);
    Player(const Vector2& spawnPoint, std::vector<Texture2D>& walkingTextures, std::vector<Texture2D>& jumpingTextures,  std::vector<Texture2D>&runningTextures,
            std::vector<Texture2D>& transformationTextures);
    void Update(float delta, const std::vector<CollisionBox>& collisionBoxes);
    void Draw() const;
    
    State GetState() const;
    void SetState(State newState);
    
private:
    float transformationFrameDelay = 0.35f; 
      float transformationTimer = 0.0f;
    Vector2 spawnPoint;
    State state;
    std::vector<Texture2D>& walkingTextures;
    std::vector<Texture2D>& jumpingTextures;
    std::vector<Texture2D>& runningTextures;
    std::vector<Texture2D>& transformationTextures;
    
    void HandleMovement(float delta);
    void HandleCollisions(float delta, const std::vector<CollisionBox>& collisionBoxes);
    void UpdateFrame(float delta);
};

#endif // PLAYER_HPP

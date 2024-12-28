#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "CollisionBox.hpp"
#include "Fireball.hpp"

constexpr float GRAVITY = 1200.0f;


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
    bool fireballsActive;
    enum State {
        WALKING,
        RUNNING,
        JUMPING,
        STANDING,
        TRANSFORMING,
    };
    void StartTransformation(std::vector<Texture2D>& newWalkingTextures, std::vector<Texture2D>& newJumpingTextures,  std::vector<Texture2D>& newRunningTextures);
    void fireballsAvaiable();
    
    Player(const Vector2& spawnPoint, std::vector<Texture2D>& walkingTextures, std::vector<Texture2D>& jumpingTextures,  std::vector<Texture2D>&runningTextures,
        std::vector<Texture2D>& transformationTextures,
           std::vector<Texture2D>& fireballsTexture);
    void Update(float delta, const std::vector<CollisionBox>& collisionBoxes);
    void Draw() const;
    State GetState() const;
    void SetState(State newState);
    void ActivateFireballs();
    void DeactivateFireballs();

    Vector2 &GetPosition();
    Vector2 &GetSize();
    Vector2 &GetVelocity();
private:
    float transformationFrameDelay = 0.35f;
    float transformationTimer = 0.0f;
    Vector2 spawnPoint;
    State state;
    std::vector<Fireball> activeFireballs; 
    std::vector<Texture2D>& walkingTextures;
    std::vector<Texture2D>& jumpingTextures;
    std::vector<Texture2D>& runningTextures;
    std::vector<Texture2D>& transformationTextures;
    std::vector<Texture2D>& fireballsTextures;
    void HandleMovement(float delta);
    void HandleCollisions(float delta, const std::vector<CollisionBox>& collisionBoxes);
    void UpdateFrame(float delta);
    void DrawFireballs() const;
    void HandleFireballs(float delta, const std::vector<CollisionBox>& collisionBoxes);
};

#endif // PLAYER_HPP

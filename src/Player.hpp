#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <raylib.h>
#include "CollisionBox.hpp"
class Player {
public:
    Vector2 position;
    Vector2 velocity;
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
        STANDING
    };

    Player(const Vector2& spawnPoint, const std::vector<Texture2D>& walkingTextures, const std::vector<Texture2D>& jumpingTextures);
    void Update(float delta, const std::vector<CollisionBox>& collisionBoxes);
    void Draw() const;

    State GetState() const;
    void SetState(State newState);

private:
    Vector2 spawnPoint;
    State state;
    const std::vector<Texture2D>& walkingTextures;
    const std::vector<Texture2D>& jumpingTextures;

    void HandleMovement(float delta);
    void HandleCollisions(float delta, const std::vector<CollisionBox>& collisionBoxes);
    void UpdateFrame(float delta);
};

#endif // PLAYER_HPP

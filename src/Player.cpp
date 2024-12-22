#include "Player.hpp"
#include <cmath>

constexpr float GRAVITY = 1200.0f;
constexpr float JUMP_VELOCITY = 600.0f;

Player::Player(const Vector2& spawnPoint, const std::vector<Texture2D>& walkingTextures, const std::vector<Texture2D>& jumpingTextures)
: spawnPoint(spawnPoint),
walkingTextures(walkingTextures),
jumpingTextures(jumpingTextures),
position(spawnPoint),
velocity({0, 0}),
onGround(false),
size({(float)walkingTextures[0].width, (float)walkingTextures[0].height}),
currentFrame(0),
frameTime(0.1f),
frameCounter(0.0f),
faceRight(true),
state(STANDING) {}
void Player::Update(float delta, const std::vector<CollisionBox>& collisionBoxes) {
    HandleMovement(delta);
    HandleCollisions(delta, collisionBoxes);
    UpdateFrame(delta);
}
void Player::HandleMovement(float delta) {
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        velocity.x = 300.0f;
        state = WALKING;
        faceRight = true;
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        velocity.x = -300.0f;
        state = WALKING;
        faceRight = false;
    } else {
        velocity.x *= 0.8f;
        if (std::fabs(velocity.x) < 0.1f) {
            velocity.x = 0.0f;
            if (onGround) {
                state = STANDING;
                currentFrame = 0;
            }
        }
    }
    if ((IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_SPACE)) && onGround) {
        velocity.y = -JUMP_VELOCITY;
        onGround = false;
    }
    if (!onGround) {
        state = JUMPING;
        velocity.y += GRAVITY * delta;
    }
}

void Player::HandleCollisions(float delta, const std::vector<CollisionBox>& collisionBoxes) {
    Vector2 nextPosition = {
        position.x + velocity.x * delta,
        position.y + velocity.y * delta
    };
    
    Rectangle verticalBox = {position.x, nextPosition.y, size.x, size.y};
    bool groundCollisionDetected = false;
    for (const auto& box : collisionBoxes) {
        if (CheckCollisionRecs(verticalBox, box.rect)) {
            if (velocity.y > 0) { 
                nextPosition.y = box.rect.y - size.y;
                onGround = true;
                groundCollisionDetected = true;
            }else if (velocity.y < 0) {
                nextPosition.y = box.rect.y + box.rect.height;
                velocity.y = 0;
            }
        }
    }
    if (!groundCollisionDetected) {
        onGround = false;
    }
    position.y = nextPosition.y;
    Rectangle horizontalBox = {nextPosition.x, position.y, size.x, size.y};
    for (const auto& box : collisionBoxes) {
        if (CheckCollisionRecs(horizontalBox, box.rect)) {
            if (velocity.x > 0) {
                nextPosition.x = box.rect.x - size.x;
            } else if (velocity.x < 0) {
                nextPosition.x = box.rect.x + box.rect.width;
            }
            velocity.x = 0;
            break;
        }
    }
    position.x = nextPosition.x;
}

void Player::UpdateFrame(float delta) {
    frameCounter += delta;
    if (frameCounter >= frameTime) {
        frameCounter = 0.0f;
        if (state == WALKING) {
            currentFrame = (currentFrame + 1) % walkingTextures.size();
            size = {(float)walkingTextures[0].width, (float)walkingTextures[0].height};
        } else if (state == JUMPING) {
            currentFrame = (currentFrame + 1) % jumpingTextures.size();
            size = {(float)jumpingTextures[0].width, (float)jumpingTextures[0].height};
        }
    }
}

void Player::Draw() const {
    Texture2D currentTexture;
    if(state == WALKING){
        currentTexture = walkingTextures[currentFrame];
    }else if(state == STANDING){
        currentTexture = walkingTextures[0];
    }else
        currentTexture  = jumpingTextures[0];
    Rectangle sourceRect = {
        0.0f, 0.0f,
        (float)(faceRight ? currentTexture.width : -currentTexture.width),
        (float)currentTexture.height
    };
    DrawTextureRec(
                   currentTexture,
                   sourceRect,
                   position, 
                   WHITE
                   );
}

Player::State Player::GetState() const {
    return state;
}

void Player::SetState(Player::State newState) {
    state = newState;
}

#include "Player.hpp"
#include <cmath>

constexpr float GRAVITY = 1200.0f;
constexpr float JUMP_VELOCITY = 600.0f;
constexpr float ACCELERATION = 600.0f; // Acceleration value
constexpr float MAX_VELOCITY = 300.0f; // Max walking velocity
constexpr float RUNNING_VELOCITY = 500.0f;
constexpr float TRANSFORMATION_FRAME_TIME = 0.3f;
Player::Player(const Vector2& spawnPoint, std::vector<Texture2D>& walkingTextures, std::vector<Texture2D>& jumpingTextures,  std::vector<Texture2D>&runningTextures,
               std::vector<Texture2D>& transformationTextures,
               std::vector<Texture2D>& fireballsTexture)
: spawnPoint(spawnPoint),
walkingTextures(walkingTextures),
jumpingTextures(jumpingTextures),
runningTextures(runningTextures),
transformationTextures(transformationTextures),
fireballsTextures(fireballsTexture),
fireballsActive(false),
position(spawnPoint),
velocity({0, 0}),
acceleration({0, 0}), // Initialize acceleration
onGround(false),
size({(float)walkingTextures[0].width, (float)walkingTextures[0].height}),
currentFrame(0),
frameTime(0.2f),
frameCounter(0.0f),
faceRight(true),
state(STANDING)
{}
void Player::ActivateFireballs() {
    fireballsActive = true;
    
}

void Player::DeactivateFireballs() {
    fireballsActive = false;
}

void Player::HandleFireballs(float deltaTime, const std::vector<CollisionBox>& collisionBoxes) {
    if (fireballsActive) {
        // Create a new fireball when the F key is pressed
        if (IsKeyPressed(KEY_F)) {
            Vector2 fireballVelocity = {faceRight ? 500.0f : -500.0f, 0.0f};
            Vector2 fireballPosition = {position.x + (faceRight ? size.x : -20.0f), position.y + size.y / 2};
            activeFireballs.emplace_back(fireballPosition, fireballVelocity, fireballsTextures);
        }
        
        // Update and remove expired or off-screen fireballs
    }
    for (auto it = activeFireballs.begin(); it != activeFireballs.end();) {
        
        bool collided = false;
        // Check for collisions with each collision box
        for (const auto& box : collisionBoxes) {
            if (CheckCollisionRecs(it->GetBoundingBox(), box.rect)) {
                // Handle the collision logic here, e.g., fireball gets destroyed on collision
                collided = true;
                break;
            }
        }
        
        it->Update(deltaTime);
        if (collided || it->HasExpired()) {
            it = activeFireballs.erase(it);
        } else {
            ++it;
        }
    }
}

void Player::DrawFireballs() const {
    for (const auto& fireball : activeFireballs) {
        fireball.Draw();
    }
}



void Player::Update(float delta, const std::vector<CollisionBox>& collisionBoxes) {
    if(!(state == TRANSFORMING)){
        HandleMovement(delta);
        HandleFireballs(delta, collisionBoxes);
        HandleCollisions(delta, collisionBoxes);
    }
    
    UpdateFrame(delta);
}
void Player::StartTransformation( std::vector<Texture2D>& newWalkingTextures,  std::vector<Texture2D>& newJumpingTextures,  std::vector<Texture2D>& newRunningTextures) {
    state = TRANSFORMING;
    currentFrame = 0;
    frameCounter = 0.0f;
    runningTextures.clear();
    for(auto it: newRunningTextures){
        runningTextures.push_back(it);
    }
    jumpingTextures.clear();
    for(auto it: newJumpingTextures){
        jumpingTextures.push_back(it);
    }
    walkingTextures.clear();
    for(auto it: newWalkingTextures){
        walkingTextures.push_back(it);
    }
    Vector2 preSize = size;
    size = {(float)transformationTextures[currentFrame].width, (float)transformationTextures[currentFrame].height};
    position.y -= fabs(size.y - preSize.y);
}
void Player::HandleMovement(float delta) {
    acceleration = {0.0f, 0.0f}; // Reset acceleration each frame
    float maxVelocity = MAX_VELOCITY;
    if (IsKeyDown(KEY_LEFT_SHIFT) && (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))) {
        maxVelocity = RUNNING_VELOCITY;
        acceleration.x = 1.1*ACCELERATION;
        state = RUNNING;
    }else if (IsKeyDown(KEY_LEFT_SHIFT) && (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))) {
        maxVelocity = RUNNING_VELOCITY;
        acceleration.x = -1.1*ACCELERATION;
        state = RUNNING;
    }else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        acceleration.x = ACCELERATION;
        faceRight = true;
        state = WALKING;
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        acceleration.x = -ACCELERATION;
        faceRight = false;
        state = WALKING;
    } else {
        acceleration.x = -velocity.x * 5.0f; // Friction factor
        if (std::fabs(velocity.x) < 10.0f) {
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
        acceleration.y = GRAVITY;
        state = JUMPING;
    }
    velocity.x += acceleration.x * delta;
    velocity.y += acceleration.y * delta;
    velocity.x = std::clamp(velocity.x, -MAX_VELOCITY, MAX_VELOCITY);
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
            } else if (velocity.y < 0) {
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
    if (state == TRANSFORMING) {
        if (frameCounter >= TRANSFORMATION_FRAME_TIME) {
            frameCounter = 0.0f;
            if (currentFrame < transformationTextures.size()-1) {
                currentFrame++;
                Vector2 preSize = size;
                size = {(float)transformationTextures[currentFrame].width, (float)transformationTextures[currentFrame].height};
                position.y += (size.y - preSize.y)/2.0f;
            } else {
                currentFrame = 0;
                size = {(float)runningTextures[0].width, (float)runningTextures[0].height};
                state = STANDING;
            }
            
        }
    }
    // Handle other states (walking, jumping, running)
    else if (frameCounter >= frameTime) {
        frameCounter = 0.0f;
        if (state == WALKING) {
            currentFrame = (currentFrame + 1) % walkingTextures.size();
            size = {(float)walkingTextures[0].width, (float)walkingTextures[0].height};
        } else if (state == JUMPING) {
            currentFrame = (currentFrame + 1) % jumpingTextures.size();
            size = {(float)jumpingTextures[0].width, (float)jumpingTextures[0].height};
        } else if (state == RUNNING) {
            currentFrame = (currentFrame + 1) % runningTextures.size();
            size = {(float)runningTextures[0].width, (float)runningTextures[0].height};
        }
    }
}

void Player::Draw() const {
    
    Texture2D currentTexture;
    if (state == TRANSFORMING) {
        currentTexture = transformationTextures[currentFrame];
    } else if(state == RUNNING){
        currentTexture = runningTextures[currentFrame];
    }else if (state == WALKING) {
        currentTexture = walkingTextures[currentFrame];
    } else if (state == STANDING) {
        currentTexture = walkingTextures[0];
    } else {
        currentTexture = jumpingTextures[0];
    }
    Rectangle sourceRect = {
        0.0f, 0.0f,
        (float)(faceRight ? currentTexture.width : -currentTexture.width),
        (float)currentTexture.height
    };
    Color c = WHITE;
    if(fireballsActive)
        c = ORANGE;
    DrawTextureRec(currentTexture, sourceRect, position, c);
    DrawFireballs();
}

Player::State Player::GetState() const {
    return state;
}

void Player::SetState(Player::State newState) {
    state = newState;
}

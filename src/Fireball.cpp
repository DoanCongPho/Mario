#include "Fireball.hpp"

Fireball::Fireball(Vector2 startPosition, Vector2 startVelocity, std::vector<Texture2D>& fireballTextures)
    : position(startPosition),
      velocity(startVelocity),
      textures(fireballTextures),
      currentFrame(0),
      frameTime(0.1f),
      frameCounter(0.0f),
      lifetime(5.0f) {}

void Fireball::Update(float deltaTime) {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    frameCounter += deltaTime;
    if (frameCounter >= frameTime) {
        frameCounter = 0.0f;
        currentFrame = (currentFrame + 1) % textures.size();
    }

    lifetime -= deltaTime;
}

void Fireball::Draw() const {
    if (!textures.empty()) {
        DrawTexture(textures[currentFrame], position.x, position.y, WHITE);
    }
}

bool Fireball::IsOffScreen(int screenWidth) const {
    return (position.x < 0 || position.x > screenWidth);
}

bool Fireball::HasExpired() const {
    return lifetime <= 0.0f;
}

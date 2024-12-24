#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include "raylib.h"
#include <vector>

class Fireball {
private:
    Vector2 position;
    Vector2 velocity;
    std::vector<Texture2D> textures; // Vector of textures for animation
    int currentFrame;                // Current animation frame
    float frameTime;                 // Time per frame
    float frameCounter;              // Counter to switch frames
    float lifetime;                  // Time before fireball disappears

public:
    Fireball(Vector2 startPosition, Vector2 startVelocity, std::vector<Texture2D>& fireballTextures);
    void Update(float deltaTime);
    void Draw() const;
    bool IsOffScreen(int screenWidth) const;
    bool HasExpired() const;
    Rectangle GetBoundingBox(){
        return Rectangle{position.x, position.y, static_cast<float>(textures[0].width), static_cast<float>(textures[0].height)}; 
    }
    Vector2 GetPosition() const { return position; }
};

#endif // FIREBALL_HPP

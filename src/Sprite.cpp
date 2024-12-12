#include "Sprite.hpp"

Sprite::Sprite(const string& texturePath, float x, float y) {
    texture = LoadTexture(texturePath.c_str());
    pos = { x, y };
    dim.x = (float)texture.width;
    dim.y = (float)texture.height;
    vel = { 0.0f, 0.0f };
}

Sprite::~Sprite() {
    UnloadTexture(texture);
}

void Sprite::update(float deltaTime) {
    pos.x += vel.x * deltaTime;
    pos.y += vel.y * deltaTime;
}

void Sprite::draw() const {
    DrawTexture(texture, pos.x, pos.y, WHITE);
}

Vector2 Sprite::getPos() const {
    return pos;
}

void Sprite::setPos(float x, float y) {
    pos.x = x;
    pos.y = y;
}

void Sprite::setVel(float vx, float vy) {
    vel.x = vx;
    vel.y = vy;
}

Vector2 Sprite::getVel() const {
    return vel;
}

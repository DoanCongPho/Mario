#include "Sprite.hpp"

Sprite::Sprite()
    : pos(Vector2(0, 0)), dim(Vector2(0, 0)), vel(Vector2(0, 0)), angle(0),
      hitsToDie(0), earnedPoints(0), isFacingRight(false), maxFrames(0) {}

Sprite::Sprite(const string &texturePath, float x, float y) {
  texture = LoadTexture(texturePath.c_str());
  pos = {x, y};
  dim.x = (float)texture.width;
  dim.y = (float)texture.height;
  vel = {0.0f, 0.0f};
  cpNorth = CollisionProbe(pos.x, pos.y, dim.x, 5);
}

Sprite::~Sprite() { UnloadTexture(texture); }

void Sprite::update(float deltaTime) {
  pos.x += vel.x * deltaTime;
  pos.y += vel.y * deltaTime;
}

void Sprite::draw() const { DrawTexture(texture, pos.x, pos.y, WHITE); }

Vector2 &Sprite::getPos() { return pos; }

void Sprite::setPos(float x, float y) {
  pos.x = x;
  pos.y = y;
}

void Sprite::setVel(float vx, float vy) {
  vel.x = vx;
  vel.y = vy;
}
Rectangle Sprite::getRect() const {
  return Rectangle(pos.x, pos.y, dim.x, dim.y);
}

Vector2 &Sprite::getVel() { return vel; }

CollisionType Sprite::checkCollision(const Sprite *sprite) const {
  if (state == SPRITE_STATE_NOT_COLLIDABLE ||
      secondaryState == SPRITE_STATE_NOT_COLLIDABLE ||
      sprite->state == SPRITE_STATE_NOT_COLLIDABLE ||
      sprite->secondaryState == SPRITE_STATE_NOT_COLLIDABLE) {
    return COLLISION_TYPE_NONE;
  }

  auto rect = sprite->getRect();

  if (cpNorth.collided(rect)) {
    return COLLISION_TYPE_NORTH;
  }

  if (cpSouth.collided(rect)) {
    return COLLISION_TYPE_SOUTH;
  }

  if (cpEast.collided(rect)) {
    return COLLISION_TYPE_EAST;
  }

  if (cpWest.collided(rect)) {
    return COLLISION_TYPE_WEST;
  }

  return COLLISION_TYPE_NONE;
}

void Sprite::updateCollisionProbes() {
  cpNorth.setX(pos.x + dim.x / 2 - cpNorth.getWidth() / 2);
  cpNorth.setY(pos.y);

  cpSouth.setX(pos.x + dim.x / 2 - cpSouth.getWidth() / 2);
  cpSouth.setY(pos.y + dim.y - cpSouth.getHeight());

  cpEast.setX(pos.x + dim.x - cpEast.getWidth());
  cpEast.setY(pos.y + dim.y / 2 - cpEast.getHeight() / 2);

  cpWest.setX(pos.x);
  cpWest.setY(pos.y + dim.y / 2 - cpWest.getHeight() / 2);
}

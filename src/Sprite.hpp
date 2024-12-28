#ifndef Sprite_hpp
#define Sprite_hpp

#include "CollisionBox.hpp"
#include "CollisionProbe.h"
#include "CollisionType.h"
#include "raylib.h"
#include <iostream>

#include "SpriteState.h"

using namespace std;

class Sprite {
protected:
  Vector2 pos;
  Vector2 dim;
  Vector2 vel;
  float angle;
  int hitsToDie;
  int earnedPoints;

  float frameTime;
  float frameAcum;

  bool isFacingRight;
  int currentFrame;
  int maxFrames;
  Texture2D texture;

  SpriteState state = SPRITE_STATE_IDLE;
  SpriteState secondaryState = SPRITE_STATE_NONE;

  CollisionProbe cpNorth;
  CollisionProbe cpSouth;
  CollisionProbe cpEast;
  CollisionProbe cpWest;

public:
  Sprite();
  Sprite(const string &texturePath, float x, float y);
  virtual ~Sprite();

  virtual void update(float deltaTime, const std::vector<CollisionBox>& collisionBoxes);
  virtual void draw() const;

  Vector2 &getPos();
  void setPos(float x, float y);

  Vector2 &getVel();
  void setVel(float vx, float vy);

  Rectangle getRect() const;

  CollisionType checkCollision(const Sprite *sprite) const;
  CollisionType checkCollision(const Rectangle& rect) const;
  virtual void updateCollisionProbes();

  SpriteState getState() { return state; }
  SpriteState getSecondaryState() { return secondaryState; }
};

#endif

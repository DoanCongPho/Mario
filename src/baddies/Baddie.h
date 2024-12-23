//
// Created by Administrator on 12/23/2024.
//

#ifndef BADDIE_H
#define BADDIE_H

#include "../Player.hpp"
#include "../Sprite.hpp"

class Baddie : public Sprite {
protected:
  float dyingFrameAcum;
  float dyingFrameTime;
  int maxDyingFrames;
  int currentDyingFrame;
  float pointsFrameAcum;
  float pointsFrameTime;
  Vector2 posOnDying;

public:
  Baddie();
  ~Baddie() override = default;

  void update(float deltaTime) override;
  virtual void updatePosition(float deltaTime);

  void draw() const override = 0;
  void activateWithPlayerProximity(Player &player);

  virtual void onHit();
  virtual void onDying();
  virtual void onSouthCollision();
  virtual void followTheLeader(Sprite *sprite);
};

#endif // BADDIE_H

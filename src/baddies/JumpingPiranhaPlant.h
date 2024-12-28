//
// Created by Administrator on 12/24/2024.
//

#ifndef JUMPINGPIRANHAPLANT_H
#define JUMPINGPIRANHAPLANT_H
#include "Baddie.h"

class JumpingPiranhaPlant : public Baddie {
private:
  bool waiting = false;
  bool goingUp = true;
  float waitAcum = 0;
  float waitTime = 0.8;
  float minY = 0;
  float maxY = 0;
  float currentVelocityUp = -400;
  float velocityUp = -400;
  float velocityDown = 80;

public:
  JumpingPiranhaPlant(Vector2 position, Vector2 dimension, Vector2 velocity,
                      Color color);
  ~JumpingPiranhaPlant() override = default;

  void updatePosition(float deltaTime, const std::vector<CollisionBox>& collisionBoxes) override;
};

#endif // JUMPINGPIRANHAPLANT_H

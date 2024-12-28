//
// Created by Administrator on 12/24/2024.
//

#ifndef MONTYMOLE_H
#define MONTYMOLE_H
#include "Baddie.h"

class MontyMole : public Baddie {
private:
  float jumpTimeAcum = 0;
  int jumpTime;
  int maxJumpTime = 6;

public:
  MontyMole(Vector2 position, Vector2 dimension, Vector2 velocity, Color color);
  ~MontyMole() override = default;

  void updatePosition(float deltaTime, const std::vector<CollisionBox>& collisionBoxes) override;
  void followTheLeader(Sprite *sprite) override;
};

#endif // MONTYMOLE_H

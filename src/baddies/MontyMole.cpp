//
// Created by Administrator on 12/24/2024.
//

#include "MontyMole.h"

MontyMole::MontyMole(Vector2 position, Vector2 dimension, Vector2 velocity,
                     Color color) {
  pos = position;
  dim = dimension;
  vel = velocity;
  maxFrames = 2;
  textureNameTemplate = "MontyMole_%d";

  jumpTime = GetRandomValue(2, maxJumpTime);
}

void MontyMole::updatePosition(const float deltaTime) {
  jumpTimeAcum += deltaTime;

  if (jumpTimeAcum >= static_cast<float>(jumpTime)) {
    jumpTimeAcum = 0;
    jumpTime = GetRandomValue(2, maxJumpTime);
    vel.y = -200;
  }

  Baddie::updatePosition(deltaTime);
}
void MontyMole::followTheLeader(Sprite *sprite) {
  if (pos.x < sprite->getPos().x - 60) {
    vel.x = std::abs(vel.x);
  } else if (pos.x > sprite->getPos().x + 60) {
    vel.x = -std::abs(vel.x);
  }
}
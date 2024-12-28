//
// Created by Administrator on 12/24/2024.
//

#include "JumpingPiranhaPlant.h"
JumpingPiranhaPlant::JumpingPiranhaPlant(Vector2 position, Vector2 dimension,
                                         Vector2 velocity, Color color) {
  pos = position;
  dim = dimension;
  vel = velocity;
  affectedByGravity = false;
  minY = pos.y - dim.y * 4;
  maxY = pos.y;
  maxFrames = 4;
  textureNameTemplate = "JumpingPiranhaPlant_%d";
  secondaryState = SPRITE_STATE_INVULNERABLE;
}

void JumpingPiranhaPlant::updatePosition(float deltaTime) {
  if (state != SPRITE_STATE_ACTIVE) {
    Baddie::updatePosition(deltaTime);
    return;
  }

  if (waiting) {
    waitAcum += deltaTime;

    if (waitAcum >= waitTime) {
      waitAcum = 0;
      waiting = false;
    }
  } else {
    if (goingUp) {
      pos.y += currentVelocityUp * deltaTime;

      if (currentVelocityUp < velocityUp * 0.1) {
        currentVelocityUp *= 0.96;
      }
    } else {
      pos.y += velocityDown * deltaTime;
    }

    if (pos.y < minY) {
      pos.y = minY;
      goingUp = false;
      waiting = true;
    } else if (pos.y > maxY) {
      pos.y = maxY;
      goingUp = true;
      currentVelocityUp = velocityUp;
      waiting = true;
    }
  }
}

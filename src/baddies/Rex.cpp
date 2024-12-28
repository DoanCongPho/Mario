//
// Created by Administrator on 12/24/2024.
//

#include "Rex.h"

Rex::Rex(Vector2 position, Vector2 dimension, Vector2 velocity, Color color) {
  pos = position;
  dim = dimension;
  vel = velocity;
  hitsToDie = 2;
  maxFrames = 2;
  animationTextureName = "rex2";
}

void Rex::onHit() {
  // Reset all dying timers
  dyingFrameAcum = 0;
  dyingFrameTime = 0;
  pointsFrameAcum = 0;

  // If the Rex has 2 lives, transform it into the smaller variant
  if (hitsToDie == 2) {
    dim.x = 32;
    dim.y = 32;
    pos.x += 32;
    vel.x *= 2;
    frameTime /= 2;

    state = SPRITE_STATE_HIT;
    animationTextureName = "rex1";

    updateCollisionProbes();
  }

  Baddie::onHit();
}
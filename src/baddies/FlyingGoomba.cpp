//
// Created by Administrator on 12/24/2024.
//

#include "FlyingGoomba.h"
FlyingGoomba::FlyingGoomba(Vector2 position, Vector2 dimension,
                           Vector2 velocity, Color color) {
  pos = position;
  dim = dimension;
  vel = velocity;
  maxFrames = 4;
  hitsToDie = 2;
  textureNameTemplate = "FlyingGoomba_%d";
}

void FlyingGoomba::updateCollisionProbes() {
  Baddie::updateCollisionProbes();

  cpNorth.setY(pos.y + (hitsToDie == 2 ? 14.0f : 0.0f));
}

void FlyingGoomba::onHit() {
  // Reset all dying timers
  dyingFrameAcum = 0;
  dyingFrameTime = 0;
  pointsFrameAcum = 0;

  if (hitsToDie == 2) {
    // If a flying goomba is hit, it transforms into a normal goomba
    state = SPRITE_STATE_HIT;

    dim.x = 32;
    dim.y = 32;
    pos.y += 18;

    maxFrames = 2;
    currentFrame = 0;
    frameAcum = 0;
    textureNameTemplate = "Goomba_%d";

    updateCollisionProbes();
  }

  Baddie::onHit();
}

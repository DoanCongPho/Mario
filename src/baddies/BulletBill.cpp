//
// Created by Administrator on 12/24/2024.
//

#include "BulletBill.h"

BulletBill::BulletBill(Vector2 position, Vector2 dimension, Vector2 velocity,
                       Color color) {
  pos = position;
  dim = dimension;
  vel = velocity;
  affectedByGravity = false;
  maxFrames = 1;
  textureNameTemplate = "BulletBill_%d";
  secondaryState = SPRITE_STATE_NOT_COLLIDABLE;
}

void BulletBill::onDying() {
  affectedByGravity = true;
  Baddie::onDying();
}
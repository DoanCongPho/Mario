//
// Created by Administrator on 12/23/2024.
//

#include "BanzaiBill.h"

#include "../ResourcesManager.hpp"

BanzaiBill::BanzaiBill(Vector2 position, Vector2 dimensions, Vector2 velocity,
                       Color color) {
  pos = position;
  dim = dimensions;
  vel = velocity;
  affectedByGravity = false;
  maxFrames = 1;
  textureNameTemplate = "BanzaiBill_%d";
}

void BanzaiBill::onDying() {
  affectedByGravity = true;

  Baddie::onDying();
}

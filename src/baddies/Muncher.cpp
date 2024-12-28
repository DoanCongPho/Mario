//
// Created by Administrator on 12/24/2024.
//

#include "Muncher.h"

Muncher::Muncher(Vector2 position, Vector2 dimension, Vector2 velocity,
                 Color color) {
  pos = position;
  dim = dimension;
  vel = Vector2 { 0, 0 };
  maxFrames = 2;
  textureNameTemplate = "Muncher_%d";
  state = SPRITE_STATE_INVULNERABLE;
}

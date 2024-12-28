//
// Created by Administrator on 12/24/2024.
//

#include "Goomba.h"

Goomba::Goomba(Vector2 position, Vector2 dimension, Vector2 velocity,
               Color color) {
  pos = position;
  dim = dimension;
  vel = velocity;
  maxFrames = 2;
  textureNameTemplate = "Goomba_%d";
}

//
// Created by Administrator on 12/24/2024.
//

#include "BobOmb.h"

BobOmb::BobOmb(Vector2 position, Vector2 dimensions, Vector2 velocity,
               Color color) {
  pos = position;
  dim = dimensions;
  vel = velocity;
  maxFrames = 2;
  animationTextureName = "bobomb";
}
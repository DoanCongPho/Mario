//
// Created by Administrator on 12/24/2024.
//

#include "BuzzyBeetle.h"

BuzzyBeetle::BuzzyBeetle(Vector2 position, Vector2 dimensions, Vector2 velocity,
                         Color color) {
  pos = position;
  dim = dimensions;
  vel = velocity;
  maxFrames = 2;
  animationTextureName = "buzzyBeetle";
  textureNameTemplate = "BuzzyBeetle_%d";
}
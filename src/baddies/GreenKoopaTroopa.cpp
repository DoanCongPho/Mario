//
// Created by Administrator on 12/24/2024.
//

#include "GreenKoopaTroopa.h"

GreenKoopaTroopa::GreenKoopaTroopa(Vector2 position, Vector2 dimension,
                                   Vector2 velocity, Color color) {
  pos = position;
  dim = dimension;
  vel = velocity;
  maxFrames = 2;
  animationTextureName = "greenKoopaTroopa";
  textureNameTemplate = "GreenKoopaTroopa_%d";
}

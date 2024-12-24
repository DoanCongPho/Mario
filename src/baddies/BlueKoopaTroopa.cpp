//
// Created by Administrator on 12/24/2024.
//

#include "BlueKoopaTroopa.h"

#include "../ResourcesManager.hpp"

BlueKoopaTroopa::BlueKoopaTroopa(Vector2 position, Vector2 dimensions,
                                 Vector2 velocity, Color color) {
  pos = position;
  dim = dimensions;
  vel = velocity;
  maxFrames = 2;
  textureNameTemplate = "BlueKoopaTroopa_%d";
}

//
// Created by Administrator on 12/23/2024.
//

#include "CollisionProbe.h"

bool CollisionProbe::collided(Rectangle &other) const {
  return CheckCollisionRecs(rect, other);
}
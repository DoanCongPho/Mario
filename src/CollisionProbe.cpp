//
// Created by Administrator on 12/23/2024.
//

#include "CollisionProbe.h"

bool CollisionProbe::collided(const Rectangle &other) const {
  return CheckCollisionRecs(rect, other);
}

void CollisionProbe::draw() const {
  DrawRectangle(rect.x, rect.y, rect.width, rect.height, color);
}
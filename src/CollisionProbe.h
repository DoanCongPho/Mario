//
// Created by Administrator on 12/23/2024.
//

#ifndef COLLISIONPROBE_H
#define COLLISIONPROBE_H
#include "CollisionType.h"
#include "raylib.h"

class CollisionProbe {
private:
  Rectangle rect;
  Color color = WHITE;

public:
  CollisionProbe() : rect(Rectangle { 0, 0, 5, 5 }) {}
  explicit CollisionProbe(const Rectangle &r) : rect(r) {}
  CollisionProbe(const float x, const float y) : rect(Rectangle { x, y, 5, 5 }) {}
  CollisionProbe(const float x, const float y, const float w, const float h)
      : rect(Rectangle { x, y, w, h }) {}
  CollisionProbe(const float x, const float y, const Color color)
      : rect(Rectangle { x, y, 5, 5 }), color(color) {}
  ~CollisionProbe() = default;

  bool collided(Rectangle &other) const;
  void draw() const;

  [[nodiscard]] float getWidth() const { return rect.width; }
  [[nodiscard]] float getHeight() const { return rect.height; }

  void setPosition(const Vector2 position) {
    this->rect.x = position.x;
    this->rect.y = position.y;
  }
  void setPosition(const float x, const float y) {
    this->rect.x = x;
    this->rect.y = y;
  }
  void setX(const float x) { this->rect.x = x; }
  void setY(const float y) { this->rect.y = y; }
};

#endif // COLLISIONPROBE_H

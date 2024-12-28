//
// Created by Administrator on 12/24/2024.
//

#ifndef GOOMBAS_H
#define GOOMBAS_H
#include "Baddie.h"

class Goomba : public Baddie {
public:
  Goomba(Vector2 position, Vector2 dimension, Vector2 velocity, Color color);
  ~Goomba() override = default;
};

#endif // GOOMBAS_H

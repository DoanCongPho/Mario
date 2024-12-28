//
// Created by Administrator on 12/24/2024.
//

#ifndef MUNCHER_H
#define MUNCHER_H
#include "Baddie.h"

class Muncher : public Baddie {
public:
  Muncher(Vector2 position, Vector2 dimension, Vector2 velocity, Color color);
  ~Muncher() override = default;
};

#endif // MUNCHER_H

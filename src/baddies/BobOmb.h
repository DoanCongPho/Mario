//
// Created by Administrator on 12/24/2024.
//

#ifndef BOBOMB_H
#define BOBOMB_H
#include "Baddie.h"

class BobOmb : public Baddie {
public:
  BobOmb(Vector2 position, Vector2 dimensions, Vector2 velocity, Color color);
  ~BobOmb() override = default;
};

#endif // BOBOMB_H

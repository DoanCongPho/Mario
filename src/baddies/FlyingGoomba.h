//
// Created by Administrator on 12/24/2024.
//

#ifndef FLYINGGOOMBA_H
#define FLYINGGOOMBA_H
#include "Baddie.h"

class FlyingGoomba : public Baddie {
public:
  FlyingGoomba(Vector2 position, Vector2 dimension, Vector2 velocity,
               Color color);
  ~FlyingGoomba() override = default;

  void updateCollisionProbes() override;
  void onHit() override;
};

#endif // FLYINGGOOMBA_H

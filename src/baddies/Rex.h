//
// Created by Administrator on 12/24/2024.
//

#ifndef REX_H
#define REX_H
#include "Baddie.h"

class Rex : public Baddie {
public:
  Rex(Vector2 position, Vector2 dimension, Vector2 velocity, Color color);
  ~Rex() override = default;

  void onHit() override;
};

#endif // REX_H

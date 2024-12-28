//
// Created by Administrator on 12/24/2024.
//

#ifndef GREENKOOPATROOPA_H
#define GREENKOOPATROOPA_H
#include "Baddie.h"

class GreenKoopaTroopa : public Baddie {
public:
  GreenKoopaTroopa(Vector2 position, Vector2 dimension, Vector2 velocity,
                   Color color);
  ~GreenKoopaTroopa() override = default;
};

#endif // GREENKOOPATROOPA_H

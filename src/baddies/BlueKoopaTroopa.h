//
// Created by Administrator on 12/24/2024.
//

#ifndef BLUEKOOPATROOPA_H
#define BLUEKOOPATROOPA_H
#include "Baddie.h"

class BlueKoopaTroopa : public Baddie {
public:
  BlueKoopaTroopa(Vector2 position, Vector2 dimensions, Vector2 velocity,
                  Color color);
  ~BlueKoopaTroopa() override = default;
};

#endif // BLUEKOOPATROOPA_H

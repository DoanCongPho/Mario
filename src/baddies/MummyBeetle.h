//
// Created by Administrator on 12/24/2024.
//

#ifndef MUMMYBEETLE_H
#define MUMMYBEETLE_H
#include "Baddie.h"

class MummyBeetle : public Baddie {
public:
  MummyBeetle(Vector2 position, Vector2 dimension, Vector2 velocity,
              Color color);
  ~MummyBeetle() override = default;
};

#endif // MUMMYBEETLE_H

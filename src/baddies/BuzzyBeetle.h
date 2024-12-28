//
// Created by Administrator on 12/24/2024.
//

#ifndef BUZZYBEETLE_H
#define BUZZYBEETLE_H
#include "Baddie.h"

class BuzzyBeetle : public Baddie {
public:
  BuzzyBeetle(Vector2 position, Vector2 dimensions, Vector2 velocity,
              Color color);
  ~BuzzyBeetle() override = default;
};

#endif // BUZZYBEETLE_H

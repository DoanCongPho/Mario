//
// Created by Administrator on 12/23/2024.
//

#ifndef BANZAIBILL_H
#define BANZAIBILL_H

#include "Baddie.h"

class BanzaiBill : public Baddie {
public:
  BanzaiBill(Vector2 position, Vector2 dimensions, Vector2 velocity,
             Color color);
  ~BanzaiBill() override = default;

  void onDying() override;
};

#endif // BANZAIBILL_H

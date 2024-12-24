//
// Created by Administrator on 12/24/2024.
//

#ifndef BULLETBILL_H
#define BULLETBILL_H
#include "Baddie.h"

class BulletBill : public Baddie {
public:
  BulletBill(Vector2 position, Vector2 dimension, Vector2 velocity,
             Color color);
  ~BulletBill() override = default;

  void onDying() override;
};

#endif // BULLETBILL_H

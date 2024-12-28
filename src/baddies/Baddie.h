//
// Created by Administrator on 12/23/2024.
//

#ifndef BADDIE_H
#define BADDIE_H

#include "../Player.hpp"
#include "../Sprite.hpp"

class Baddie : public Sprite {
protected:
  std::string textureNameTemplate = "Unknown_%d";
  std::string animationTextureName = "unknown";
  bool affectedByGravity = true;
  float dyingFrameAcum = 0;
  float dyingFrameTime = 0.1;
  int maxDyingFrames = 4;
  int currentDyingFrame = 0;
  float pointsFrameAcum = 0;
  float pointsFrameTime = 1;
  Vector2 posOnDying = Vector2 { 0, 0 };

public:
  Baddie();
  ~Baddie() override = default;

  void update(float deltaTime, const std::vector<CollisionBox>& collisionBoxes) override;
  virtual void updatePosition(float deltaTime, const std::vector<CollisionBox>& collisionBoxes);

  void draw() const override;
  void activateWithPlayerProximity(Player &player);

  virtual void onHit();
  virtual void onDying();
  virtual void onSouthCollision();
  virtual void followTheLeader(Sprite *sprite);
};

#endif // BADDIE_H

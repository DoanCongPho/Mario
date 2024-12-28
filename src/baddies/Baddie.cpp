//
// Created by Administrator on 12/23/2024.
//

#include "Baddie.h"

#include "../ResourcesManager.hpp"

Baddie::Baddie() {
  frameTime = 0.2;
  hitsToDie = 1;
  earnedPoints = 200;
}

void Baddie::update(const float deltaTime, const std::vector<CollisionBox>& collisionBoxes) {
  updateCollisionProbes();
  updatePosition(deltaTime, collisionBoxes);
  updateCollisionProbes();

  if (state == SPRITE_STATE_ACTIVE) {
    frameAcum += deltaTime;

    if (frameAcum >= frameTime) {
      frameAcum = 0;
      currentFrame++;
      currentFrame %= maxFrames;
    }
  } else if (state == SPRITE_STATE_DYING) {
    dyingFrameAcum += deltaTime;
    pointsFrameAcum += deltaTime;

    if (dyingFrameAcum >= dyingFrameTime) {
      dyingFrameAcum = 0;
      currentDyingFrame++;

      if (currentDyingFrame >= maxDyingFrames) {
        state = SPRITE_STATE_TO_BE_REMOVED;
      }
    }

    if (pointsFrameAcum >= pointsFrameTime) {
      pointsFrameAcum = pointsFrameTime;
    }
  }
}

void Baddie::updatePosition(const float deltaTime, const std::vector<CollisionBox>& collisionBoxes) {
  Vector2 nextPosition { pos.x + vel.x * deltaTime, pos.y + vel.y * deltaTime };


  if (affectedByGravity) {
    vel.y = GRAVITY;
  }

  if (state == SPRITE_STATE_ACTIVE) {
    isFacingRight = vel.x >= 0;
  }

  if (affectedByGravity) {
    Rectangle verticalBox { pos.x, nextPosition.y, dim.x, dim.y };
    Rectangle horizontalBox { nextPosition.x, pos.y, dim.x, dim.y };

    for (const auto& box : collisionBoxes) {
      if (CheckCollisionRecs(verticalBox, box.rect)) {
        if (vel.y > 0) {
          nextPosition.y = box.rect.y - dim.y;
        } else if (vel.y < 0) {
          nextPosition.y = box.rect.y + box.rect.height;
        }

        vel.y = 0;
      }

      if (CheckCollisionRecs(horizontalBox, box.rect)) {
        if (vel.x > 0) {
          nextPosition.x = box.rect.x - dim.x;
        } else if (vel.x < 0) {
          nextPosition.x = box.rect.x + box.rect.width;
        }

        vel.x = -vel.x;
      }
    }
  }

  pos.x = nextPosition.x;
  pos.y = nextPosition.y;
}

void Baddie::draw() const {
  if (state == SPRITE_STATE_ACTIVE) {
    const auto animations = ResourcesManager::getInstance().getA(animationTextureName);
    const auto texture = animations[currentFrame];
    const auto needsFlipping = !isFacingRight;

    DrawTexturePro(texture, Rectangle { 0, 0, dim.x * (needsFlipping ? -1.0f : 1.0f), dim.y },
                   Rectangle { pos.x + dim.x / 2, pos.y + dim.y / 2,
                             dim.x, dim.y },
                   Vector2 {dim.x / 2, dim.y / 2}, angle, WHITE);
  } else if (state == SPRITE_STATE_DYING) {
    const auto animations = ResourcesManager::getInstance().getA("puft");
    const auto texture = animations[currentDyingFrame];

    DrawTexture(texture, posOnDying.x, posOnDying.y, WHITE);
  }

#if 0
  cpNorth.draw();
  cpSouth.draw();
  cpEast.draw();
  cpWest.draw();
#endif
}

void Baddie::activateWithPlayerProximity(Player &player) {
  auto [width, height] = player.GetSize();
  auto [posX, posY] = player.GetPosition();
  const auto activationWidth = static_cast<float>(
      GetScreenWidth() * 2); // yeah this needs to be refactored out eventually
  const auto collision =
      CheckCollisionPointRec(Vector2 { pos.x + dim.x / 2, pos.y + dim.y / 2 },
                             Rectangle { posX + width / 2 - activationWidth / 2,
                                       posY + height / 2 - activationWidth / 2,
                                       activationWidth, activationWidth });

  if (collision) {
    state = SPRITE_STATE_ACTIVE;
  }
}

void Baddie::onHit() {
  hitsToDie--;

  if (hitsToDie == 0) {
    state = SPRITE_STATE_DYING;
    posOnDying = pos;
    onDying();
  }
}

void Baddie::onDying() {
  vel.x = GetRandomValue(0, 1) == 0 ? 200 : -200;
  vel.y = -200;
  affectedByGravity = false;
}

void Baddie::onSouthCollision() {}

void Baddie::followTheLeader(Sprite *sprite) {}

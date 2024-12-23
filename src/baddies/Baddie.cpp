//
// Created by Administrator on 12/23/2024.
//

#include "Baddie.h"

Baddie::Baddie()
    : dyingFrameAcum(0), dyingFrameTime(0.1), maxDyingFrames(4),
      currentDyingFrame(0), pointsFrameAcum(0), pointsFrameTime(1),
      posOnDying(Vector2(0, 0)) {}

void Baddie::update(const float deltaTime) {
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

void Baddie::updatePosition(const float deltaTime) {
  pos.x += vel.x * deltaTime;
  pos.y += vel.y * deltaTime;

  if (state == SPRITE_STATE_ACTIVE) {
    isFacingRight = vel.x >= 0;
  }
}

void Baddie::activateWithPlayerProximity(Player &player) {
  auto [width, height] = player.GetSize();
  auto [posX, posY] = player.GetPosition();
  const auto activationWidth = static_cast<float>(
      GetScreenWidth() * 2); // yeah this needs to be refactored out eventually
  const auto collision =
      CheckCollisionPointRec(Vector2(pos.x + dim.x / 2, pos.y + dim.y / 2),
                             Rectangle(posX + width / 2 - activationWidth / 2,
                                       posY + height / 2 - activationWidth / 2,
                                       activationWidth, activationWidth));

  if (collision) {
    state = SPRITE_STATE_ACTIVE;
  }
}

void Baddie::onHit() {
  state = SPRITE_STATE_DYING;
  posOnDying = pos;
}

void Baddie::onDying() {
  vel.x = GetRandomValue(0, 1) == 0 ? 200 : -200;
  vel.y = -200;
}

void Baddie::onSouthCollision() {}

void Baddie::followTheLeader(Sprite *sprite) {}

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

void Baddie::update(const float deltaTime) {
  updatePosition(deltaTime);
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

void Baddie::updatePosition(const float deltaTime) {
  pos.x += vel.x * deltaTime;
  pos.y += vel.y * deltaTime;

  if (state == SPRITE_STATE_ACTIVE) {
    isFacingRight = vel.x >= 0;
  }

  if (affectedByGravity) {
    vel.y += GRAVITY;
  }
}

void Baddie::draw() const {
  if (state == SPRITE_STATE_ACTIVE) {
    const auto textureName =
        TextFormat(textureNameTemplate.c_str(), currentFrame);
    const auto texture =
        ResourcesManager::getInstance().GetTexture(textureName);
    const auto needsFlipping = !isFacingRight;

    DrawTexturePro(texture, Rectangle(0, 0, dim.x, dim.y),
                   Rectangle(pos.x + dim.x / 2, pos.y + dim.y / 2,
                             dim.x * (needsFlipping ? -1.0 : 1.0), dim.y),
                   Vector2(dim.x / 2, dim.y / 2), angle, WHITE);
  } else if (state == SPRITE_STATE_DYING) {
    auto puftName = TextFormat("Puft_%d", currentDyingFrame);
    auto puftTexture = ResourcesManager::getInstance().GetTexture(puftName);

    DrawTexture(puftTexture, posOnDying.x, posOnDying.y, WHITE);
  }

#ifdef DEBUG
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
      CheckCollisionPointRec(Vector2(pos.x + dim.x / 2, pos.y + dim.y / 2),
                             Rectangle(posX + width / 2 - activationWidth / 2,
                                       posY + height / 2 - activationWidth / 2,
                                       activationWidth, activationWidth));

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
}

void Baddie::onSouthCollision() {}

void Baddie::followTheLeader(Sprite *sprite) {}

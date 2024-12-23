//
// Created by Administrator on 12/23/2024.
//

#include "BanzaiBill.h"

#include "../ResourcesManager.hpp"

BanzaiBill::BanzaiBill(Vector2 position, Vector2 dimensions, Vector2 velocity,
                       Color color) {
  pos = position;
  dim = dimensions;
  vel = velocity;
}

void BanzaiBill::updatePosition(const float deltaTime) {
  Baddie::updatePosition(deltaTime);

  if (state == SPRITE_STATE_DYING) {
    vel.y += GRAVITY;
  }
}

void BanzaiBill::draw() const {
  auto textures = ResourcesManager::getInstance().GetTextures();
  auto texture = textures["BanzaiBill_0"];
  auto needsFlipping = !isFacingRight;

  DrawTexturePro(texture, Rectangle(0, 0, dim.x, dim.y),
                 Rectangle(pos.x + dim.x / 2, pos.y + dim.y / 2,
                           dim.x * (needsFlipping ? -1.0 : 1.0), dim.y),
                 Vector2(dim.x / 2, dim.y / 2), angle, WHITE);

  if (state == SPRITE_STATE_DYING) {
    auto puftName = TextFormat("Puft_%d", currentDyingFrame);
    auto puftTexture = textures[puftName];

    DrawTexture(puftTexture, posOnDying.x, posOnDying.y, WHITE);
  }
}
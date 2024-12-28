

#ifndef Map_hpp
#define Map_hpp

#include "CollisionBox.hpp"
#include "Player.hpp"
#include "ResourcesManager.hpp"
#include "baddies/Baddie.h"
#include "tmx.h"
#include <iostream>
#include <raylib.h>
#include <vector>

class Map {
public:
  Map(const char *mapFile, const char *objectGroupName);
  ~Map();

  void Render();
  const std::vector<CollisionBox> &GetCollisionBoxes() const;
  std::vector<Baddie *> &GetBaddies() { return baddies; }

private:
  std::vector<Baddie *> baddies;
  RenderTexture2D mapFrameBuffer;
  vector<CollisionBox> collisionBoxes;
  void LoadCollisionData(const char *mapFile, const char *objectGroupName);
};

void UnloadMapTexture(Texture2D *tex);
void DrawTmxImageLayer(tmx_layer *layer, Vector2 mapDim);
void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf);
void DrawTmxLayer(tmx_map *map, tmx_layer *layer);
Texture2D *LoadMapTexture(const char *fileName);
void loadAllAnimations();
bool IsTileCollidable(tmx_layer *layer, tmx_map *map, int x, int y);
bool CheckCollisionWithMap(Player *player, tmx_map *map,
                           tmx_layer *collisionLayer);
Rectangle GetPlayerCollisionBox(const Player &player);

#endif

#include "ResourcesManager.hpp"
#include <iostream>

void ResourcesManager::LoadAnimationTextures(const pair<string, string>& p, int frameCount) {
    string basePath = p.second;
    string nameA = p.first;
    
    vector<Texture2D> textures;
    
    for (int i = 0; i < frameCount; ++i) {
        string filePath = basePath + std::to_string(i) + ".png";
        Texture2D texture = LoadTexture(filePath.c_str());
        if (texture.id == 0) {
            cerr << "Failed to load texture: " << filePath << endl;
            continue;
        }
        textures.push_back(texture);
    }
    if (!textures.empty()) {
        animations[nameA] = textures;
    } else {
        cerr << "No textures were loaded for animation: " << nameA << endl;
    }
}

void ResourcesManager::UnloadAnimationTextures(vector<Texture2D>& textures) {
    for (Texture2D& tex : textures) {
        UnloadTexture(tex);
    }
    textures.clear();
}

vector<Texture2D>& ResourcesManager::getA(const string& nameA) {
    return animations[nameA];
}

void ResourcesManager::LoadTextures(const pair<string, string>& p) {
    string basePath = p.second;
    string nameT = p.first;
    string filePath = basePath + ".png";
    Texture2D texture = LoadTexture(filePath.c_str());
    if (texture.id == 0) {
        cerr << "Failed to load texture: " << filePath << endl;
    } else {
        textures[nameT] = texture;
    }
}

void ResourcesManager::DrawTexture(const string& textureName, Vector2 position, float rotation, float scale, Color tint) {
    if (textures.find(textureName) != textures.end()) {
        Texture2D& texture = textures[textureName];
        Vector2 origin = {texture.width * scale / 2.0f, texture.height * scale / 2.0f};
        Rectangle sourceRect = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
        Rectangle destRect = {position.x, position.y, texture.width * scale, texture.height * scale};
        
        DrawTexturePro(texture, sourceRect, destRect, origin, rotation, tint);
    } else {
        TraceLog(LOG_ERROR, "Texture %s not found!", textureName.c_str());
    }
}



const Texture2D& ResourcesManager::GetTexture(const std::string& textureName) const {
    auto it = textures.find(textureName);
    if (it != textures.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Texture not found: " + textureName);
    }
}




Texture2D *LoadMapTexture(const char *fileName)
{
    Texture2D *tex = (Texture2D *)malloc(sizeof(Texture2D));
    if (tex != NULL)
    {
        *tex = LoadTexture(fileName);
        TraceLog(LOG_INFO, "TMX texture loaded from %s", fileName);
        return tex;
    }
    return NULL;
}
void UnloadMapTexture(Texture2D *tex)
{
    if (tex != NULL)
    {
        UnloadTexture(*tex);
        free(tex);
    }
}
void DrawTmxLayer(tmx_map *map, tmx_layer *layer)
{
    unsigned long row, col;
    unsigned int gid;
    unsigned int flip;
    tmx_tile *tile;
    unsigned int tile_width;
    unsigned int tile_height;
    Rectangle sourceRect;
    Rectangle destRect;
    Texture2D *tsTexture; // tileset texture
    float rotation = 0.0;
    Vector2 origin = {0.0, 0.0};
    
    for (row = 0; row < map->height; row++)
    {
        for (col = 0; col < map->width; col++)
        {
            gid = layer->content.gids[(row * map->width) + col];
            flip = gid & ~TMX_FLIP_BITS_REMOVAL;    // get flip operations from GID
            gid = gid & TMX_FLIP_BITS_REMOVAL;      // remove flip operations from GID to get tile ID
            tile = map->tiles[gid];
            if (tile != NULL)
            {
                
                if (tile->image != NULL)
                {
                    tsTexture = (Texture2D *)tile->image->resource_image;
                    tile_width = tile->image->width;
                    tile_height = tile->image->height;
                }
                else
                {
                    tsTexture = (Texture2D *)tile->tileset->image->resource_image;
                    tile_width = tile->tileset->tile_width;
                    tile_height = tile->tileset->tile_height;
                }
                
                sourceRect.x = tile->ul_x;
                sourceRect.y = tile->ul_y;
                sourceRect.width = destRect.width = tile_width;
                sourceRect.height = destRect.height = tile_height;
                destRect.x = col * tile_width;
                destRect.y = row * tile_height;
                // Deal with flips
                origin.x = 0.0;
                origin.y = 0.0;
                rotation = 0.0;
                switch(flip)
                {
                    case TMX_FLIPPED_DIAGONALLY:
                    {
                        sourceRect.height = -1 * sourceRect.height;
                        rotation = 90.0;
                    } break;
                    case TMX_FLIPPED_VERTICALLY:
                    {
                        sourceRect.height = -1 * sourceRect.height;
                    } break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        rotation = -90.0;
                    } break;
                    case TMX_FLIPPED_HORIZONTALLY:
                    {
                        sourceRect.width = -1 * sourceRect.width;
                    } break;
                    case  TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_HORIZONTALLY:
                    {
                        rotation = 90.0;
                    } break;
                    case TMX_FLIPPED_HORIZONTALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        rotation = 180.0;
                    } break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_HORIZONTALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        sourceRect.width = -1 * sourceRect.width;
                        rotation = 90.0;
                    } break;
                    default:
                    {
                        origin.x = 0.0;
                        origin.y = 0.0;
                        rotation = 0.0;
                    } break;
                }
                if (rotation != 0.0)
                {
                    origin.x = tile_width / 2;
                    origin.y = tile_height / 2;
                    destRect.x += tile_width / 2;
                    destRect.y += tile_height / 2;
                }
                DrawTexturePro(*tsTexture, sourceRect, destRect, origin, rotation, WHITE);
            }
        }
    }
}
void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf)
{
    tmx_layer *layer = NULL;
    tmx_img_load_func = (void *(*)(const char *))LoadMapTexture;
    tmx_img_free_func = (void (*)(void *))UnloadMapTexture;
    tmx_map *mapTmx = tmx_load(mapFileName);
    if (mapTmx == NULL) {
        tmx_perror("tmx_load");
        return;
    }

    *buf = LoadRenderTexture(mapTmx->width * mapTmx->tile_width, mapTmx->height * mapTmx->tile_height);
    
    BeginTextureMode(*buf);
    ClearBackground(RAYWHITE);
    layer = mapTmx->ly_head;

    while(layer)
    {
        if (layer->visible)
        {
            switch(layer->type)
            {
                case L_LAYER:
                    TraceLog(LOG_INFO, "Render TMX layer \"%s\"", layer->name);
                    DrawTmxLayer(mapTmx, layer);
                    break;
                case L_GROUP:
                case L_OBJGR:
                case L_IMAGE:
                    TraceLog(LOG_INFO, "Render TMX image layer \"%s\"", layer->name);
                    DrawTmxImageLayer(layer, (Vector2){static_cast<float>(mapTmx->width*32), static_cast<float>(mapTmx->height*32)});
                    break;
                case L_NONE:
                default:
                    break;
            }
        }
        layer = layer->next;
    }
    EndTextureMode();
    
    tmx_map_free(mapTmx);
}

void DrawTmxImageLayer(tmx_layer *layer, Vector2 mapDim)
{
    if (layer->type != L_IMAGE || !layer->content.image) return;
    
    tmx_image *image = layer->content.image;

    // Load the texture from the image resource
    Texture2D *imageTexture = (Texture2D*)image->resource_image;
    if (imageTexture->id == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load image for layer \"%s\"", layer->name);
        return;
    }

    float offsetX = layer->offsetx;
    float offsetY = layer->offsety;

    int mapWidth = mapDim.x;  // Or use map dimensions if available
    int mapHeight = mapDim.y; // Or use map dimensions if available

    int horizontalRepeats = (mapWidth + imageTexture->width - 1) / imageTexture->width;
    int verticalRepeats = (mapHeight + imageTexture->height - 1) / imageTexture->height;

    // Draw the image repeatedly across the screen
    for (int i = 0; i < horizontalRepeats; i++) {
        for (int j = 0; j < verticalRepeats; j++) {
            DrawTexture(*imageTexture, offsetX + i * imageTexture->width, offsetY + j * imageTexture->height, WHITE);
        }
    }
}

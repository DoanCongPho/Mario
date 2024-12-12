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

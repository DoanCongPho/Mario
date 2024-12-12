#ifndef ResourcesManager_hpp
#define ResourcesManager_hpp
#include <map>
#include <vector>
#include <string>
#include "raylib.h"
#include "config.hpp"
#include "tmx.h"


using namespace std;

class ResourcesManager {
private:
    // Private constructor to prevent instantiation
    ResourcesManager() = default;
    
    // Private destructor to prevent deletion
    ~ResourcesManager() = default;
    
    // Deleted copy constructor and assignment operator to prevent copying
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;
    
    // Storage for Resourcess
    map<string, Texture2D> textures;
    map<string, vector<Texture2D>> animations;
    
public:
    // Public static method to get the singleton instance
    static ResourcesManager& getInstance() {
        static ResourcesManager instance; // Single instance
        return instance;
    }
    
    void LoadTSX(const std::string& tsxFilePath);
    const Texture2D& GetTexture(const std::string& textureName) const;
    
    // Public methods
    void LoadAnimationTextures(const pair<string, string>& p, int frameCount);
    void LoadTextures(const pair<string, string>& p);
    vector<Texture2D>& getA(const string& nameA);
    void UnloadAnimationTextures(vector<Texture2D>& textures);
    void DrawTexture(const string& textureName, Vector2 position, float rotation = 0.0f, float scale = 1.0f, Color tint = WHITE);
    
};

#endif



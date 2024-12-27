#include "Sound.h"

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager() : isMusicPlaying(false) {
    InitAudioDevice();
}

SoundManager::~SoundManager() {
    if (isMusicPlaying) {
        StopMusicStream(currentMusic);
        UnloadMusicStream(currentMusic);
    }
    CloseAudioDevice();
}

void SoundManager::addMapMusic(const std::string& mapName, const std::string& filePath) {
    mapMusicPaths[mapName] = filePath;
}

void SoundManager::playMapMusic(const std::string& mapName) {
    auto it = mapMusicPaths.find(mapName);
    if (it != mapMusicPaths.end()) {
        if (isMusicPlaying) {
            StopMusicStream(currentMusic);
            UnloadMusicStream(currentMusic);
        }
        currentMusic = LoadMusicStream(it->second.c_str());
        PlayMusicStream(currentMusic);
        isMusicPlaying = true;
    } else {
        std::cerr << "Music for map '" << mapName << "' not found!" << std::endl;
    }
}

void SoundManager::stopMusic() {
    if (isMusicPlaying) {
        StopMusicStream(currentMusic);
        UnloadMusicStream(currentMusic);
        isMusicPlaying = false;
    }
}

void SoundManager::updateMusic() {
    if (isMusicPlaying) {
        UpdateMusicStream(currentMusic);
    }
}
void loadMusic(){
    SoundManager::getInstance().addMapMusic("Map2", "Resources/musics/music3.mp3");
    SoundManager::getInstance().addMapMusic("Map1", "Resources/musics/music2.mp3"); SoundManager::getInstance().addMapMusic("INTRO", "Resources/musics/music1.mp3");
}

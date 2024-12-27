#ifndef SOUND_H
#define SOUND_H

#include <unordered_map>
#include <string>
#include <raylib.h>
#include <iostream>

class SoundManager {
public:
    static SoundManager& getInstance();

    // Prevent copying and assignment
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    void addMapMusic(const std::string& mapName, const std::string& filePath);
    void playMapMusic(const std::string& mapName);
    void stopMusic();
    void updateMusic(); // Update music stream (for streaming music in Raylib)

private:
    SoundManager();
    ~SoundManager();

    Music currentMusic;
    bool isMusicPlaying;
    std::unordered_map<std::string, std::string> mapMusicPaths;
};


void loadMusic();



#endif // SOUND_H

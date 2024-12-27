#include <iostream>
#include "raylib.h"
#include <mmsystem.h>




using namespace std;


void LoadMusic(){
    InitAudioDevice();  // Initialize the audio device
    // Load a music file
    Music music1 = LoadMusicStream("Resources/musics/baothucquandoi.wav");
    Music music2 = LoadMusicStream("Resources/musics/BackgroundSoundMap2.wav");
    Music music3 = LoadMusicStream("Resources/musics/courseClear.mp3");
    Music music4 = LoadMusicStream("Resources/musics/ending.mp3");
    Music music5 = LoadMusicStream("Resources/musics/gameOver.mp3");
    Music music6 = LoadMusicStream("Resources/musics/invincible.mp3");
    Music music7 = LoadMusicStream("Resources/musics/music1.mp3");
    Music music8 = LoadMusicStream("Resources/musics/music2.mp3");
    Music music9 = LoadMusicStream("Resources/musics/music3.mp3");
    Music music10 = LoadMusicStream("Resources/musics/music4.mp3");
    Music music11 = LoadMusicStream("Resources/musics/music5.mp3");
    Music music12 = LoadMusicStream("Resources/musics/music6.mp3");
    Music music13 = LoadMusicStream("Resources/musics/music7.mp3");
    Music music14 = LoadMusicStream("Resources/musics/music8.mp3");
    Music music15 = LoadMusicStream("Resources/musics/music9.mp3");
    Music music16 = LoadMusicStream("Resources/musics/playerDown.mp3");
    Music music17 = LoadMusicStream("Resources/musics/title.mp3");



}


void playSoundMap1(){
InitAudioDevice();  // Initialize the audio device
// Load a music file
Music music1 = LoadMusicStream("Resources/musics/baothucquandoi.wav");

PlayMusicStream(music1);  // Start playing the music

while (!WindowShouldClose()) {
    UpdateMusicStream(music1);  // Keep the music stream updated  
}

UnloadMusicStream(music1);  // Unload music when done
CloseAudioDevice();        // Close the audio device
}






void playSoundMap2() {
    InitAudioDevice();  // Initialize the audio device
    // Load a music file
    Music music2 = LoadMusicStream("Resources/musics/BackgroundSoundMap2.wav");

    PlayMusicStream(music2);  // Start playing the music

    while (!WindowShouldClose()) {
        UpdateMusicStream(music2);  // Keep the music stream updated  
    }

    UnloadMusicStream(music2);  // Unload music when done
    CloseAudioDevice();        // Close the audio device
}



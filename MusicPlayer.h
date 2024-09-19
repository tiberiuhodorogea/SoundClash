#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <stdexcept>
#include <iostream>

class MusicPlayer {
public:
    MusicPlayer();
    ~MusicPlayer();
    void loadMusic(const std::string& filePath);
    void playMusic(int loops = -1);
    void setMusicPosition(double seconds);
    double getMusicPosition();
    void pauseMusic();
    void ResumeMusic();
    void uninitMusicPlayer();

private:
    Mix_Music* music;
};

#endif // MUSICPLAYER_H
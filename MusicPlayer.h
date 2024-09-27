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
    void load(const std::string& filePath);
    void play(int loops = -1);
    void setPosition(double seconds);
    void pause();
    void Resume();
    double getPosition();
    void uninit();

private:
    Mix_Music* _music;
};

#endif // MUSICPLAYER_H
#include "MusicPlayer.h"
#include <SDL.h>
#include <SDL_mixer.h>

MusicPlayer::MusicPlayer() : music(nullptr) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        throw std::runtime_error("SDL initialization failed");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_Quit();
        throw std::runtime_error("SDL_mixer initialization failed");
    }
}

MusicPlayer::~MusicPlayer() {
    if (music) {
        Mix_FreeMusic(music);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void MusicPlayer::loadMusic(const std::string& filePath) {
    music = Mix_LoadMUS(filePath.c_str());
    if (!music) {
        std::cerr << "Error loading music: " << Mix_GetError() << std::endl;
        throw std::runtime_error("Music loading failed");
    }
}

void MusicPlayer::playMusic(int loops) {
    if (Mix_PlayMusic(music, loops) == -1) {
        std::cerr << "Error playing music: " << Mix_GetError() << std::endl;
        throw std::runtime_error("Music playback failed");
    }
}

void MusicPlayer::setMusicPosition(double seconds) {
    if (Mix_SetMusicPosition(seconds) == -1) {
        std::cerr << "Error setting music position: " << Mix_GetError() << std::endl;
        throw std::runtime_error("Music position setting failed");
    }
}

double MusicPlayer::getMusicPosition()
{
    return Mix_GetMusicPosition(music);
        
}

// Mix_OpenAudioDevice schimbare device output
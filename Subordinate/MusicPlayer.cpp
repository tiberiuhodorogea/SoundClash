#include "MusicPlayer.h"
#include <SDL.h>
#include <SDL_mixer.h>

MusicPlayer::MusicPlayer() : _music(nullptr) {
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
    if (_music) {
        Mix_FreeMusic(_music);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void MusicPlayer::load(const std::string& filePath) {
    _music = Mix_LoadMUS(filePath.c_str());
    if (!_music){
        std::cerr << "Error loading music: " << Mix_GetError() << std::endl;
        throw std::runtime_error("Music loading failed");
    }
}

void MusicPlayer::play(int loops) {
    if (Mix_PlayMusic(_music, loops) == -1) {
        std::cerr << "Error playing music: " << Mix_GetError() << std::endl;
        throw std::runtime_error("Music playback failed");
    }
}

void MusicPlayer::setPosition(double seconds) {
    if (Mix_SetMusicPosition(seconds) == -1) {
        std::cerr << "Error setting music position: " << Mix_GetError() << std::endl;
        throw std::runtime_error("Music position setting failed");
    }
}

void MusicPlayer::pause()
{
    Mix_PauseMusic();
}

void MusicPlayer::Resume()
{
    Mix_ResumeMusic();
}

double MusicPlayer::getPosition()
{
    return Mix_GetMusicPosition(_music);
        
}
void MusicPlayer::uninit()
{
    std::cout << "Terminating music";
    Mix_HaltMusic();
    std::cout << "Closing the audio device";
    Mix_CloseAudio();
    std::cout << "Quitting SDL_mixer";
    Mix_Quit();
}
// Mix_OpenAudioDevice schimbare device output
#ifndef __AUDIO_HPP__
#define __AUDIO_HPP__
#include "rsdl.hpp"
#include <string>
#include <cstring>
#include <iostream>

enum AudioListType {
    THEME,
    SHOOTING, 
    EXPLOTION,

};

const std::string AudioList[] {
    "assets/musics/theme.mp3",
    "assets/musics/shot.wav", 
    "assets/musics/explotion.wav"
};

class AudioPlayer {
public:
    AudioPlayer(Window*);
    void play_sound_effect(AudioListType);
    void play_theme();
    void pause_theme();
    void resume_theme();
private:
    Window* win;
};

#endif 
#pragma once

#include <SDL_mixer.h>
#include <string>
#include "lib.h"

using namespace std;

class sound:LTexture
{
public:
    bool playing;

    bool init();

    void Free();

    void playBreath();

    void playHit();

    void renderSound();

    bool soundIcon();

private:
    const short int POS_X = 107;
    const short int POS_Y = 267;
    Mix_Chunk* breath = NULL;
    Mix_Chunk* hit = NULL;
    SDL_Rect Mute ;
    SDL_Rect Active ;
};



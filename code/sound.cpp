#include "sound.h"
#include <stdio.h>
#include <iostream>
#include <string>

bool sound::init()
{
    string breath_path = "res/sound/sfx_breath.wav";
    string hit_path = "res/sound/sfx_bonk.wav";
    string sound_path = "res/image/sound.png";

    bool success = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        breath = Mix_LoadWAV( breath_path.c_str() );
        if ( breath == NULL )
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        hit = Mix_LoadWAV( hit_path.c_str() );
        if (hit == NULL)
        {
            printf( "Failed to load chord! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }

        if (!Load(sound_path))
        {
            return false;
        }

        Active.x = 0; Active.y = 0; Active.w = getWidth(); Active.h = getHeight() / 2;
        Mute.x = 0; Mute.y = getHeight() / 2; Mute.w = getWidth(); Mute.h = getHeight() / 2;
        isPlay = true;
    }
    return success;
}

void sound::Free()
{
    free();

    Mix_FreeChunk(breath);
    breath = NULL;
    Mix_FreeChunk(hit);
    hit = NULL;

    Mix_Quit();
}

void sound::playBreath()
{
    if (isPlay)
    {
        Mix_PlayChannel( -1, breath, 0 );
    }
}

void sound::playHit()
{
    if (isPlay)
    {
        Mix_PlayChannel(-1, hit, 0);
    }
}

void sound::renderSound()
{
    if (isPlay)
    {
        Render(POS_X, POS_Y, 0, &Active);
    }
    else
    {
        Render(POS_X, POS_Y, 0, &Mute);
    }
}

bool sound::checkSound()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > POS_X && x < POS_X + getWidth() &&
        y > POS_Y && y < POS_Y + getHeight())
    {
        isPlay = !isPlay;
        return true;
    }
    return false;
}
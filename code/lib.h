#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

class position
{
public:
    short int x, y, angle, state;
    void getPos(const short int x, const short int y);
};

class LTexture
{
public:
    LTexture();

    ~LTexture() {}

    bool isNULL();

    bool Load(string path, double scale = 1);

    short int getWidth();
    short int getHeight();

    void free();
    void Render(short int x, short int y, short int angle = 0, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
public:
    SDL_Texture* Texture;

    short int tWidth;
    short int tHeight;

public:
    static SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;
    static SDL_Event event;
    static bool quit;
    static bool die;
    static short int score;

    static const short int SCREEN_WIDTH = 350;
    static const short int SCREEN_HEIGHT = 625;
    static const short int PIPE_SPACE = 160;
    static const short int TOTAL_PIPE = 4;
    static const short int PIPE_DISTANCE = 220;
    static const short int LAND_HEIGHT = 140;
    static const short int SHIBA_WIDTH = 50;
    static const short int SHIBA_HEIGHT = 35;
};
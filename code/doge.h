#pragma once

#include "lib.h"
#include "pipe.h"

using namespace std;

class doge:LTexture
{
private:
    short int angle, time, x0;
    position pos;
    short int ahead = 0;
public:
    bool init(bool isDark);

    void render();

    void Free();

    void resetTime() { time = 0;}

    void fall();

    void update(short int pileWidth, short int pileHeight);

    string saved_path = "";
};


#pragma once

#include "lib.h"
#include <vector>

using namespace std;

class land : LTexture
{
public:
    bool init();

    void Free();

    void render();

    void update();

private:
    position posLand;
};
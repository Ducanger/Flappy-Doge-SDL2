#include "land.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

bool land::init()
{
    posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
    string back_path = "res/image/land.png";
    if (isNULL())
    {
        if ( Load( back_path.c_str(), 1 ) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void land::Free()
{
    free();
}

void land::render()
{
    if (posLand.x > -getWidth() + SCREEN_WIDTH)
    {
        Render(posLand.x, posLand.y);
    }
    else if (posLand.x >= -getWidth() && posLand.x <= -getWidth() + SCREEN_WIDTH)
    {
        Render(posLand.x, posLand.y);
        Render(posLand.x + getWidth(), posLand.y, 0, NULL);
    }
    else if (posLand.x > - 2 * getWidth() + SCREEN_HEIGHT)
    {
        Render(posLand.x + getWidth(), posLand.y, 0, NULL);
    }
    else if (posLand.x > - 2 * getWidth() && posLand.x <= - 2 * getWidth() + SCREEN_HEIGHT)
    {
        Render(posLand.x + getWidth(), posLand.y, 0, NULL);
        Render(posLand.x + 2 * getWidth(), posLand.y);
    }
    else
    {
        posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
        Render(posLand.x, posLand.y);
    }
}

void land::update()
{
    posLand.x -= 3;
}
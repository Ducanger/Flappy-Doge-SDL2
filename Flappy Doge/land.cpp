#include "land.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

bool land::init()
{
    pos.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
    string back_path = "image/land.png";
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
    if (pos.x > -getWidth() + SCREEN_WIDTH)
    {
        Render(pos.x, pos.y);
    }
    else if (pos.x >= -getWidth() && pos.x <= -getWidth() + SCREEN_WIDTH)
    {
        Render(pos.x, pos.y);
        Render(pos.x + getWidth(), pos.y, 0, NULL);
    }
    else if (pos.x > - 2 * getWidth() + SCREEN_HEIGHT)
    {
        Render(pos.x + getWidth(), pos.y, 0, NULL);
    }
    else if (pos.x > - 2 * getWidth() && pos.x <= - 2 * getWidth() + SCREEN_HEIGHT)
    {
        Render(pos.x + getWidth(), pos.y, 0, NULL);
        Render(pos.x + 2 * getWidth(), pos.y);
    }
    else
    {
        pos.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
        Render(pos.x, pos.y);
    }
}

void land::update()
{
    pos.x -= 3;
}


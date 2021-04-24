#include "doge.h"
#include <stdio.h>
#include <iostream>

bool doge::init(bool isDark)
{
    string shiba_path = "res/image/shiba.png";
    if (isDark) shiba_path = "res/image/shiba-dark.png";
    if (saved_path == shiba_path)
    {
        pos.getPos(75, SCREEN_HEIGHT / 2 - 10);
        ahead = 0;
        angle = 0;
    }
    if (isNULL() || saved_path != shiba_path)
    {
        saved_path = shiba_path;
        if ( Load(shiba_path.c_str() , 1) )
        {
            //angle = 0;
            //time = -1;
            return true;
        }
        else
        {
            return false;
        }

    }
    return false;
}

void doge::Free()
{
    free();
}

void doge::render()
{
    Render(pos.x, pos.y, angle);
}

void doge::fall() 
{
    if (lost && pos.y < SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5)
    {
        if (time == 0)
        {
            x0 = pos.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            pos.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }
    }
    else return;
}

void doge::update(short int pipeWidth, short int pipeHeight)
{
    if (!lost)
    {
        if (time == 0)
        {
            x0 = pos.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            pos.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }

        if ( (pos.x + getWidth() > posPipe[ahead].x + 5) && (pos.x + 5 < posPipe[ahead].x + pipeWidth) &&
             (pos.y + 5 < posPipe[ahead].y + pipeHeight || pos.y  + getHeight() > posPipe[ahead].y + pipeHeight + PIPE_SPACE + 5) )
        {
            lost = true;
        }
        else if (pos.x > posPipe[ahead].x + pipeWidth )
        {
            ahead = ( ahead + 1 ) % TOTAL_PIPE;
            score++;
        }

        if ( pos.y > SCREEN_HEIGHT - LAND_HEIGHT -  SHIBA_HEIGHT - 5 || pos.y < - 10 )
        {
            lost = true;
        }
    }
}

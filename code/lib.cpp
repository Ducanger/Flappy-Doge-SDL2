#include "game.h"
#include <iostream>

bool LTexture::quit = false;
SDL_Window* LTexture::gWindow = NULL;
SDL_Renderer* LTexture::gRenderer = NULL;
SDL_Event LTexture::e;
short int LTexture::score = 0;
bool LTexture::lost = true;

LTexture::LTexture()
{
	Texture = NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture );
		Texture = NULL;
		tWidth = 0;
		tHeight = 0;
	}
}

short int LTexture::getWidth()
{
	return tWidth;
}

short int LTexture::getHeight()
{
	return tHeight;
}

void LTexture::Render(short int x, short int y, short int angle, SDL_Rect* clip, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect Rec_Render = { x, y, tWidth, tHeight };

    if( clip != NULL )
	{
		Rec_Render.w = clip->w ;
		Rec_Render.h = clip->h ;
	}

	//Render to screen
    SDL_RenderCopyEx( gRenderer, Texture, clip, &Rec_Render, angle, NULL, flip );
}

bool LTexture::Load(string path, double scale)
{
	//Get rid of preexisting texture
	free();

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x00, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        Texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( Texture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			tWidth = (loadedSurface->w) * scale;
			tHeight = (loadedSurface->h) * scale;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//Return success
	return Texture != NULL;

}

bool LTexture::isNULL()
{
    if (Texture == NULL) return true;
    return false;
}

void position::getPos(const short int x, const short int y)
{
    this->x = x;
    this->y = y;
}

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cmath>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <sstream>


using namespace std;

class LTexture
{
public:
	LTexture();
	void free();
	
	
	void render(int x,int y,SDL_Rect* clipRect = NULL, double degree = 0, SDL_Point* center = NULL, SDL_RendererFlip fliptype = SDL_FLIP_NONE);
	bool loadFromFile(string path);
	bool loadFromRenderedText(string text, SDL_Color textColor, TTF_Font* gFont);
	int getWidth();
	int getHeight();
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};
class LTimer
{
public:
	LTimer();
	void start();
	void stop();
	Uint32 getTicks();
	bool isStarted;
private:
	int mStart;
};
class LBird
{
public:
	const int BIRD_WIDTH = 60;
	const int BIRD_HEIGHT = 42;
	const int ACCELARATION = 1625; //acceleration of the bird's falling
	const int BIRD_X = 120; 
	const int V0 = -450; //velocity when the bird jump
	bool isPlayed;
	int mCurrentSprite;
	
	LBird();
	void handleEvent(SDL_Event &e);
	void move(bool &isMenu);
	void render();
	
	int getY();
	void restart();
	void fall();

private:
	int mY0;
	int mY;
	int degree;
};
class LDoublePipe
{
public:
	const int PIPE_WIDTH = 86;
	const int PIPE_TEXTURE_HEIGHT = 494;
	const int PIPES_DISTANCE = 155;
	LDoublePipe();
	LDoublePipe(int x);
	void move();
	void render();
	int getX();
	int getDownsideY();
	vector <SDL_Rect> getColliders();
	void shiftColliders();
	

private:
	int mX;
	int mDownsidePipeY;
	vector <SDL_Rect> mColliders;
	bool isScored;

};


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gScoreFont = NULL;
TTF_Font* gHighestScoreFont = NULL;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;
const int BIRD_RADIUS = 25;
const int SCREEN_FPS = 200;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
const int SCROLL_VELOCITY = 1;


Mix_Chunk* gWingSound = NULL;
Mix_Chunk* gHitSound = NULL;
Mix_Chunk* gDieSound = NULL;
Mix_Chunk* gPointSound = NULL;


LTexture gBirdTexture;
LTexture gPipeTexture; 
LTexture gBackgroundTexture;
LTexture gGroundTexture;
LTexture gRestartTexture;
LTexture gScoreTexture;
LTexture gHighestScoreTexture;
LTexture gPromptTexture;
LTexture gStartTexture;

LTimer birdTimer;
LTimer fpsTimer;
vector <LDoublePipe> pipes;

int score = 0;
int highestScore;

bool checkCollision(int x, int y, SDL_Rect rect);
void gameInit(bool &isMenu, int &scrollOffset, int &frame, LBird &bird);
bool init();
void loadMedia();
void close();

LTexture::LTexture()
{
	mWidth = 0;
	mHeight = 0;
	mTexture = NULL;
}
void LTexture::free()
{
	mWidth = 0;
	mHeight = 0;
	mTexture = NULL;
}
void LTexture::render(int x, int y, SDL_Rect* clipRect, double degree, SDL_Point* center, SDL_RendererFlip flipType)
{
	SDL_Rect renderQuad = { x,y,mWidth,mHeight };
	if (clipRect != NULL)
	{
		renderQuad.w = clipRect->w;
		renderQuad.h = clipRect->h;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clipRect, &renderQuad, degree, center, flipType);
}
bool LTexture::loadFromFile(string path)
{
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Can't load image! " << IMG_GetError();
	}
	else
	{
		
		mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		mHeight = loadedSurface->h;
		mWidth = loadedSurface->w;
		SDL_FreeSurface(loadedSurface);
	}
	return mTexture != NULL;
}
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor,TTF_Font* gFont)
{
	
	free();


	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
	
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
		
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}
int LTexture::getWidth()
{
	return mWidth;
}
int LTexture::getHeight()
{
	return mHeight;
}
LTimer::LTimer()
{
	mStart = 0;
	isStarted = false;
}
void LTimer::start()
{
	mStart = SDL_GetTicks();
	isStarted = true;
}
void LTimer::stop()
{
	mStart = 0;
	isStarted = false;
}
Uint32 LTimer::getTicks()
{
	if (isStarted == false) return 0;
	return SDL_GetTicks() - mStart;
}
LBird::LBird()
{
	mY = 260;
	mY0 = 260;
	mCurrentSprite = 0;
	degree = 0;
	isPlayed = false;
}
void LBird::restart()
{
	mY =260;
	mY0 = 260;
	mCurrentSprite = 0;
	degree = 0;
	isPlayed = false;
	birdTimer.stop();
}
void LBird::handleEvent(SDL_Event &e)
{
	if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
		if (e.key.keysym.sym == SDLK_SPACE)
		{
			birdTimer.start(); //reset the movement of the bird from the moment the bird get Velocity0
			mY0 = mY;
			isPlayed = true;
			Mix_PlayChannel(-1, gWingSound, 0);
		}
	}
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
			birdTimer.start();
			mY0 = mY;
			isPlayed = true;
			Mix_PlayChannel(-1, gWingSound, 0);	
	}
	
}
void LBird::move(bool &isMenu)
{
	float timeStep = birdTimer.getTicks() / 1000.f; //convert time from tick to second
	mY = mY0 + V0 * timeStep + 0.5 * ACCELARATION * timeStep * timeStep; //phuong trinh roi tu do :v

	if (mY <= -100 || mY >= gBackgroundTexture.getHeight()-BIRD_HEIGHT)
	{
		isMenu = true;
		Mix_PlayChannel(-1, gHitSound, 0);
		return;
	}
	for (int i = 0; i < pipes.size(); ++i)
	{
		vector <SDL_Rect> temp = pipes[i].getColliders(); //colliders of the pipes
		for (int j = 0; j < temp.size(); ++j)
		{
			if (checkCollision(BIRD_X + BIRD_WIDTH/2, mY + BIRD_HEIGHT/2, temp[j])) //check collision with the pipes
			{
				isMenu = true;
				Mix_PlayChannel(-1, gHitSound, 0);
				
				return;
			}
		}
	}
	//check all of the cases that make game over

}
void LBird::fall() // fall after dead
{
	float timeStep = birdTimer.getTicks() / 1000.f;

	mY = mY0 + V0 * timeStep + 0.5 * ACCELARATION * timeStep * timeStep;

	if (mY >= gBackgroundTexture.getHeight() - BIRD_HEIGHT)
	{
		mY = gBackgroundTexture.getHeight() - BIRD_HEIGHT + 10;

		return;
	}

}
void LBird::render()
{
	SDL_Rect temp;
	if (isPlayed)
	{
		temp.x = mCurrentSprite * BIRD_WIDTH;
		temp.y = 0;
		temp.w = BIRD_WIDTH;
		temp.h = BIRD_HEIGHT;
		degree = -30;
		if (birdTimer.getTicks() > 300 && degree < 90)
		{
			degree += (birdTimer.getTicks() - 300) / 50 * 10;
			if (degree > 90) degree = 90; //con chim cui dau
		}
	}
	else {
		temp.x = BIRD_WIDTH;
		temp.y = 0;
		temp.w = BIRD_WIDTH;
		temp.h = BIRD_HEIGHT; // neu chua choi thi chim dung im
		degree = 0;
	}
	gBirdTexture.render(BIRD_X, mY, &temp,degree);
	


	
}
int LBird::getY()
{
	return mY;
}
LDoublePipe::LDoublePipe()
{
	mX = SCREEN_WIDTH*2;
	
	mDownsidePipeY = 175 + rand() % (520 + 1 - 175);
	mColliders.resize(4);
	mColliders[0].w = PIPE_WIDTH;
	mColliders[0].h = 40;
	mColliders[0].x = mX;
	mColliders[0].y = mDownsidePipeY;
	mColliders[1].w = PIPE_WIDTH - 6;
	mColliders[1].h = PIPE_TEXTURE_HEIGHT - 40;
	mColliders[1].x = mX + 3;
	mColliders[1].y = mDownsidePipeY + 40;
	mColliders[2].w = PIPE_WIDTH;
	mColliders[2].h = 40;
	mColliders[2].x = mX;
	mColliders[2].y = mDownsidePipeY-PIPES_DISTANCE-40;
	mColliders[3].w = PIPE_WIDTH - 6;
	mColliders[3].h = PIPE_TEXTURE_HEIGHT - 40;
	mColliders[3].x = mX + 3;
	mColliders[3].y = mDownsidePipeY - PIPES_DISTANCE - 40 - 454;
	//colliders are 4 rectangles
	isScored = false;
}
LDoublePipe::LDoublePipe(int x)
{
	mX = x;

	mDownsidePipeY = 175 + rand() % (520 + 1 - 175);
	mColliders.resize(4);
	mColliders[0].w = PIPE_WIDTH;
	mColliders[0].h = 40;
	mColliders[0].x = mX;
	mColliders[0].y = mDownsidePipeY;
	mColliders[1].w = PIPE_WIDTH - 6;
	mColliders[1].h = PIPE_TEXTURE_HEIGHT - 40;
	mColliders[1].x = mX + 3;
	mColliders[1].y = mDownsidePipeY + 40;
	mColliders[2].w = PIPE_WIDTH;
	mColliders[2].h = 40;
	mColliders[2].x = mX;
	mColliders[2].y = mDownsidePipeY - PIPES_DISTANCE - 40;
	mColliders[3].w = PIPE_WIDTH - 6;
	mColliders[3].h = PIPE_TEXTURE_HEIGHT - 40;
	mColliders[3].x = mX + 3;
	mColliders[3].y = mDownsidePipeY - PIPES_DISTANCE - 40 - 454;
	//colliders are rectangles
	isScored = false;
}

void LDoublePipe::move()
{
	
	mX -= SCROLL_VELOCITY;
	if (mX <= -PIPE_WIDTH)
	{
		mDownsidePipeY = 175 + rand() % (520 + 1 - 175);
		mX = SCREEN_WIDTH;
		isScored = false;
	}
	shiftColliders();
	if (mX <= 120 - PIPE_WIDTH && mX >= 120 - PIPE_WIDTH - SCROLL_VELOCITY + 1)
	{
		isScored = true;
		score++;
		if (score > highestScore)
		{
			highestScore = score;
		}
		Mix_PlayChannel(-1, gPointSound, 0);
	}
}
void LDoublePipe::render()
{
	gPipeTexture.render(mX, mDownsidePipeY);
	gPipeTexture.render(mX, mDownsidePipeY - PIPES_DISTANCE - PIPE_TEXTURE_HEIGHT, NULL, 180);
	
	
}
int LDoublePipe::getX()
{
	return mX;
}
int LDoublePipe::getDownsideY()
{
	return mDownsidePipeY;
}
vector <SDL_Rect> LDoublePipe::getColliders()
{
	return mColliders;
}
void LDoublePipe::shiftColliders()
{
	mColliders[0].x = mX;
	mColliders[0].y = mDownsidePipeY;
	mColliders[1].x = mX + 3;
	mColliders[1].y = mDownsidePipeY + 40;
	mColliders[2].x = mX;
	mColliders[2].y = mDownsidePipeY - PIPES_DISTANCE - 40;
	mColliders[3].x = mX + 3;
	mColliders[3].y = mDownsidePipeY - PIPES_DISTANCE - 40 - 454;

}

bool checkCollision(int x, int y, SDL_Rect rect) //check collision between a circle with ordinates x,y and a rectangle
{
	int cX, cY;
	if (x < rect.x)
	{
		cX = rect.x;
	}
	else if (x > rect.x + rect.w)
	{
		cX = rect.x + rect.w;
	}	
	else
	{
		cX = x;
	}
	if (y < rect.y)
	{
		cY = rect.y;
	}
	else if (y > rect.y + rect.h)
	{
		cY = rect.y + rect.h;
	}
	else
	{
		cY = y;
	}

	int deltaX = abs(x - cX);
	int deltaY = abs(y - cY);
	if (deltaX*deltaX + deltaY * deltaY <= BIRD_RADIUS * BIRD_RADIUS) return true;
	return false;

}
bool init()
{
	bool success = 1;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "Can't initialize! " << SDL_GetError();
		success = 0;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
		{
			cout<<"Warning: Can't init linearing filter!";
		}
		gWindow = SDL_CreateWindow("Flappy Bird 1.0 made by Phong <3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "Can't create window! " << SDL_GetError();
			success = 0;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				cout << "Can't create renderer! " << SDL_GetError();
				success = 0;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();
					success = false;
				}

				
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048) < 0)
				{
					cout << "Can't init mixer! " << TTF_GetError();
					success = false;
				}
			}
		}
	}
	return success;
}
void loadMedia()
{
	gBirdTexture.loadFromFile("imageSource/bird.png");
	gBackgroundTexture.loadFromFile("imageSource/background.png");
	gPipeTexture.loadFromFile("imageSource/pipe.png");
	gGroundTexture.loadFromFile("imageSource/ground.png");
	gRestartTexture.loadFromFile("imageSource/restart_out.png");
	
	gPromptTexture.loadFromFile("imageSource/prompt.png");
	gDieSound = Mix_LoadWAV("audioSource/die.wav");
	gWingSound = Mix_LoadWAV("audioSource/wing.wav");
	gHitSound = Mix_LoadWAV("audioSource/hit.wav");
	gPointSound = Mix_LoadWAV("audioSource/point.wav");	
}
void gameInit(bool &isMenu, int &scrollOffset, int &frame, LBird &bird)
{
	isMenu = false;
	scrollOffset = 0;

	frame = 0;
	score = 0;
	bird.restart();
	pipes.clear();
	LDoublePipe pipe1;
	LDoublePipe pipe2(pipe1.PIPE_WIDTH + 197 + SCREEN_WIDTH * 2);
	pipes.push_back(pipe1);
	pipes.push_back(pipe2);
	gScoreFont = TTF_OpenFont("fontSource/FlappyFont.ttf", 60);
	gHighestScoreFont = TTF_OpenFont("fontSource/FlappyFont.ttf", 18);
}
void close()
{
	gBirdTexture.free();
	birdTimer.stop();
	pipes.clear();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

}

int main(int argc, char *args[])
{
	if (!init())
	{
		cout << "Can't initialize!" << endl;
	}
	else 
	{
			SDL_Surface* icon;
			icon = IMG_Load("imageSource/icon.png");
			SDL_SetWindowIcon(gWindow, icon);
			loadMedia();
			srand((int)time(0));

			bool quit = false;
			SDL_Event e;
			LBird bird;
			int frame;
			int scrollOffset; //scroll of the ground texture pipes
			bool isMenu;

			gameInit(isMenu, scrollOffset, frame, bird);

			ifstream fileIn("data/highestScore.txt");
			fileIn >> highestScore; //get Highest score from file
			ofstream fileOut("data/highestScore.txt", ios::trunc); //open file to overload the highest score

			SDL_Color textColor = { 255, 255 ,255 };
			
			//initialize some variables
			while (!quit)
			{
				if (!isMenu)
				{
					fpsTimer.start();
					//start timer to calculate the time of a frame
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
						bird.handleEvent(e);
					}
					frame++;
					scrollOffset -= SCROLL_VELOCITY;
					if (scrollOffset < -gGroundTexture.getWidth()) scrollOffset = 0; //handle the scrollOffset of the groundTexture and the pipes

					if (frame == 72) frame = 0;
					if (frame % 24 == 0)
					{
						bird.mCurrentSprite++;
						if (bird.mCurrentSprite == 3) bird.mCurrentSprite = 0; 
						//handle the frame to change the CurrentSprite of bird each 12 frames
					}

					if (bird.isPlayed) for (int i = 0; i < pipes.size(); ++i) pipes[i].move();

					bird.move(isMenu);
					//move bird and pipes

					SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
					SDL_RenderClear(gRenderer);
					gBackgroundTexture.render(0, 0);
					if (bird.isPlayed) for (int i = 0; i < pipes.size(); ++i) pipes[i].render();
					gGroundTexture.render(scrollOffset, 560);
					gGroundTexture.render(scrollOffset + gGroundTexture.getWidth(), 560);
					bird.render();
					if (bird.isPlayed == 0)
					{
						TTF_Font* tempFont = TTF_OpenFont("fontSource/flappyFont.ttf", 20);
						string temp = "Press Space or Mouse Down to Start!";
						gStartTexture.loadFromRenderedText(temp, textColor, tempFont);
						gStartTexture.render(SCREEN_WIDTH / 2 - gStartTexture.getWidth() / 2, 120);
					}
					else
					{
						string s = to_string(score);
						string s2 = "Highest: " + to_string(highestScore);
						gScoreTexture.loadFromRenderedText(s, textColor, gScoreFont);
						gHighestScoreTexture.loadFromRenderedText(s2, textColor, gHighestScoreFont);
						gScoreTexture.render(SCREEN_WIDTH / 2 - gScoreTexture.getWidth() / 2, 30);
						gHighestScoreTexture.render(SCREEN_WIDTH / 2 - gHighestScoreTexture.getWidth() / 2, 85);
					}
					//render everything
					SDL_RenderPresent(gRenderer);

					int frameTicks = fpsTimer.getTicks();
					if (frameTicks < SCREEN_TICKS_PER_FRAME)
					{
						SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
					}
				}
				else
				{
					int restartX = SCREEN_WIDTH / 2 - gRestartTexture.getWidth() / 2;
					int restartY = 405;
					//coordinate of the restart texture
					SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
					SDL_RenderClear(gRenderer);

					gBackgroundTexture.render(0, 0);
					if (bird.isPlayed) for (int i = 0; i < pipes.size(); ++i) pipes[i].render();
					gGroundTexture.render(scrollOffset, 560);
					gGroundTexture.render(scrollOffset + gGroundTexture.getWidth(), 560);
					bird.fall();
					bird.render();
					gPromptTexture.render(SCREEN_WIDTH / 2 - gPromptTexture.getWidth() / 2, gBackgroundTexture.getHeight() / 2 - gPromptTexture.getHeight() / 2);
					gRestartTexture.render(restartX, restartY);
					gScoreFont = TTF_OpenFont("fontSource/FlappyFont.ttf", 40);
					gHighestScoreFont = TTF_OpenFont("fontSource/FlappyFont.ttf", 40);
					string s = to_string(score);
					string s2 = to_string(highestScore);
					gScoreTexture.loadFromRenderedText(s, textColor, gScoreFont);
					gHighestScoreTexture.loadFromRenderedText(s2, textColor, gHighestScoreFont);
					gScoreTexture.render(SCREEN_WIDTH / 2 - gScoreTexture.getWidth() / 2, SCREEN_HEIGHT / 2 - gPromptTexture.getHeight() / 2 + 25);
					gHighestScoreTexture.render(SCREEN_WIDTH / 2 - gHighestScoreTexture.getWidth() / 2, SCREEN_HEIGHT / 2 - gPromptTexture.getHeight() / 2 + 110);
					//render everything in the menu
					SDL_RenderPresent(gRenderer);

					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
						else if (e.type == SDL_KEYDOWN)
						{
							//if player press space then quit the menu and reset the game
							if (e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0)
							{
								gameInit(isMenu, scrollOffset, frame, bird);
							}

						}
						else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
						{
							
							int x, y;
							SDL_GetMouseState(&x, &y);
							bool inside = true; //check if the mouse is in the restart button or not
							if (x < restartX)
							{
								inside = false;
							}
							
							else if (x > restartX + gRestartTexture.getWidth())
							{
								inside = false;
							}
							
							else if (y < restartY)
							{
								inside = false;
							}
							
							else if (y > restartY + gRestartTexture.getHeight())
							{
								inside = false;
							}

							
							if (inside)
							{
							
								
								switch (e.type)
								{
								// if the mouse is inside and player press the mouse then reset the game and quit menu
								case SDL_MOUSEBUTTONUP:
									gameInit(isMenu, scrollOffset, frame, bird);
									break;
								}
							}
						}
					}	
				}
			}
			
			fileOut << highestScore; //overload the highest score
			fileIn.close();
			fileOut.close();
		}
	
	close();
	return 0;
}
#### Table of contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [How to play](#play)
4. [Installation](#installation)

# Introduction <a name="introduction"></a>

* The game is inspired by the dog [Kabosu](https://wikipedia.org/wiki/Doge_(meme)) - one of the hottest memes from 2013 until now and [Flappy Bird](https://wikipedia.org/wiki/Flappy_Bird) - the famous Vietnamese game developed by Nguyen Ha Dong in 2013.
* Flappy Doge was created using [SDL2](https://www.libsdl.org/download-2.0.php) and C++.

_*The resources used in the game are collected from the Internet and most of them have been edited to suit the property of the game, the edit files are saved at the path ./code/res/psd._

<p align="center">
<img width="640" height="480" src="https://i.pinimg.com/originals/02/98/fa/0298fa4e7f8b0495169b2e964f06d7f2.jpg">
</p>

# Features <a name="features"></a>

**1. GameWindow**
* Handles collisions between characters and pipes, the ground, and borders on windows.
* Handles the player's key/mouse actions.
* Display score, game status icon (play/pause).
* The ground, moving characters make the game more realistic.
* Limit FPS to be compatible with all devices (if not, when running the game on a high-configuration machine, the image will be rendered too fast, causing the "fast forward" effect).

**2. TabPause**
* Enable/Mute the game.
* Light/Dark interface (changes immediately after selection).
* View current score, highest score.
* Play next icon.

**3. TabGameOver**
* Display medals corresponding to the number of points (Gold > 50, Silver > 20, Honor <= 20).
* View current score, highest score.
* Play next icon.

# How to play <a name="play"></a>
* Click mouse or press SPACE/UP key to play.
* Press ESC to pause.
* Video demo at [Youtube](https://youtu.be/LihM4SI81ug).

<p align="center">
<img src="https://i.imgur.com/dvni6mF.png">
</p>

# Installation <a name="installation"></a>

After installing [Mingw64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z/download), [SDL2](https://www.libsdl.org/download-2.0.php), [SDL_Image](https://www.libsdl.org/projects/SDL_image), [SDL_TTF](https://www.libsdl.org/projects/SDL_ttf), và [SDL_Mixer](https://www.libsdl.org/projects/SDL_mixer), run **Flappy Doge.exe** to enter the game.

_* You may not need to install SDL2, SDL_Image, SDL_TTF and SDL_Mixer because the **.dll** files are already in the ./res/sdl path._

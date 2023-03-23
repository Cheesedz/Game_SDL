#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RenderGame.hpp"

//Define a game pointer
Game* Mygame = nullptr;

int main(int argc, char* args[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Mygame = new Game();

	//Initial game screen 
	Mygame->init("Game v1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 640, false);
	
	//Operator -> is to access to function
	while (Mygame->running())
	{
		frameStart = SDL_GetTicks();

		Mygame->handleEvent();
		Mygame->upDate();
		Mygame->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	Mygame->clear();
	return 0;
}

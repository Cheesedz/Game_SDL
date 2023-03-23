#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Game
{
public:
	//Constructor
	Game();
	//Destructor
	~Game();

	//Initial game screen
	void init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
	
	//Handle game event
	void handleEvent();

	void render();

	//Update game status
	void upDate();

	//Clear memory when game finished
	void clear();
	
	//Let the main function whether tha game is running
	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	
private:
	
	bool isRunning;
	SDL_Window* window;

};

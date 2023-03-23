#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"
#include "GameObject.h"
#include "Component.h"

GameObject* player;
GameObject* enemy;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newplayer(manager.addEntity());

Game::Game() {}

Game::~Game() {}

int cnt = 0;

void Game::init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen)
{
	//Control fullscreen or not
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	//Create game window
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem Initialized successfully!" << std::endl;
		//Initial window
		window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
		if (window)
		{
			std::cout << "Window created successfully!" << std::endl;
		}

		//Initial renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created successfully!" << std::endl;
		}

		//Update running status
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player = new GameObject("Boss.png", 0, 0);
	enemy = new GameObject("Six.bmp", 100, 100);
	map = new Map();
	newplayer.addComponent<PositionComponent>();
	//player.addComponent<SpriteComponent>("Knight.png");
	
}

//Handle event
void Game::handleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;

		default: 
			break;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->drawMap();
	player->render();
	enemy->render();
	SDL_RenderPresent(renderer);
}

void Game::upDate()
{
	player->upDate();
	enemy->upDate();
	//manager.fresh();
	manager.upDate();
	std::cout << newplayer.getComponent<PositionComponent>().x()
		<< ";" << newplayer.getComponent<PositionComponent>().y() << std::endl;

	/*if (player.getComponent<PositionComponent>().x() > 100)
	{
		player.getComponent<SpriteComponent>().setTex("Boss.png");
	}*/
}

//Clear all the game opponent
void Game::clear()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned successfully!" << std::endl;
}

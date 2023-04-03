#include "CommonFunction.h"
#include "BaseObject.h"
#include "Map.h"
#include "MainObject.h"
#include "Timer.h"

BaseObject gBackground;

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gWindow = SDL_CreateWindow("Game v1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if (gWindow == NULL)
	{
		success = false;
	}
	else {
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL) success = false;
		else
		{
			SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags)) success = false;
		}
	}
	return success;
}

bool LoadBackground()
{
	bool ret = gBackground.LoadImg("res//deadCity.png", gRenderer);
	if (ret == false) return false;

	return true;
}

void clear()
{
	gBackground.Free();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	Timer fps_timer;
	if (InitData() == false)
	{
		std::cout << "Failed to load data" << std::endl;
		return -1;
	}

	if (LoadBackground() == false)
	{
		std::cout << "Failed to load background" << std::endl;
		return -1;
	}

	GameMap gameMap;
	char path[] = "map//map01.txt";
	gameMap.LoadMap(path);
	gameMap.LoadTiles(gRenderer);


	MainObject player;
	player.LoadImg("res//megaman_right.png", gRenderer);
	player.SetClips();

	bool isQuit = false;
	while (!isQuit)
	{
		fps_timer.start();
		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
			{
				isQuit = true;
			}
			player.HandleInputEvent(gEvent, gRenderer);
		}
		SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(gRenderer);


		gBackground.Render(gRenderer, NULL);

		//gameMap.Drawmap(gRenderer);

		Map map_data = gameMap.getMap();

		player.HandleBullet(gRenderer);

		player.SetMapXY(map_data.start_x, map_data.start_y);

		player.actionPlayer(map_data);

		player.Show(gRenderer);

		gameMap.SetMap(map_data);

		gameMap.Drawmap(gRenderer);

		SDL_RenderPresent(gRenderer);
		
		int real_time = fps_timer.get_ticks();
		int time_per_frame = 1000 / FPS;

		if (real_time < time_per_frame)
		{
			int delay_time = time_per_frame - real_time;
			if (delay_time >= 0) SDL_Delay(delay_time);
		}
	}

	clear();
	return 0;
}

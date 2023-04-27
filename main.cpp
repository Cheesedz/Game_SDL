#include "CommonFunction.h"
#include "BaseObject.h"
#include "Map.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "Timer.h"
#include "Hit.h"
#include "Text.h"
#include "Energy.h"
#include "Menu.h"
#include "Boss.h"

BaseObject gBackground;

Menu gMenu;

bool gotoMenu;

TTF_Font* font;

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gWindow = SDL_CreateWindow("MEGAMAN ADVENTURE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
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

	if (TTF_Init() == -1)
	{
		success = false;
	}

	font = TTF_OpenFont("font//PublicPixel-z84yD.ttf", 20);
	if (font == NULL)
	{
		success = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		/*printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());*/
		success = false;
	}

	//The sound effects that will be used
	Mix_Music* gMusic = Mix_LoadMUS("sound effect//game_theme.wav");

	Mix_Chunk* gFire = Mix_LoadWAV("sound effect//fire.wav");
	Mix_Chunk* gOption = Mix_LoadWAV("sound effect//opt.wav");
	Mix_Chunk* gExplosion = Mix_LoadWAV("sound effect//boom.wav");
	Mix_Chunk* gHurt = Mix_LoadWAV("sound effect//boom.wav");
	Mix_Chunk* gRing = Mix_LoadWAV("sound effect//get_energy.wav");
	Mix_Chunk* gWin = Mix_LoadWAV("sound effect//win.wav");
	Mix_Chunk* gLose = Mix_LoadWAV("sound effect//lose.wav");
	return success;
}


bool LoadMenuGame()
{
	bool ret = gMenu.LoadImg("menu//mainmenu1.png", gRenderer);
	if (ret == false) return false;
	return true;
}

bool LoadBackground()
{
	bool ret = gBackground.LoadImg("res//deadCity.png", gRenderer);
	if (ret == false) return false;
	return true;
}

bool LoadEndScreen()
{
	bool ret = gMenu.LoadImg("menu//PLAY_AGAIN.png", gRenderer);
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

	//Free the sound effects
	Mix_FreeChunk(gFire);
	Mix_FreeChunk(gWin);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gHurt);
	Mix_FreeChunk(gOption);
	Mix_FreeChunk(gRing);
	Mix_FreeChunk(gExplosion);

	gFire = NULL;
	gOption = NULL;
	gExplosion = NULL;
	gHurt = NULL;
	gRing = NULL;
	gWin = NULL;
	gLose = NULL;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

std::vector<ThreatObject*> CreateThreatList()
{
	std::vector<ThreatObject*> listThreat;
	int ENEMY_NUM = gMenu.getEnemyNum();
	ThreatObject* motivate_threat = new ThreatObject[ENEMY_NUM];
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		ThreatObject* p_threat = (motivate_threat + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("res//enemy_left.png", gRenderer);
			p_threat->setClip();
			p_threat->set_type_move(ThreatObject::MOVE_IN_SPACE);
			p_threat->set_x_pos(500 + i * 1000);
			p_threat->set_y_pos(250);

			int pos1 = p_threat->get_x_pos() - 60;
			int pos2 = p_threat->get_y_pos() + 60;
			p_threat->setAnimationPos(pos1, pos2);
			p_threat->setInputLeft(1);
			listThreat.push_back(p_threat);
		}
	}

	ThreatObject* threatObj = new ThreatObject[ENEMY_NUM];

	for (int i = 0; i < ENEMY_NUM; i++)
	{
		ThreatObject* p_threat = threatObj + i;
		if (p_threat != NULL)
		{
			p_threat->LoadImg("res//enemy_fire_left.png", gRenderer);
			p_threat->setClip();
			p_threat->set_x_pos(700 + i * 1000);
			p_threat->set_y_pos(250);
			p_threat->set_type_move(ThreatObject::THREAT);
			//p_threat->setInputLeft(0);

			Bullet* p_bullet = new Bullet();
			p_threat->InitBullet(p_bullet, gRenderer);

			listThreat.push_back(p_threat);

		}
	}
	return listThreat;
}

int mainGame()
{
	bool gameOver = false;

	Timer fps_timer;

	if (gExplosion == NULL)
	{
		gExplosion = Mix_LoadWAV("sound effect//boom.wav");
	}

	if (gLose == NULL)
	{
		gLose = Mix_LoadWAV("sound effect//lose.wav");
	}
	if (gWin == NULL)
	{
		gWin = Mix_LoadWAV("sound effect//win.wav");
	}
	if (gMusic == NULL)
	{
		gMusic = Mix_LoadMUS("sound effect//game_theme.wav");
	}
	if (LoadBackground() == false)
	{
		/*std::cout << "Failed to load background" << std::endl;*/
		return -1;
	}

	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(gMusic, -1);
	}

	GameMap gameMap;
	char path[] = "map//map01.txt";
	gameMap.LoadMap(path);
	gameMap.LoadTiles(gRenderer);

	MainObject player;
	player.LoadImg("res//megaman_right.png", gRenderer);
	player.SetClips();

	Energy player_energy;
	player_energy.Init(gRenderer);

	std::vector<ThreatObject*> threat_list = CreateThreatList();

	Hit hit_player;
	bool playerRet = hit_player.LoadImg("res//explosion.png", gRenderer);
	hit_player.setClip();
	if (!playerRet) return -1;
	
	int life = 3;

	Text timeGame;
	timeGame.SetColor(Text::WHITE);

	Text score_text;
	score_text.SetColor(Text::WHITE);
	UINT score = 0;

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
			player.HandleInputEvent(gEvent, gRenderer, gFire);
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

		player_energy.Show(gRenderer);

		for (int i = 0; i < threat_list.size(); i++)
		{
			ThreatObject* p_threat = threat_list.at(i);
			if (p_threat != NULL)
			{
				p_threat->setMapXY(map_data.start_x, map_data.start_y);
				p_threat->moveType(gRenderer);
				p_threat->actionThreat(map_data);
				p_threat->CreateThreatBullet(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(gRenderer);

				SDL_Rect rect_player = player.getRectFrame();
				bool bulletCol1 = false;
				std::vector<Bullet*> threat_bullet_list = p_threat->getBulletList();
				for (int j = 0; j < threat_bullet_list.size(); j++)
				{
					Bullet* p_threat_bullet = threat_bullet_list.at(j);
					if (p_threat_bullet)
					{
						bulletCol1 = SDLCommonFunction::checkCollision(p_threat_bullet->GetRect(), rect_player);
						if (bulletCol1)
						{
							int frame_hit_width = hit_player.get_frame_width();
							int frame_hit_height = hit_player.get_frame_height();

							for (int k = 0; k < HIT_NUM_FRAME; k++)
							{
								int x_pos = (player.GetRect().x + player.get_width_frame() * 0.5) - frame_hit_width * 0.5;
								int y_pos = (player.GetRect().y + player.get_height_frame() * 0.5) - frame_hit_height * 0.5;

								hit_player.set_frame(k);
								hit_player.SetRect(x_pos, y_pos);
								/*player.Free();*/
								hit_player.Show(gRenderer);
								SDL_RenderPresent(gRenderer);

							}
							Mix_PlayChannel(-1, gExplosion, 0);
							p_threat->RemoveBullet(j);
							break;
						}
					}
				}

				SDL_Rect rect_threat = p_threat->getRectFrame();
				bool bulletCol2 = SDLCommonFunction::checkCollision(rect_player, rect_threat);
				if (bulletCol1 || bulletCol2)
				{
					int frame_hit_width = hit_player.get_frame_width();
					int frame_hit_height = hit_player.get_frame_height();

					for (int k = 0; k < HIT_NUM_FRAME; k++)
					{
						int x_pos = (player.GetRect().x + player.get_width_frame() * 0.5) - frame_hit_width * 0.5;
						int y_pos = (player.GetRect().y + player.get_height_frame() * 0.5) - frame_hit_height * 0.5;
						
						hit_player.set_frame(k);
						hit_player.SetRect(x_pos, y_pos);
						/*player.Free();*/
						hit_player.Show(gRenderer);
						SDL_RenderPresent(gRenderer);
						
					}

					Mix_PlayChannel(-1, gExplosion, 0);
					
					life--;
					if (life > 0)
					{
						player.SetClips();
						player.SetRect(0, 0);
						player.setRespawnTime(10);
						
						/*
						player.LoadImg("res//megaman_right.png", gRenderer);*/
						SDL_Delay(100);
						player_energy.decreaseLife();
						player_energy.Render(gRenderer);
						/*hit_threat.Show(gRenderer);*/
						/*SDL_RenderPresent(gRenderer);*/
						continue;
					}
					else
					{
						Mix_PauseMusic();
						Mix_PlayChannel(-1, gLose, 0);
						if (MessageBox(NULL, L" YOU DIED ", L" GAME OVER ", MB_RETRYCANCEL | MB_ICONSTOP) == IDCANCEL)
						{
							/*p_threat->Free();
							clear();*/
							SDL_Quit();
							return 0;
						}
						else
						{
							Mix_ResumeMusic();
							mainGame();
						}

					}
				}

			}
		}

		int frame_hit_width = hit_player.get_frame_width();
		int frame_hit_height = hit_player.get_frame_height();
		
		std::vector<Bullet*> bullet_arr = player.getBulletList();
		for (int i = 0; i < bullet_arr.size(); i++)
		{
			Bullet* p_bullet = bullet_arr.at(i);
			if (p_bullet != NULL)
			{
				for (int j = 0; j < threat_list.size(); j++)
				{
					int cnt = 0;
					ThreatObject* obj_threat = threat_list.at(j);
					if (obj_threat != NULL)
					{
						SDL_Rect threat_rect;
						threat_rect.x = obj_threat->GetRect().x;
						threat_rect.y = obj_threat->GetRect().y;
						threat_rect.w = obj_threat->get_width_frame();
						threat_rect.h = obj_threat->get_height_frame();

						SDL_Rect bullet_rect = p_bullet->GetRect();

						bool bulletCol = SDLCommonFunction::checkCollision(bullet_rect, threat_rect);

						if (bulletCol)
						{
							cnt++;
							
							for (int k = 0; k < HIT_NUM_FRAME; k++)
							{
								int x_pos = p_bullet->GetRect().x - frame_hit_width * 0.5;
								int y_pos = p_bullet->GetRect().y - frame_hit_height * 0.5;

								hit_player.set_frame(k);
								hit_player.SetRect(x_pos, y_pos);
								hit_player.Show(gRenderer);


							}
							Mix_PlayChannel(-1, gExplosion, 0);
							player.RemoveBullet(i);
							/*if (cnt == 3)
							{
								cnt = 0;*/
								score += 150;
								obj_threat->Free();
								threat_list.erase(threat_list.begin() + j);
							//}
							
						}
					}
				}
			}
		}

		std::string str_time = "TIME: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		Uint32 val_time = gMenu.getGameTime() - time_val;
		if (val_time <= 0)
		{
			
			gMenu.HandleMainMenu(gEvent);
			gMenu.Show(gRenderer);
			SDL_RenderPresent(gRenderer);*/
			Mix_PauseMusic();
			Mix_PlayChannel(-1, gLose, 0);
			if (MessageBox(NULL, L" TIME OUT ", L" GAME OVER ", MB_RETRYCANCEL | MB_ICONSTOP) == IDCANCEL)
			{
				isQuit = true;
				break;
			}
			else
			{
				Mix_ResumeMusic();
				mainGame();
			}
			
		}
		else
		{
			std::string str_val = std::to_string(val_time);
			str_time += str_val;

			timeGame.SetText(str_time);
			timeGame.LoadFromRenderText(font, gRenderer);
			timeGame.RenderText(gRenderer, SCREEN_WIDTH - 300, 10);


			std::string val_str_score = std::to_string(score);
			std::string strScore("Score: ");
			strScore += val_str_score;

			score_text.SetText(strScore);
			score_text.LoadFromRenderText(font, gRenderer);
			score_text.RenderText(gRenderer, SCREEN_WIDTH * 0.5 - 40, 10);
		}

		if (player.GetRect().x == SCREEN_WIDTH - 10)
		{
			Mix_PlayChannel(-1, gWin, 0);
			if (MessageBox(NULL, L" YOU WIN ", L" CONGRATULATION ", MB_RETRYCANCEL | MB_ICONSTOP) == IDCANCEL)
			{
				/*p_threat->Free();
				clear();*/
				SDL_Quit();
				return 0;
			}
			else
			{
				mainGame();
			}
		}

		/*std::string val_str_score = std::to_string(score);
		std::string strScore("Score: ");
		strScore += val_str_score;

		score_text.SetText(strScore);
		score_text.LoadFromRenderText(font, gRenderer);
		score_text.RenderText(gRenderer, SCREEN_WIDTH * 0.5 - 40, 10);*/

		/*int count_energy = player.getEnergy();
		std::string energy_str = std::to_string(count_energy);
		energy.SetText(energy_str);
		energy.LoadFromRenderText(font, gRenderer);
		energy.RenderText(gRenderer, SCREEN_WIDTH * 0.5 - 400, 10);*/

		/*int val = MAX_MAP_X * TILE_SIZE - (map_data.start_x + player.GetRect().x);
		if (val <= SCREEN_WIDTH)
		{
			boss.SetMapXY(map_data.start_x, map_data.start_y);
			boss.actionBoss(map_data);
			boss.CreateBullet(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			boss.Show(gRenderer);
		}*/
		

		SDL_RenderPresent(gRenderer);

		int real_time = fps_timer.get_ticks();
		int time_per_frame = 1000 / FPS;

		if (real_time < time_per_frame)
		{
			int delay_time = time_per_frame - real_time;
			if (delay_time >= 0) SDL_Delay(delay_time);
		}
	}
	return 1;
}

void HandleGameLoop()
{
	bool isQuit = false;
	while (!isQuit)
	{
		/*fps_timer.start();*/

		while (SDL_PollEvent(&gEvent) != 0)
		{
			if (gEvent.type == SDL_QUIT)
			{
				isQuit = true;
			}
			gMenu.HandleMainMenu(gEvent, gOption);
			gMenu.ShowMainMenu(gRenderer);
			SDL_RenderPresent(gRenderer);

			if (gMenu.startingGame())
			{
				/*mainGame();*/
				if (mainGame() == 0)
				{
					/*while (SDL_PollEvent(&gEvent) != 0)
					{
						if (gEvent.type == SDL_QUIT)
						{
							isQuit = true;
						}*/
						SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
						SDL_RenderClear(gRenderer);
						gMenu.HandleEndScreen(gEvent);
						gMenu.ShowEndScreen(gRenderer);
						SDL_RenderPresent(gRenderer);
					/*}*/
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	if (InitData() == false)
	{
		std::cout << "Failed to load data" << std::endl;
		return -1;
	}
	if (LoadMenuGame() == false)
	{
		std::cout << "Failed to load menu" << std::endl;
		return -1;
	}
	do
	{
		gotoMenu = false;
		HandleGameLoop();
	} 
	while (gotoMenu == true);
	clear();
	return 0;
}

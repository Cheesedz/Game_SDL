#include "Menu.h"
#include "Timer.h"

Menu::Menu()
{
	choose = 1;
	enter = 0;
	enterMode = 0;
	esc = 0;
	selectMode = 1;
	selectGameOver = 1;
	enterGameOver = 0;
	getInMode = 0;
	input_type.up = 0;
	input_type.down = 0;
	startGame = false;
	GotoMenu = false;
	win = false;
	status = 0;
	gameTime = MODE_EASY;
}

Menu::~Menu()
{

}

bool Menu::LoadImg(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		newTexture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (newTexture != NULL)
		{
			rect.w = load_surface->w;
			rect.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}

	p_object = newTexture;

	return p_object != NULL;
}

void Menu::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };

	SDL_RenderCopy(des, p_object, clip, &renderquad);
}


void Menu::Free()
{
	if (p_object != NULL)
	{
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}

void Menu::ShowMainMenu(SDL_Renderer* des)
{
	if (win)
	{
		LoadImg("menu//win.png", des);
		SDL_Delay(15000);
	}

	//switch (choose % 3)
	//{
	//case START_GAME:
	//	{
	//		if (esc == 1 || win)
	//		{
	//			LoadImg("menu//mainmenu1.png", des);
	//		}

	//		if (enter == 1) startGame = true;
	//	}
	//	break;
	//case GAME_MODE:
	//	{
	//		LoadImg("menu//mainmenu2.png", des);
	//		if (enterMode == 1)
	//		{
	//			LoadImg("menu//mode_easy.png", des);
	//			/*status = GAME_MODE;*/
	//
	//			if (input_type.up == 1)
	//			{
	//				selectMode--;
	//			}
	//			else if (input_type.down == 1)
	//			{
	//				selectMode++;
	//			}
	//			if (select
	//		}
	//		if (selectMode % 3 == 2)
	//		{
	//			LoadImg("menu//mode_normal.png", des);
	//			if (input_type.up == 1)
	//			{
	//				selectMode--;
	//			}
	//			else if (input_type.down == 1)
	//			{
	//				selectMode++;
	//			}
	//		}
	//		if (selectMode % 3 == 0)
	//		{
	//			LoadImg("menu//mode_hard.png", des);
	//			if (input_type.up == 1)
	//			{
	//				selectMode--;
	//			}
	//			else if (input_type.down == 1)
	//			{
	//				selectMode++;
	//			}
	//		}
	//		if (selectMode % 3 == 1 && enter == 1)
	//		{
	//			gameTime = MODE_EASY;
	//			choose = 1;
	//			break;
	//		}
	//		if (selectMode % 3 == 2 && enter == 1)
	//		{
	//			gameTime = MODE_NORMAL;
	//			choose = 1;
	//			break;
	//		}
	//		if (selectMode % 3 == 0 && enter == 1)
	//		{
	//			gameTime = MODE_HARD;
	//			choose = 1;
	//			break;
	//		}
	//	}
	//	break;
	//case HOW_TO_PLAY:
	//	{
	//		LoadImg("menu//mainmenu3.png", des);
	//		if (enter == 1)
	//		{
	//			LoadImg("menu//how to play.png", des);
	//		}
	//		if (esc == 1)
	//		{
	//			choose = 1;
	//			break;
	//		}
	//	}
	//	break;
	//}
	

	if (choose%3 == START_GAME || esc == 1 || win == true)
	{
		LoadImg("menu//mainmenu1.png",des);
	}
	if (choose % 3 == START_GAME && enter == 1)
	{
		startGame = true;
	}

	if (choose % 3 == GAME_MODE)
	{
		LoadImg("menu//mainmenu2.png", des);
		status = GAME_MODE;
		if (enterMode == 1)
		{
			/*status = GAME_MODE;*/
			if (input_type.up == 1)
			{
				selectMode--;
			}
			else if (input_type.down == 1)
			{
				selectMode++;
			}

			if (selectMode % 3 == 1)
			{
				LoadImg("menu//mode_easy.png", des);
				if (getInMode == 1)
				{
					gameTime = MODE_EASY;
					esc = 1;
					enterMode = 0;
					getInMode = 0;
				}
			}
			if (selectMode % 3 == 2)
			{
				LoadImg("menu//mode_normal.png", des);
				if (getInMode == 1)
				{
					gameTime = MODE_NORMAL;
					esc = 1;
					enterMode = 0;
					getInMode = 0;
				}
			}
			if (selectMode % 3 == 0)
			{
				LoadImg("menu//mode_hard.png", des);
				if (getInMode == 1)
				{
					gameTime = MODE_HARD;
					esc = 1;
					enterMode = 0;
					getInMode = 0;
				}
			}
		}
	}
	
	//if (choose % 3 == GAME_MODE && enter == 1)
	//{
	//	LoadImg("menu//mode_easy.png", des);
	//	status = GAME_MODE;
	//	/*gameTime = MODE_EASY;*/
	//	choose = 1;
	//}

	//if (status == GAME_MODE && choose % 3 == 2 /*&& enter == 1*/)
	//{
	//	LoadImg("menu//mode_normal.png", des);
	//	/*gameTime = MODE_NORMAL;*/
	//}


	//if (status == GAME_MODE && choose % 3 == 0 /*&& enter == 1*/)
	//{
	//	LoadImg("menu//mode_hard.png", des);
	//	/*gameTime = MODE_HARD;
	//	esc = 1;*/
	//}

	if (choose % 3 == HOW_TO_PLAY)
	{
		LoadImg("menu//mainmenu3.png", des);
		if (enter == 1)
		{
			LoadImg("menu//how to play.png", des);
		}
	}

	/*if (choose%3 == HOW_TO_PLAY && enter == 1)
	{
		LoadImg("menu//how to play.png", des);
	}*/

	if (/*status != GAME_MODE && */enterMode != 1)
	{
		if (input_type.up == 1)
		{
			choose--;
		}
		else if (input_type.down == 1)
		{
			choose++;
		}
	}
	
	/*if (choose > 3) choose = 1;*/
	Render(des);
}

void Menu::HandleMainMenu(SDL_Event events)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
		{
			input_type.up = 1;
			input_type.down = 0;
			if (status != GAME_MODE)
			{
				enterMode = 0;
				getInMode = 0;
			}
			enter = 0;
			/*enterGameOver = 0;*/
			esc = 0;
			SDL_Delay(100);
		}
		break;

		case SDLK_DOWN:
		{
			input_type.up = 0;
			input_type.down = 1;
			if (status != GAME_MODE)
			{
				enterMode = 0;
				getInMode = 0;
			}
			enter = 0;
			/*enterGameOver = 0;*/
			esc = 0;
			SDL_Delay(100);
		}
		break;

		case SDLK_SPACE:
			if (enterMode == 1) getInMode = 1;
			if (status == GAME_MODE) enterMode = 1;
			/*if (status == GAME_OVER) enterGameOver = 1;*/
			enter = 1;
		break;

		case SDLK_ESCAPE:
			esc = 1;
			enter = 0;
			enterMode = 0;
			getInMode = 0;
			/*enterGameOver = 0;*/
		break;

		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
		{
			input_type.up = 0;
		}
		break;

		case SDLK_DOWN:
		{
			input_type.down = 0;
		}
		break;

		default:
			break;
		}

	}
}

void Menu::ShowEndScreen(SDL_Renderer* des)
{
	LoadImg("menu//PLAY_AGAIN.png", des);
	if (selectGameOver % 3 == 1)
	{
		LoadImg("menu//PLAY_AGAIN.png", des);
		if (enterGameOver == 1)
		{
			startGame = true;
		}
	}

	if (selectGameOver % 3 == 2)
	{
		LoadImg("menu//BACK_TO_MENU.png", des);
		if (enterGameOver == 1)
		{
			GotoMenu = true;
		}
	}

	if (selectGameOver % 3 == 0)
	{
		LoadImg("menu//EXIT_GAME.png", des);
		if (enterGameOver == 1)
		{
			SDL_Quit();
		}
	}
	if (input_type.down == 1)
	{
		selectGameOver++;
	}
	if (input_type.up == 1)
	{
		selectGameOver--;
	}
}

void Menu::HandleEndScreen(SDL_Event events)
{
	startGame = false;
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
		{
			input_type.up = 1;
			input_type.down = 0;
			enterGameOver = 0;
			esc = 0;
			SDL_Delay(100);
		}
		break;

		case SDLK_DOWN:
		{
			input_type.up = 0;
			input_type.down = 1;
			enterGameOver = 0;
			esc = 0;
			SDL_Delay(100);
		}
		break;

		case SDLK_SPACE:
			enterGameOver = 1;
			break;

		case SDLK_ESCAPE:
			esc = 1;
			enterGameOver = 0;
			break;

		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
		{
			input_type.up = 0;
		}
		break;

		case SDLK_DOWN:
		{
			input_type.down = 0;
		}
		break;

		default:
			break;
		}

	}
}

bool Menu::startingGame()
{
	return startGame;
}

bool Menu::isWin()
{
	return win;
}

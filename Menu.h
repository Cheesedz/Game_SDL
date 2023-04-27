#pragma once
#include "CommonFunction.h"
#include "BaseObject.h"

#define GAME_OVER 3
#define START_GAME 1
#define GAME_MODE 2
#define HOW_TO_PLAY 0
#define MODE_EASY 300
#define MODE_NORMAL 250
#define MODE_HARD 200

class Menu : public BaseObject
{
public:
	Menu();
	~Menu();
	bool LoadImg(std::string path, SDL_Renderer* screen);

	void ShowMainMenu(SDL_Renderer* des);

	void ShowEndScreen(SDL_Renderer* des);

	void HandleMainMenu(SDL_Event events, Mix_Chunk* gOption);

	void HandleGameMode(SDL_Event events);

	void HandleEndScreen(SDL_Event events);

	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

	void Free();

	bool startingGame();

	bool gotoMenu() { return GotoMenu; }
	
	bool isWin() ;

	int getGameTime() const { return gameTime; }

	int getEnemyNum() const { return enemyNum; }

private:
	SDL_Texture* p_object;
	SDL_Rect rect;
	int choose;
	int selectMode;
	int selectGameOver;
	int enter;
	int enterGameOver;
	int enterMode;
	int getInMode;
	int esc;
	Input input_type;
	bool startGame;
	bool GotoMenu;
	bool win;
	int status;
	int gameTime;
	int enemyNum;
};

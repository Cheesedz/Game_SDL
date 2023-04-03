#pragma once

#include "CommonFunction.h"
#include "BaseObject.h"

#define MAX_TILES 20

class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};

class GameMap
{
public: 
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(char* name);

	void LoadTiles(SDL_Renderer* screen);

	void Drawmap(SDL_Renderer* screen);

	Map getMap() { return gameMap; };

	void SetMap(Map& mapData) { gameMap = mapData;  };
private:
	Map gameMap;
	TileMap tile_map[MAX_TILES];
};
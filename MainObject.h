#pragma once

#include <vector>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "Bullet.h"

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	bool LoadImg(std::string path, SDL_Renderer* screen);

	void Show(SDL_Renderer* des);

	void HandleInputEvent(SDL_Event events, SDL_Renderer* screen);

	void SetClips();

	void actionPlayer(Map& mapData);

	void checkMap(Map& mapData);

	void SetMapXY(const int mapX, const int mapY) { map_x = mapX; map_y = mapY; }
	
	void CenterEntityOnMap(Map& mapData);

	void setBulletList(std::vector<Bullet*> bulletList)
	{
		bullet_list = bulletList;
	}
	std::vector <Bullet*> getBulletList() const { return bullet_list; }

	void HandleBullet(SDL_Renderer* des);

	enum WalkType
	{
		WALK_RIGHT = 1,
		WALK_LEFT = 0,
		IDLE = 0,
	};

private:
	std::vector<Bullet*> bullet_list;

	double x_val;
	double y_val;

	double x_pos;
	double y_pos;

	int width_frame;
	int height_frame;

	SDL_Rect frame_clip[8];

	//Lưu trạng thái khung hình
	Input input_type;

	int frame;

	int status;

	bool onGround;

	int map_x;
	int map_y;

	int respawnTime;
};

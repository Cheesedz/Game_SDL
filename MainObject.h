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

	void HandleInputEvent(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* gFire);

	void SetClips();

	void actionPlayer(Map& mapData);

	void checkMap(Map& mapData);

	void SetMapXY(const int mapX, const int mapY) { map_x = mapX; map_y = mapY; }
	
	void CenterEntityOnMap(Map& mapData);

	void setBulletList(const std::vector<Bullet*> bulletList)
	{
		bullet_list = bulletList;
	}
	std::vector <Bullet*> getBulletList() const { return bullet_list; }

	void RemoveBulletList(/*std::vector<Bullet*> bullet_list*/);

	void HandleBullet(SDL_Renderer* des);

	void RemoveBullet(const int& index);

	int get_width_frame() { return width_frame; }

	int get_height_frame() { return height_frame; }

	void setRespawnTime(const int& respawn_time) { respawnTime = respawn_time; }

	bool increaseEnergy() const { return increase_energy; }

	int getEnergy() const { return energy_count; }



	SDL_Rect getRectFrame();

	enum WalkType
	{
		WALK_RIGHT = 1,
		WALK_LEFT = 0,
		IDLE = 0,
		JUMP = 0,
		FALL = 0,
	};

private:
	int PLAYER_JUMP_SPEED;

	int PLAYER_RUN_SPEED;

	int energy_count;

	bool increase_energy;

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

	long frame;

	int status;

	bool onGround;

	int map_x;
	int map_y;

	int respawnTime;
};

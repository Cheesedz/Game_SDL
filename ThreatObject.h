#pragma once

#include "BaseObject.h"
#include "CommonFunction.h"
#include "Bullet.h"

#define THREAT_FRAME_NUM 8
#define GRAVITY 0.8
#define MAX_FALL_SPEED 10
#define THREAT_SPEED 7

class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	enum TypeMove
	{
		THREAT = 0,
		MOVE_IN_SPACE = 1,
	};

	void set_x_val(const double& xVal) { x_val = xVal; }
	void set_y_val(const double& yVal) { y_val = yVal; }

	void set_x_pos(const double& xPos) { x_pos = xPos; }
	void set_y_pos(const double& yPos) { y_pos = yPos; }

	double get_x_pos() const { return x_pos; }
	double get_y_pos() const { return y_pos; }

	void setMapXY(const int& mapX, const int& mapY) { map_x = mapX; map_y = mapY; }

	void setClip();

	bool LoadImg(std::string, SDL_Renderer* screen);

	void Show(SDL_Renderer* des);

	int get_width_frame() const { return width_frame; }
	int get_height_frame() const { return height_frame; }

	void actionThreat(Map& mapData);

	void checkMap(Map& mapDat);

	void set_type_move(const int& typeMove) { type_move = typeMove; }

	void setAnimationPos(const int& pos_x, const int& pos_y) { animate_x = pos_x, animate_y = pos_y; }

	void setInputLeft(const int& left) { input_type.left = left; }

	void moveType(SDL_Renderer* screen);

	void respawn();

	std::vector <Bullet*> getBulletList() const { return bullet_list; }

	void setBulletList(const std::vector<Bullet*>& bulletList) { bullet_list = bulletList; }

	void InitBullet(Bullet* p_bullet, SDL_Renderer* screen);

	void CreateThreatBullet(SDL_Renderer* screen, const int& x_border, const int& y_border);

	void RemoveBullet(const int& index);

	SDL_Rect getRectFrame();

private:
	SDL_Rect frame_clip[THREAT_FRAME_NUM];
	bool isColision;
	bool onGround;
	int height_frame;
	int width_frame;
	int frame;
	int respawnTime;
	double x_val;
	double y_val;
	double x_pos;
	double y_pos;
	int map_x;
	int map_y;
	int type_move;
	int animate_x;
	int animate_y;
	Input input_type;
	std::vector<Bullet*> bullet_list;
};
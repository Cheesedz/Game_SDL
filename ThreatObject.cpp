#include "ThreatObject.h"
#define SPIKE 5
#define HEART 3

ThreatObject::ThreatObject()
{
	width_frame = 0;
	height_frame = 0;
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;
	onGround = false;
	isColision = false;
	respawnTime = 0;
	frame = 0;
	animate_x = 0;
	animate_y = 0;
	input_type.left = 0;
	type_move = THREAT;
}

ThreatObject::~ThreatObject()
{

}

bool ThreatObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret)
	{
		width_frame = rect.w / THREAT_FRAME_NUM;
		height_frame = rect.h;
	}
	return ret;
}

SDL_Rect ThreatObject::getRectFrame()
{
	SDL_Rect gRect;
	gRect.x = rect.x;
	gRect.y = rect.y;
	gRect.w = width_frame;
	gRect.h = height_frame;
	return gRect;
}

void ThreatObject::setClip()
{
	if (width_frame > 0 && height_frame > 0)
	{
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = width_frame;
		frame_clip[0].h = height_frame;

		frame_clip[1].x = width_frame;
		frame_clip[1].y = 0;
		frame_clip[1].w = width_frame;
		frame_clip[1].h = height_frame;

		frame_clip[2].x = 2 * width_frame;
		frame_clip[2].y = 0;
		frame_clip[2].w = width_frame;
		frame_clip[2].h = height_frame;

		frame_clip[3].x = 3 * width_frame;
		frame_clip[3].y = 0;
		frame_clip[3].w = width_frame;
		frame_clip[3].h = height_frame;

		frame_clip[4].x = 4*width_frame;
		frame_clip[4].y = 0;
		frame_clip[4].w = width_frame;
		frame_clip[4].h = height_frame;

		frame_clip[5].x = 5*width_frame;
		frame_clip[5].y = 0;
		frame_clip[5].w = width_frame;
		frame_clip[5].h = height_frame;

		frame_clip[6].x = 6*width_frame;
		frame_clip[6].y = 0;
		frame_clip[6].w = width_frame;
		frame_clip[6].h = height_frame;

		frame_clip[7].x = 7 * width_frame;
		frame_clip[7].y = 0;
		frame_clip[7].w = width_frame;
		frame_clip[7].h = height_frame;
	}
}

void ThreatObject::Show(SDL_Renderer* des)
{
	if (respawnTime == 0)
	{
		rect.x = x_pos - map_x;
		rect.y = y_pos - map_y;
		frame++;
		if (frame >= 7)
		{
			frame = 0;
		}
		SDL_Rect* currentClip = &frame_clip[frame];
		SDL_Rect rendQuad = { rect.x, rect.y, width_frame, height_frame };
		SDL_RenderCopy(des, p_object, currentClip, &rendQuad);
	}
}

void ThreatObject::actionThreat(Map& mapData)
{
	if (respawnTime == 0)
	{
		x_val = 0;
		y_val += GRAVITY;
		if (y_val >= MAX_FALL_SPEED)
		{
			y_val = MAX_FALL_SPEED;
		}

		if (input_type.left == 1)
		{
			x_val -= THREAT_SPEED;
		}
		else if (input_type.right == 1)
		{
			x_val += THREAT_SPEED;
		}
		checkMap(mapData);

	}
	else if (respawnTime > 0)
	{
		respawnTime --;
		if (respawnTime == 0)
		{
			respawn();
		}
	}
}

void ThreatObject::respawn()
{
	x_val = 0;
	y_val = 0;
	if (x_pos > 256)
	{
		x_pos -= 256;
		animate_x -= 256;
		animate_y -= 256;
	}
	else
	{
		x_pos = 0;
	}
	y_pos = 0;
	respawnTime = 0;
	input_type.left = 1;
}

void ThreatObject::checkMap(Map& mapData)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check horizontal
	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val > 0) //main opbject is moving to right
		{
			int val1 = mapData.tile[y1][x2];
			int val2 = mapData.tile[y2][x2];

			if ((val1 != BLANK_TILE && val1 != SPIKE && val1 != HEART) || (val2 != BLANK_TILE && val2 != SPIKE && val2 != HEART))
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= width_frame + 1;
				x_val = 0;
				isColision = true;
			}
		}
		else if (x_val < 0)
		{
			int val1 = mapData.tile[y1][x1];
			int val2 = mapData.tile[y2][x1];

			if (val1 == HEART || val2 == HEART)
			{
				mapData.tile[y1][x1] = 0;
				mapData.tile[y2][x1] = 0;
			}

			if ((val1 != BLANK_TILE && val1 != SPIKE && val1 != HEART) || (val2 != BLANK_TILE && val2 != SPIKE && val2 != HEART))
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
				isColision = true;
			}
		}
	}

	//Check vertical
	int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val > 0)
		{
			int val1 = mapData.tile[y2][x1];
			int val2 = mapData.tile[y2][x2];

			if (val1 == HEART || val2 == HEART)
			{
				mapData.tile[y2][x1] = 0;
				mapData.tile[y2][x2] = 0;
			}

			if ((val1 != BLANK_TILE && val1 != SPIKE && val1 != HEART) || (val2 != BLANK_TILE && val2 != SPIKE && val2 != HEART))
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= (height_frame + 1);
				y_val = 0;
				onGround = true;

			}
			//else onGround = false;
		}
		else if (y_val < 0)
		{

			int val1 = mapData.tile[y1][x1];
			int val2 = mapData.tile[y1][x2];

			if (val1 == HEART || val2 == HEART)
			{
				mapData.tile[y1][x1] = 0;
				mapData.tile[y1][x2] = 0;
			}

			if ((val1 != BLANK_TILE && val1 != SPIKE && val1 != HEART) || (val2 != BLANK_TILE && val2 != SPIKE && val2 != HEART))
			{
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
		}
	}

	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < 0)
	{
		x_pos = 0;
	}

	else if (x_pos + width_frame > mapData.max_x)
	{
		x_pos = mapData.max_x - width_frame - 1;
	}

	if (y_pos > mapData.max_y)
	{
		respawnTime = 500;
	}
}

void ThreatObject::moveType(SDL_Renderer* screen)
{
	if (type_move == THREAT)
	{

	}
	else if (type_move == MOVE_IN_SPACE)
	{
		
		if (onGround == true)
		{
			/*if (x_pos <= animate_x && x_pos >= animate_y)
			{
				if (isColision == true)
				{
					if (input_type.left == 1)
					{
						input_type.left = 0;
						input_type.right = 1;
						LoadImg("res//Boss_right.png", screen);
					}
					else if (input_type.right == 1)
					{
						input_type.right = 0;
						input_type.left = 1;
						LoadImg("res//Boss_left.png", screen);
					}
				}
			}*/

			if (x_pos > animate_x)
			{
				/*if (isColision == true)
				{
					input_type.right = 1;
					input_type.left = 0;
					LoadImg("res//Boss_right.png", screen);
				}
				else {*/
					input_type.left = 1;
					input_type.right = 0;
					LoadImg("res//enemy_left.png", screen);

				/*}*/
				
				
				
			}
			else if (x_pos < animate_y)
			{
				/*if (isColision == true)
				{
					input_type.right = 0;
					input_type.left = 1;
					LoadImg("res//Boss_left.png", screen);
				}
				else
				{
				*/	input_type.left = 0;
					input_type.right = 1;
					LoadImg("res//enemy_right.png", screen);

				/*}*/
				
				
			}
		}
		else
		{
			if (input_type.left == 1)
			{
				LoadImg("res//enemy_left.png", screen);
			}
		}
	}
}

void ThreatObject::InitBullet(Bullet* p_bullet, SDL_Renderer* screen)
{
	if (p_bullet != NULL)
	{
		p_bullet->LoadImg("res//Boss_bullet_left.png", screen);
		p_bullet->setIsMove(true);
		p_bullet->setBulletDirect(Bullet::DIR_LEFT);
		p_bullet->SetRect(x_pos + 20, y_pos + 25);
		p_bullet->setX(10);
		bullet_list.push_back(p_bullet);
	}
}

void ThreatObject::CreateThreatBullet(SDL_Renderer* screen, const int& x_border, const int& y_border)
{
	for (int i = 0; i < bullet_list.size(); i++)
	{
		Bullet* p_bullet = bullet_list.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->getIsMove())
			{
				p_bullet->HandleMove(x_border, y_border);
				p_bullet->Render(screen);
			}
			else
			{
				p_bullet->setIsMove(true);
				p_bullet->SetRect(x_pos + 5, y_pos + 10);
			}
		}
	}
}

void ThreatObject::RemoveBullet(const int& index)
{
	int size = bullet_list.size();
	if (size > 0 && index < size)
	{
		Bullet* p_bullet = bullet_list.at(index);
		bullet_list.erase(bullet_list.begin() + index);

		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}
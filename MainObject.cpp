#include "MainObject.h"
#include "Timer.h"

#define GRAVITY 1.2
#define MAX_FALL_SPEED 10
#define PLAYER_RUN_SPEED 15
#define PLAYER_JUMP_SPEED 15
#define HEART 3
#define ENERGY 2
#define SPIKE 4
#define SPIKE_INVERSE 99

MainObject::MainObject()
{
	frame = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;
	width_frame = 0;
	height_frame = 0;
	status = -1;
	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;
	input_type.jump = 0;
	map_x = 0;
	map_y = 0;
	respawnTime = 0;
}

int cooldown = 0;

MainObject :: ~MainObject()
{

}
void MainObject::increaseEnergy()
{
	energy_count++;
}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame = rect.w / 8;
		height_frame = rect.h;
	}
	return ret;
}

SDL_Rect MainObject::getRectFrame()
{
	SDL_Rect gRect;
	gRect.x = rect.x;
	gRect.y = rect.y;
	gRect.w = width_frame;
	gRect.h = height_frame;
	return gRect;
}

void MainObject::SetClips()
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

		frame_clip[2].x = 2*width_frame;
		frame_clip[2].y = 0;
		frame_clip[2].w = width_frame;
		frame_clip[2].h = height_frame;

		frame_clip[3].x = 3*width_frame;
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

		frame_clip[6].x =6* width_frame;
		frame_clip[6].y = 0;
		frame_clip[6].w = width_frame;
		frame_clip[6].h = height_frame;

		frame_clip[7].x = 7 * width_frame;
		frame_clip[7].y = 0;
		frame_clip[7].w = width_frame;
		frame_clip[7].h = height_frame;
	}
}

void MainObject::Show(SDL_Renderer* des)
{
	if (status == WALK_LEFT)
	{
		LoadImg("res//megaman_left.png", des);
	}
	else if (status == WALK_RIGHT)
	{
		LoadImg("res//megaman_right.png", des);
	}
	/*else if (status == JUMP)
	{
		LoadImg("res//Jump.png", des);
	}
	else if (status == FALL)
	{
		LoadImg("res//Fall.png", des);
	}*/

	if (input_type.left == 1 || input_type.right == 1)
	{
		frame++;
	}
	else
	{
		frame = 0;
	}

	if (frame >= 7) frame = 0;
	rect.x = x_pos - map_x;
	rect.y = y_pos - map_y;

	SDL_Rect* current_clip = &frame_clip[frame];

	SDL_Rect renderQuad = { rect.x, rect.y, width_frame, height_frame };

	SDL_RenderCopy(des, p_object, current_clip, &renderQuad);

}

void MainObject::HandleInputEvent(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			status = WALK_RIGHT;
			input_type.right = 1;
			input_type.left = 0;
			input_type.jump = 0;
			input_type.down = 0;
		}
		break;

		case SDLK_a:
		{
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			input_type.jump = 0;
			input_type.down = 0;
		}
		break;

		case SDLK_w:
		{
			/*status = JUMP;*/
			/*input_type.down = 0;*/
			input_type.jump = 1;
			
		}
		break;
		
		case SDLK_j:
		{
			cooldown++;
			if (cooldown > 3) cooldown = 0;
			if (cooldown == 0)
			{
				Bullet* bullet = new Bullet();

				if (status == WALK_LEFT)
				{
					bullet->LoadImg("res//blade_left.png", screen);
					bullet->setBulletDirect(Bullet::DIR_LEFT);
					bullet->SetRect(this->rect.x, rect.y + height_frame * 0.2);
				}
				else
				{
					bullet->LoadImg("res//blade_right.png", screen);
					bullet->setBulletDirect(Bullet::DIR_RIGHT);
					bullet->SetRect(this->rect.x + width_frame - 20, rect.y + height_frame * 0.2);
				}
				bullet->setX(20);
				bullet->setIsMove(true);

				bullet_list.push_back(bullet);

			}
			

		}
		
		break;

		default:
			break;
		}

	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			status = WALK_RIGHT;
			input_type.right = 0;
		}
		break;
		case SDLK_a:
		{
			status = WALK_LEFT;
			input_type.left = 0;
		}
		break;
		case SDLK_w:
		{
			input_type.jump = 0;
		}
		break;
		default:
			break;
		}

	}
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < bullet_list.size(); i++)
	{
		Bullet* bullet = bullet_list.at(i);
		if (bullet != NULL)
		{
			if (bullet->getIsMove() == true)
			{
				bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				bullet->Render(des);
			}
			else
			{
				bullet_list.erase(bullet_list.begin() + i);
				if (bullet != NULL)
				{
					delete bullet;
					bullet = NULL;
				}
			}
		}
	}
}

void MainObject::RemoveBullet(const int& index)
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

void MainObject::actionPlayer(Map& mapData)
{
	if (respawnTime == 0)
	{
		x_val = 0;
		y_val += 0.7;

		if (y_val >= MAX_FALL_SPEED)
		{
			y_val = MAX_FALL_SPEED;
		}

		if (input_type.left == 1)
		{
			x_val -= PLAYER_RUN_SPEED;
		}

		if (input_type.right == 1)
		{
			x_val += PLAYER_RUN_SPEED;
		}

		if (input_type.jump == 1)
		{
			if (onGround == true)
			{
				y_val -= PLAYER_JUMP_SPEED;
			}
			onGround = false;
			input_type.jump = 0;
		}

		checkMap(mapData);
		CenterEntityOnMap(mapData);
	}
	
	if (respawnTime > 0)
	{
		respawnTime--;
		if (respawnTime == 0)
		{
			if (x_pos > 256)
			{
				x_pos -= 256;
				map_x -= 256;
			}
			else
			{
				x_pos = 0;
			}
			y_pos = 0;
			x_val = 0;
			y_val = 0;
		}
	}
	
}

void MainObject::CenterEntityOnMap(Map& mapData)
{
	mapData.start_x = x_pos - (SCREEN_WIDTH / 2);
	if (mapData.start_x < 0)
	{
		mapData.start_x = 0;
	}
	else if (mapData.start_x + SCREEN_WIDTH >= mapData.max_x)
	{
		mapData.start_x = mapData.max_x - SCREEN_WIDTH;
	}

	mapData.start_y = y_pos - (SCREEN_HEIGHT / 2);
	if (mapData.start_y < 0)
	{
		mapData.start_y = 0;
	}
	else if (mapData.start_y + SCREEN_HEIGHT >= mapData.max_y)
	{
		mapData.start_y = mapData.max_y - SCREEN_HEIGHT;
	}
}

void MainObject::checkMap(Map& mapData)
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

			if (val1 == HEART || val2 == HEART)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
			}

			if (val1 == ENERGY || val2 == ENERGY)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				increaseEnergy();
			}

			if ((val1 != BLANK_TILE && val1 != SPIKE && val1 != SPIKE_INVERSE)|| (val2 != BLANK_TILE && val2 != SPIKE && val2 != SPIKE_INVERSE ))
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= width_frame + 1;
				x_val = 0;
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

			if (val1 == ENERGY || val2 == ENERGY)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				increaseEnergy();
			}

			if ((val1 != BLANK_TILE && val1 != SPIKE && val1 != SPIKE_INVERSE ) || (val2 != BLANK_TILE && val2 != SPIKE && val2 != SPIKE_INVERSE ))
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
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

			if (val1 == ENERGY || val2 == ENERGY)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				increaseEnergy();
			}

			if ((val1 != BLANK_TILE && val1 != SPIKE && val1 != SPIKE_INVERSE ) || (val2 != BLANK_TILE && val2 != SPIKE && val2 != SPIKE_INVERSE ))
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

			if (val1 == ENERGY || val2 == ENERGY)
			{
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				increaseEnergy();
			}

			if ((val1 != BLANK_TILE && val1 != SPIKE && val1 != SPIKE_INVERSE ) || (val2 != BLANK_TILE && val2 != SPIKE && val2 != SPIKE_INVERSE ))
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
		x_pos =0;
	}

	else if (x_pos + width_frame > mapData.max_x)
	{
		x_pos = mapData.max_x - width_frame - 1;
	}

	if (y_pos > mapData.max_y)
	{
		respawnTime = 60;
	}
}

#include "MainObject.h"

#define GRAVITY 1.2
#define MAX_FALL_SPEED 10
#define PLAYER_RUN_SPEED 5
#define PLAYER_JUMP_SPEED 15

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

MainObject :: ~MainObject()
{

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
		frame_clip[1].h = width_frame;

		frame_clip[2].x = 2*width_frame;
		frame_clip[2].y = 0;
		frame_clip[2].w = width_frame;
		frame_clip[2].h = width_frame;

		frame_clip[3].x = 3*width_frame;
		frame_clip[3].y = 0;
		frame_clip[3].w = width_frame;
		frame_clip[3].h = width_frame;

		frame_clip[4].x = width_frame;
		frame_clip[4].y = 0;
		frame_clip[4].w = width_frame;
		frame_clip[4].h = width_frame;

		frame_clip[5].x = width_frame;
		frame_clip[5].y = 0;
		frame_clip[5].w = width_frame;
		frame_clip[5].h = width_frame;

		frame_clip[6].x = width_frame;
		frame_clip[6].y = 0;
		frame_clip[6].w = width_frame;
		frame_clip[6].h = width_frame;
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
	else if (status == IDLE)
	{
		LoadImg("res//megaman_idle.png", des);
	}

	if (input_type.left == 1 || input_type.right == 1)
	{
		frame++;
	}
	else
	{
		frame = 0;
	}

	if (frame >= 5) frame = 0;
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
			input_type.up = 0;
			input_type.down = 0;
		}
		break;

		case SDLK_a:
		{
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			input_type.up = 0;
			input_type.down = 0;
		}
		break;

		case SDLK_w:
		{
			input_type.jump = 1;
		}
		break;

		case SDLK_j:
		{
			Bullet* bullet = new Bullet();

			if (status == WALK_LEFT)
			{
				bullet->LoadImg("res//bullet_left.png", screen);
				bullet->setBulletDirect(Bullet::DIR_LEFT);
				bullet->SetRect(this->rect.x, rect.y + height_frame * 0.2);
			}
			else
			{
				bullet->LoadImg("res//bullet_right.png", screen);
				bullet->setBulletDirect(Bullet::DIR_RIGHT);
				bullet->SetRect(this->rect.x + width_frame - 20, rect.y + height_frame * 0.2);
			}
			bullet->setX(20);
			bullet->setIsMove(true);

			bullet_list.push_back(bullet);
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
			status = WALK_RIGHT ;
			input_type.right = 0;
		}
		break;
		case SDLK_a:
		{
			status = WALK_LEFT ;
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
			if (mapData.tile[y1][x2] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE)
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= width_frame + 1;
				x_val = 0;
			}
		}
		else if (x_val < 0)
		{
			if (mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y2][x1] != BLANK_TILE)
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
			if (mapData.tile[y2][x1] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE)
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
			if (mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y1][x2] != BLANK_TILE)
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
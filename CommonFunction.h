#pragma once

//Các thư viện thường dùng để xử lí game
#include <Windows.h>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_ttf.h>

//Cửa sổ game
 static SDL_Window* gWindow = NULL;

//Render game
 static SDL_Renderer* gRenderer = NULL;

//Current displayed texture
//static SDL_Texture* gTexture = NULL;

//Sự kiện từ bàn phím, chuột
static SDL_Event gEvent;

//Các thông số màn hình game
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 1280;

//Thông số hình ảnh game(pixel)
//const int SCREEN_BPP = 32;

//Thông số màu sắc transparent
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0xff;

const int FPS = 24;

#define TILE_SIZE 32
#define MAX_MAP_X 50
#define MAX_MAP_Y 20
#define BLANK_TILE 0

typedef struct Map
{
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name;
};

typedef struct Input
{
	int left;
	int right;
	int up;
	int down;
	int jump;
};

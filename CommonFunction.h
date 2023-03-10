#pragma once

//Các thư viện thường dùng để xử lí game
#include <Windows.h>
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_ttf.h>

//Cửa sổ game
static SDL_Window* gWindow = NULL;

//Render game
static SDL_Renderer* gScreen = NULL;

//Sự kiện từ bàn phím, chuột
static SDL_Event* gEvent;

//Các thông số màn hình game
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 1280;

//Thông số hình ảnh game(pixel)
const int SCREEN_BPP = 32;

//Thông số màu sắc transparent
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

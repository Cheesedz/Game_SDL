#pragma once

#include "CommonFunction.h"
#include "BaseObject.h"

#define HIT_NUM_FRAME 14

class Hit:public BaseObject
{
public:
	Hit();
	~Hit();

	void setClip();
	void set_frame(const int& gFrame) { frame = gFrame; }
	virtual bool LoadImg(std::string, SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	int get_frame_width() const { return frame_width; }
	int get_frame_height() const { return frame_height; }


private:
	int frame_width;
	int frame_height;

	unsigned int frame;
	SDL_Rect frame_clip[14];

};
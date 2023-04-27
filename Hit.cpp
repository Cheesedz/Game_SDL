#include "Hit.h"

Hit::Hit()
{
	frame_width = 0;
	frame_height = 0;
	frame = 0;
}

Hit::~Hit()
{

}
bool Hit::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret)
	{
		frame_width = rect.w / HIT_NUM_FRAME;
		frame_height = rect.h;
	}
	return ret;
}

void Hit::setClip()
{
	if (frame_width > 0 && frame_height > 0)
	{
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = frame_width;
		frame_clip[0].h = frame_height;

		frame_clip[1].x = frame_width;
		frame_clip[1].y = 0;
		frame_clip[1].w = frame_width;
		frame_clip[1].h = frame_height;

		frame_clip[2].x = 2 * frame_width;
		frame_clip[2].y = 0;
		frame_clip[2].w = frame_width;
		frame_clip[2].h = frame_height;

		frame_clip[3].x = 3 * frame_width;
		frame_clip[3].y = 0;
		frame_clip[3].w = frame_width;
		frame_clip[3].h = frame_height;

		frame_clip[4].x = 4 * frame_width;
		frame_clip[4].y = 0;
		frame_clip[4].w = frame_width;
		frame_clip[4].h = frame_height;

		frame_clip[5].x = 5 * frame_width;
		frame_clip[5].y = 0;
		frame_clip[5].w = frame_width;
		frame_clip[5].h = frame_height;

		frame_clip[6].x = 6 * frame_width;
		frame_clip[6].y = 0;
		frame_clip[6].w = frame_width;
		frame_clip[6].h = frame_height;

		frame_clip[7].x = 7 * frame_width;
		frame_clip[7].y = 0;
		frame_clip[7].w = frame_width;
		frame_clip[7].h = frame_height;

		frame_clip[8].x = 8 * frame_width;
		frame_clip[8].y = 0;
		frame_clip[8].w = frame_width;
		frame_clip[8].h = frame_height;

		frame_clip[9].x = 9 * frame_width;
		frame_clip[9].y = 0;
		frame_clip[9].w = frame_width;
		frame_clip[9].h = frame_height;

		frame_clip[10].x = 10 * frame_width;
		frame_clip[10].y = 0;
		frame_clip[10].w = frame_width;
		frame_clip[10].h = frame_height;

		frame_clip[11].x = 11 * frame_width;
		frame_clip[11].y = 0;
		frame_clip[11].w = frame_width;
		frame_clip[11].h = frame_height;

		frame_clip[12].x = 12 * frame_width;
		frame_clip[12].y = 0;
		frame_clip[12].w = frame_width;
		frame_clip[12].h = frame_height;

		frame_clip[13].x = 13 * frame_width;
		frame_clip[13].y = 0;
		frame_clip[13].w = frame_width;
		frame_clip[13].h = frame_height;

	}
}

void Hit::Show(SDL_Renderer* screen)
{
	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect render_quad = { rect.x, rect.y, frame_width, frame_height };
	if (current_clip != NULL)
	{
		render_quad.w = current_clip->w;
		render_quad.h = current_clip->h;
	}

	SDL_RenderCopy(screen, p_object, current_clip, &render_quad);

}
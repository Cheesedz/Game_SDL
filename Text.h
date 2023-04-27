#pragma once

#include "CommonFunction.h"

class Text
{
public:
	Text();
	~Text();

	enum TextColor
	{
		RED = 0,
		WHITE = 1,
		BLACK = 2,
	};
	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);

	void Free();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	void SetColor(int type);

	void RenderText(SDL_Renderer* screen, int xp, int yp, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	void SetText(const std::string& text) { str = text; }

	std::string getText() const { return str; }

private:
	std::string str;
	SDL_Color text_color;
	SDL_Texture* texture;
	int width;
	int height;
};

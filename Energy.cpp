#include "Energy.h"

Energy::Energy()
{
	number = 0;
}

Energy::~Energy()
{

}

void Energy::AddPos(const int& xPos)
{
	pos.push_back(xPos);
}


void Energy::Init(SDL_Renderer* screen)
{
	LoadImg("map//2.png", screen);
	number = 3;
	if (pos.size() > 0)
	{
		pos.clear();
	}
	AddPos(20);
	AddPos(50);
	AddPos(80);
}

void Energy::Show(SDL_Renderer* screen)
{
	for (int i = 0; i < pos.size(); i++)
	{
		rect.x = pos.at(i);
		rect.y = 0;
		Render(screen);
	}
}

void Energy::decreaseLife()
{
	number--;
	if (pos.size()>0) pos.pop_back();
}

void Energy::increaseLife()
{
	number++;
	int last_pos = pos.back();
	pos.push_back(last_pos);
}

//class Life
//{
//
//};
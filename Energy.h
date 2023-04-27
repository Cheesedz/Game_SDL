#pragma once
#include "CommonFunction.h"
#include "BaseObject.h"

class Energy : public BaseObject
{
public:
	Energy();
	~Energy();


	void SetNum(const int& num) { number = num; }

	void AddPos(const int& xPos);

	void Show(SDL_Renderer* screen);

	void Init(SDL_Renderer* screen);

	void increaseLife();

	void decreaseLife();
private:
	int number;
	std::vector<int> pos;
};

//class Life
//{
//
//};
#pragma once
#include "Component.h"

class PositionComponent : public Component
{
private:
	int x_pos;
	int y_pos;

public:

	PositionComponent()
	{
		x_pos = 0;
		y_pos = 0;
	}

	PositionComponent(int x, int y)
	{
		x_pos = x;
		y_pos = y;
	}

	void upDate() override
	{
		x_pos++;
		y_pos++;
	}

	int x() { return x_pos; }
	void x(int x) { x_pos = x; }
	int y() { return y_pos; }
	void y(int y) { y_pos = y; }

	void setPos(int x, int y)
	{
		x_pos = x;
		y_pos = y;
	}


};
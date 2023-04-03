#include "Bullet.h"

Bullet::Bullet()
{
	x_val = 0;
	y_val = 0;
	is_move = false;
}

Bullet::~Bullet()
{

}

void Bullet::HandleMove(const int& x_border, const int& y_border)
{
	if (bulletDirect == DIR_RIGHT)
	{
		rect.x += x_val;
		if (rect.x > x_border)
		{
			is_move = false;
		}
	}

	else if (bulletDirect == DIR_LEFT)
	{
		rect.x -= x_val;
		if (rect.x < 0)
		{
			is_move = false;
		}
	}

	
}
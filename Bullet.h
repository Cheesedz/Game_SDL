#pragma once

#include "BaseObject.h"
#include "CommonFunction.h"

class Bullet : public BaseObject
{
public: 
	Bullet();
	~Bullet();

	enum BulletDir
	{
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
	};

	void setX(const int& xVal) { x_val = xVal; }
	void setY(const int& yVal) { y_val = yVal; }
	int getX() const { return x_val; }
	int getY() const { return y_val; }
	void setIsMove(const bool& isMove) { is_move = isMove; }
	bool getIsMove() const { return is_move; }
	void HandleMove(const int& x_border, const int& y_border);
	void setBulletDirect(const unsigned int& bulletDir) { bulletDirect = bulletDir; }
	int getBulletDirect() const { return bulletDirect; }
private:
	int x_val;
	int y_val;
	bool is_move;
	unsigned int bulletDirect;
};

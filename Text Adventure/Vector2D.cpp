#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(int newx, int newy)
{
	x = newx;
	y = newy;
}

Vector2D::~Vector2D()
{
}

bool Vector2D::operator==(Vector2D & vector2)
{
	if (x == vector2.x && y == vector2.y)
		return true;
	else
		return false;
}

void Vector2D::operator=(Vector2D & vector2)
{
	x = vector2.x;
	y = vector2.y;
}

Vector2D Vector2D::operator+(Vector2D & vector2)
{
	Vector2D temp(x + vector2.x, y + vector2.y);
	return temp;
}

Vector2D Vector2D::operator-(Vector2D & vector2)
{
	Vector2D temp(x - vector2.x, y - vector2.y);
	return temp;
}

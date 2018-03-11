#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
	int x;
	int y;

	Vector2D();
	Vector2D(int newx, int newy);
	~Vector2D();

	bool		operator==	(Vector2D &vector2);					// Vector2D Comparator - returns bool
	void		operator=	(Vector2D &vector2);					// Vector2D assignment overload
	Vector2D	operator+	(Vector2D &vector2);					// Vector2D addition overload
	Vector2D	operator-	(Vector2D &vector2);					// Vector2D subtraction overload

};

#endif
#include "Vector2.h"

namespace jutiny
{

namespace engine
{

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2 Vector2::operator+(Vector2 _vector)
{
	return Vector2(x + _vector.x, y + _vector.y);
}

Vector2 Vector2::operator-(Vector2 _vector)
{
	return Vector2(x - _vector.x, y - _vector.y);
}

}

}

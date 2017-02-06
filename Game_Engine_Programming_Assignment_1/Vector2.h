#ifndef JUTINY_ENGINE_VECTOR2_H
#define JUTINY_ENGINE_VECTOR2_H

namespace jutiny
{

namespace engine
{

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float _x, float _y);

	Vector2 operator+(Vector2 _vector);
	Vector2 operator-(Vector2 _vector);
};

}

}

#endif
#ifndef JUTINY_ENGINE_VECTOR3_H
#define JUTINY_ENGINE_VECTOR3_H

namespace jutiny
{

namespace engine
{

class Vector2;

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float _x, float _y);
	Vector3(float _x, float _y, float _z);
	
	Vector3 operator+(Vector3 _vector);
	
	Vector3 operator-(Vector2 _vector);
	Vector3 operator-(Vector3 _vector);

	Vector3 operator*(float _scalar);
	Vector3 operator*(Vector3 _vector);

	Vector3 operator/(float _scalar);

	float getMagnitude();
	Vector3 getNormalized();
	static float getDistance(Vector3 a, Vector3 b);
	
};

}

}

#endif
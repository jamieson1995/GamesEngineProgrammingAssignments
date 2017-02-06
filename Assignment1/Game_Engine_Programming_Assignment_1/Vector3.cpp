#include "Vector3.h"
#include "Vector2.h"

#include <cmath>

namespace jutiny
{

namespace engine
{

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float _x, float _y)
{
	x = _x;
	y = _y;
	z = 0;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3 Vector3::operator+(Vector3 _vector)
{
	return Vector3(x + _vector.x, y + _vector.y, z + _vector.z);
}


Vector3 Vector3::operator-(Vector2 _vector)
{
	return Vector3(x - _vector.x, y - _vector.y, z);
}

Vector3 Vector3::operator-(Vector3 _vector)
{
	return Vector3(x - _vector.x, y - _vector.y, z - _vector.z);
}

Vector3 Vector3::operator*(Vector3 _vector)
{
	return Vector3(x * _vector.x, y * _vector.y, z * _vector.z);
}

Vector3 Vector3::operator*(float _scalar)
{
	return Vector3(x * _scalar, y * _scalar, z * _scalar);
}

Vector3 Vector3::operator/(float _scalar)
{
	return Vector3(x / _scalar, y / _scalar, z / _scalar);
}

float Vector3::getMagnitude()
{
  return sqrt(x*x+y*y+z*z);
}

Vector3 Vector3::getNormalized()
{
  Vector3 temp;
  float magnitude = getMagnitude();

  temp.x = x/magnitude;
  temp.y = y/magnitude;
  temp.z = z/magnitude;

  return temp;
}

float Vector3::getDistance(Vector3 a, Vector3 b)
{
  return (a - b).getMagnitude();
}

}

}

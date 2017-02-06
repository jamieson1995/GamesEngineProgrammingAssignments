#include "Vector4.h"
#include "Vector2.h"

#include <cmath>

namespace jutiny
{

namespace engine
{

Vector4::Vector4()
{
  x = 0;
  y = 0;
  z = 0;
  w = 0;
}

Vector4::Vector4(float _value)
{
  x = _value;
  y = _value;
  z = _value;
  w = _value;
}

Vector4::Vector4(float _x, float _y)
{
  x = _x;
  y = _y;
  z = 0;
  w = 0;
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
{
  x = _x;
  y = _y;
  z = _z;
  w = _w;
}

Vector4 Vector4::operator*(Vector4 _vector)
{
  return Vector4(x * _vector.x, y * _vector.y, z * _vector.z, w * _vector.w);
}

Vector4 Vector4::operator+(Vector4 _vector)
{
  return Vector4(x + _vector.x, y + _vector.y, z + _vector.z, w + _vector.w);
}

Vector4 Vector4::operator-(Vector4 _vector)
{
  return Vector4(x - _vector.x, y - _vector.y, z - _vector.z, w - _vector.w);
}

Vector4 Vector4::operator-(Vector2 _vector)
{
  return Vector4(x - _vector.x, y - _vector.y, z, w);
}

Vector4 Vector4::operator*(float _scalar)
{
  return Vector4(x * _scalar, y * _scalar, z * _scalar, w * _scalar);
}

Vector4 Vector4::operator+(float _scalar)
{
  return Vector4(x + _scalar, y + _scalar, z + _scalar, w + _scalar);
}

Vector4 Vector4::operator/(float _scalar)
{
  return Vector4(x / _scalar, y / _scalar, z / _scalar, w / _scalar);
}

Vector4 Vector4::getNormalized()
{
  Vector4 temp;
  float magnitude = getMagnitude();

  temp.x = x/magnitude;
  temp.y = y/magnitude;
  temp.z = z/magnitude;
  temp.w = w/magnitude;

  return temp;
}

float Vector4::getMagnitude()
{
  return sqrt(x*x+y*y+z*z+w*w);
}

float Vector4::getDistance(Vector4 a, Vector4 b)
{
  return (a - b).getMagnitude();
}

}

}
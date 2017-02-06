#ifndef JUTINY_ENGINE_VECTOR4_H
#define JUTINY_ENGINE_VECTOR4_H

namespace jutiny
{

namespace engine
{

class Vector2;

class Vector4
{
public:
  float x;
  float y;
  float z;
  float w;

  Vector4();
  Vector4(float _value);
  Vector4(float _x, float _y);
  Vector4(float _x, float _y, float _z, float _w);

  Vector4 operator-(Vector2 _vector);
  Vector4 operator-(Vector4 _vector);
  Vector4 operator+(Vector4 _vector);
  Vector4 operator*(Vector4 _vector);
  Vector4 operator/(float _scalar);
  Vector4 operator*(float _scalar);
  Vector4 operator+(float _scalar);

  float getMagnitude();
  Vector4 getNormalized();
  static float getDistance(Vector4 _a, Vector4 _b);
};

}

}

#endif
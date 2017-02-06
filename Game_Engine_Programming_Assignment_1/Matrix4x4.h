#ifndef JUTINY_ENGINE_MATRIX4X4_H
#define JUTINY_ENGINE_MATRIX4X4_H

#include "linmath.h"

namespace jutiny
{

namespace engine
{

class Vector3;

class Matrix4x4
{

public:
	
  mat4x4 m_matrix;

  //Returns orthographic view matrix.
  static Matrix4x4 ortho(float _left, float _right, float _bottom, float _top, float _zNear, float _zFar);

  //Returns perspective view matrix.
  static Matrix4x4 perspective(float _fieldOfView, float _aspect, float _zNear, float _zFar);

  //Returns the Identity Matrix.
  static Matrix4x4 getIdentity();

  //Returns transformation matrix.
  static Matrix4x4 getTrs(Vector3 _position, Vector3 _rotation, Vector3 _scale);

  //Returns a translated matrix based upon specified Vector3.
  Matrix4x4 translate(Vector3 _vector);

  //Returns a rotated matrix based upon specified Vector3.
  Matrix4x4 rotate(Vector3 _vector);

  //Returns a rotated matrix based upon specified Vector3 and an angle of rotation.
  Matrix4x4 rotate(float _angle, Vector3 _vector);

  //Returns a scaled matrix based upon specified Vector3.
  Matrix4x4 scale(Vector3 _vector);

  //Returns the inverse of the matrix.
  Matrix4x4 inverse();

  //Returns a mirrored version of the matrix.
  Matrix4x4 transpose();

  //Multiplies a Matrix4x4 and a Vector3 to return a point of type Vector3.
  Vector3 multiplyPoint(Vector3 _v);

  //Multiplies a Matrix4x4 and a Vector3 to return a vector of type Vector3.
  Vector3 multiplyVector(Vector3 _v);

  Vector3 operator*(Vector3 _param);

  Matrix4x4 operator*(Matrix4x4 _param);

  Matrix4x4();

  //Returns the value of the matrix.
  float* getValue();

};

}

}

#endif
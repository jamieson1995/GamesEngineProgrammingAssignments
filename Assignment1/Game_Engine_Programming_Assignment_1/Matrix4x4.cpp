#include "Matrix4x4.h"
#include "Vector3.h"
#include "Mathf.h"

#include "linmath.h"

namespace jutiny
{

namespace engine
{

Matrix4x4 Matrix4x4::ortho(float _left, float _right, float _bottom, float _top, float _zNear, float _zFar)
{
  Matrix4x4 mat = Matrix4x4();

  mat4x4_ortho(mat.m_matrix, _left, _right, _bottom, _top, _zNear, _zFar);

  return mat;
}

Matrix4x4 Matrix4x4::perspective(float _fieldOfView, float _aspect, float _zNear, float _zFar)
{
  Matrix4x4 mat = Matrix4x4();

  mat4x4_perspective(mat.m_matrix, Mathf::deg2Rad(_fieldOfView), _aspect, _zNear, _zFar);

  return mat;
}


Matrix4x4 Matrix4x4::getTrs(Vector3 _position, Vector3 _rotation, Vector3 _scale)
{
  mat4x4 tmpMat;
  Matrix4x4 mat = getIdentity();

  mat4x4_translate(mat.m_matrix, _position.x, _position.y, _position.z);

  mat4x4_rotate(tmpMat, mat.m_matrix, 0, 1, 0, Mathf::deg2Rad(_rotation.y));
  mat4x4_rotate(mat.m_matrix, tmpMat, 0, 0, 1, Mathf::deg2Rad(_rotation.z));
  mat4x4_rotate(tmpMat, mat.m_matrix, 1, 0, 0, Mathf::deg2Rad(_rotation.x));

  mat4x4_scale_aniso(mat.m_matrix, tmpMat, _scale.x, _scale.y, _scale.z);

  return mat;
}

Matrix4x4::Matrix4x4()
{
  mat4x4_identity(m_matrix);
}

Matrix4x4 Matrix4x4::getIdentity()
{
  Matrix4x4 mat;

  mat4x4_identity(mat.m_matrix);

  return mat;
}

Matrix4x4 Matrix4x4::rotate(Vector3 _vector)
{
  mat4x4 tmpMat;

  Matrix4x4 mat = rotate(_vector.z, Vector3(0, 0, 1));
            mat = mat.rotate(_vector.x, Vector3(1, 0, 0));
            mat = mat.rotate(_vector.y, Vector3(0, 1, 0));

  mat4x4_identity(tmpMat);
  mat4x4_rotate(mat.m_matrix, tmpMat, 0, 0, 1, Mathf::deg2Rad(_vector.z));
  mat4x4_rotate(tmpMat, mat.m_matrix, 0, 1, 0, Mathf::deg2Rad(_vector.y));
  mat4x4_rotate(mat.m_matrix, tmpMat, 1, 0, 0, Mathf::deg2Rad(_vector.x));

  return mat;
}

float* Matrix4x4::getValue()
{
  return (float*)m_matrix;
}

Matrix4x4 Matrix4x4::translate(Vector3 _vector)
{
  Matrix4x4 mat = *this;

  mat4x4_translate_in_place(mat.m_matrix, _vector.x, _vector.y, _vector.z);

  return mat;
}

Matrix4x4 Matrix4x4::scale(Vector3 _vector)
{
  Matrix4x4 mat = *this;

  mat4x4_scale_aniso(mat.m_matrix, m_matrix, _vector.x, _vector.y, _vector.z);

  return mat;
}

Matrix4x4 Matrix4x4::rotate(float _angle, Vector3 _vector)
{
  Matrix4x4 mat;

  mat4x4_rotate(mat.m_matrix, m_matrix, _vector.x, _vector.y, _vector.z, _angle);

  return mat;
}

Matrix4x4 Matrix4x4::inverse()
{
  Matrix4x4 mat;

  mat4x4_invert(mat.m_matrix, m_matrix);

  return mat;
}

Matrix4x4 Matrix4x4::transpose()
{
  Matrix4x4 mat;

  mat4x4_transpose(mat.m_matrix, m_matrix);

  return mat;
}

Vector3 Matrix4x4::multiplyPoint(Vector3 _v)
{
  vec4 returnVec;
  vec4 tempVec;

  tempVec[0] = _v.x;
  tempVec[1] = _v.y;
  tempVec[2] = _v.z;
  tempVec[3] = 1.0f;
  mat4x4_mul_vec4(returnVec, m_matrix, tempVec);

  return Vector3(returnVec[0], returnVec[1], returnVec[2]);
}

Vector3 Matrix4x4::multiplyVector(Vector3 _v)
{
  vec4 returnVec;
  vec4 tempVec;

  tempVec[0] = _v.x;
  tempVec[1] = _v.y;
  tempVec[2] = _v.z;
  tempVec[3] = 0.0f;
  mat4x4_mul_vec4(returnVec, m_matrix, tempVec);

  return Vector3(returnVec[0], returnVec[1], returnVec[2]);
}

Vector3 Matrix4x4::operator*(Vector3 _param)
{
  vec4 returnVec;
  vec4 tempVec;

  tempVec[0] = _param.x;
  tempVec[1] = _param.y;
  tempVec[2] = _param.z;
  tempVec[3] = 1.0f;
  mat4x4_mul_vec4(returnVec, m_matrix, tempVec);

  return Vector3(returnVec[0], returnVec[1], returnVec[2]);
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 _param)
{
  Matrix4x4 mat;

  mat4x4_mul(mat.m_matrix, m_matrix, _param.m_matrix);

  return mat;
}

}

}
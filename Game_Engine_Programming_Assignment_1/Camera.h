#ifndef JUTINY_ENGINE_CAMERA_H
#define JUTINY_ENGINE_CAMERA_H

#include "Behaviour.h"
#include "Matrix4x4.h"
#include "Colour.h"

#include <memory>
#include <vector>

namespace jutiny
{

namespace engine
{

class Application;

class Camera : public Behaviour
{
  friend class jutiny::engine::Application;

public:

  //Returns main camera.
  static ref<Camera> getMain();
  
  //Returns current Camera.
  static ref<Camera> getCurrent();

  static void setCurrent(ref<Camera> _camera);

  //Returns a vector of all cameras.
  static std::vector<ref<Camera> >& getAllCameras();

  virtual ~Camera();

  //Returns the projection matrix.
  Matrix4x4 getProjectionMatrix();

  //Sets the projection matrix.
  void setProjectionMatrix(Matrix4x4 _projectionMatrix);

  //Resets the projection matrix to NULL.
  void resetProjectionMatrix();

  void setOrthoView(bool _value) { isOrthographic = _value; }

  //Sets background colour
  void setBackgroundColor(Colour _colour);

  //Returns background colour.
  Colour getBackgroundColor();

  //Returns cull mask value.
  int getCullMask();

  //Sets cull mask value;
  void setCullMask(int _cullMask);

private:

  Colour backgroundColor;
  float fieldOfView;
  bool isOrthographic;
  float orthographicSize;
  float nearClipPlane;
  float farClipPlane;
  Matrix4x4* m_projectionMatrix;
  Matrix4x4* m_viewMatrix;
  int cullMask;

  virtual void onAwake();
  virtual void onStart();
  virtual void onDestroy();
};

}

}

#endif
#include "Camera.h"
#include "Debug.h"
#include "GameObject.h"
#include "Matrix4x4.h"
#include "Screen.h"

namespace jutiny
{

namespace engine
{

ref<Camera> Camera::getMain()
{
  return Application::context->_main;
}

ref<Camera> Camera::getCurrent()
{
  return Application::context->current;
}

void Camera::setCurrent(ref<Camera> _camera)
{
	Application::context->current = _camera;
}

std::vector<ref<Camera> >& Camera::getAllCameras()
{
  return Application::context->allCameras;
}

Camera::~Camera()
{

}

Matrix4x4 Camera::getProjectionMatrix()
{
  if(m_projectionMatrix != NULL)
  {
    return *m_projectionMatrix;
  }

  if(isOrthographic == true)
  {
    return Matrix4x4::ortho(0.0f, Screen::getWidth(), Screen::getHeight(), 0.0f, 1.0f, 10.0f);
  }
  else
  {
    return Matrix4x4::perspective(fieldOfView, (float)Screen::getWidth() / (float)Screen::getHeight(), nearClipPlane, farClipPlane);
  }
}

void Camera::setProjectionMatrix(Matrix4x4 _projectionMatrix)
{
  this->m_projectionMatrix = new Matrix4x4();
  *this->m_projectionMatrix = _projectionMatrix;
}

void Camera::resetProjectionMatrix()
{
  m_projectionMatrix = NULL;
}

void Camera::onAwake()
{
  isOrthographic = false;
  fieldOfView = 60.0f;
  orthographicSize = 100;
  nearClipPlane = 1.0f;
  farClipPlane = 30.0f;
  cullMask = 1 << 0;

  backgroundColor = Colour(49.0f / 255.0f, 77.0f / 255.0f, 121.0f / 255.0f, 1.0f);
}

void Camera::setCullMask(int cullMask)
{
  this->cullMask = cullMask;
}

int Camera::getCullMask()
{
  return cullMask;
}

void Camera::onStart()
{
  if(Application::context->_main.expired() &&
    getGameObject()->getName() == "MainCamera")
  {
    Debug::Log("MainCamera added");
    Application::context->_main = this;
  }

  Application::context->allCameras.push_back(this);
}

Colour Camera::getBackgroundColor()
{
  return backgroundColor;
}

void Camera::setBackgroundColor(Colour colour)
{
  this->backgroundColor = colour;
}

void Camera::onDestroy()
{
  Debug::Log("Camera destroyed");

  if(Application::context->_main.try_get() == this)
  {
    Application::context->_main = NULL;
  }

  for(int i = 0; i < Application::context->allCameras.size(); i++)
  {
    if(Application::context->allCameras.at(i).get() == this)
    {
      Application::context->allCameras.erase(
        Application::context->allCameras.begin() + i);

      i--;
    }
  }
}

}

}
#include "Screen.h"
#include "Application.h"

namespace jutiny
{

namespace engine
{

int Screen::m_width;
int Screen::m_height;
int Screen::m_posX;
int Screen::m_posY;
SDL_Renderer* Screen::m_renderer;
SDL_GLContext Screen::m_glContext;

int Screen::getWidth()
{
  return m_width;
}

int Screen::getHeight()
{
  return m_height;
}

int Screen::getPosX()
{
	return m_posX;
}

int Screen::getPosY()
{
	return m_posY;
}


void Screen::setResolution(int _width, int _height)
{
  Application::Reshape(_width, _height);
}

}

}


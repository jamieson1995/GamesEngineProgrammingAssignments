#ifndef JUTINY_ENGINE_SCREEN_H
#define JUTINY_ENGINE_SCREEN_H

#include <SDL.h>

namespace jutiny
{

namespace engine
{

class Application;

class Screen
{
  friend class Application;

public:
  static int getWidth();
  static int getHeight();
  static int getPosX();
  static int getPosY();
  static void setResolution(int _width, int _height);

private:
  static int m_width;
  static int m_height;
  static int m_posX;
  static int m_posY;

  static SDL_Renderer *m_renderer;
  static SDL_GLContext m_glContext;

};

}

}

#endif


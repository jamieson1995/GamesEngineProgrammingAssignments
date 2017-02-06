#include "Input.h"
#include "platform.h"
#include "Application.h"


#include <SDL.h>

#include <string>
#include <iostream>

namespace jutiny
{

namespace engine
{

// Static variable declarations
std::vector<int> Input::m_keys;
std::vector<int> Input::m_downKeys;
std::vector<int> Input::m_upKeys;
std::vector<SDL_MouseButtonEvent> Input::m_mouseButtonEvents;
std::vector<SDL_MouseButtonEvent> Input::m_upMouseButtonEvents;
std::vector<SDL_MouseButtonEvent> Input::m_downMouseButtonEvents;
int Input::m_mouseXCoord = 0;
int Input::m_mouseYCoord = 0;

// Search all currently pressed keys for keyCode
bool Input::isKey(int _keyCode)
{
  for(int i = 0; i < m_keys.size(); i++)
  {
    if(m_keys.at(i) == _keyCode)
    {
      return true;
    }
  }

  return false;
}

// Search upKeys (keys released since last display update)
bool Input::didKeyUp(int _keyCode)
{
  for(int i = 0; i < m_upKeys.size(); i++)
  {
    if(m_upKeys.at(i) == _keyCode)
    {
      return true;
    }
  }

  return false;
}

// Search downKeys (keys pressed since last display update)
bool Input::didKeyDown(int _keyCode)
{
  for(int i = 0; i < m_downKeys.size(); i++)
  {
    if(m_downKeys.at(i) == _keyCode)
    {
      return true;
    }
  }

  return false;
}

// Search all currently pressed mouse buttons for mouseButton
bool Input::isMouseButton(Uint8 _mouseButton)
{
  for(int i = 0; i < m_mouseButtonEvents.size(); i++)
  {
    if(m_mouseButtonEvents.at(i).button == _mouseButton)
    {
      return true;
    }
  }

  return false;
}

// Search upMouseButtons (mouse buttons released since last display update)
bool Input::didMouseButtonUp(Uint8 _mouseButton)
{
  for(int i = 0; i < m_upMouseButtonEvents.size(); i++)
  {
    if(m_upMouseButtonEvents.at(i).button == _mouseButton)
    {
      return true;
    }
  }

  return false;
}

// Search downMouseButtons (mmouse buttons pressed since last display update)
bool Input::didMouseButtonDown(Uint8 _mouseButton)
{
  for(int i = 0; i < m_downMouseButtonEvents.size(); i++)
  {
    if(m_downMouseButtonEvents.at(i).button == _mouseButton)
    {
      return true;
    }
  }

  return false;
}

Sint32 Input::lastXCoordClicked(Uint8 _mouseButton)
{
	for(int i = 0; i < m_downMouseButtonEvents.size(); i++)
	{
		if (m_downMouseButtonEvents.at(i).button == _mouseButton)
		{
			return m_downMouseButtonEvents.at(i).x;
		}
	}

	return NULL;
	
}

Sint32 Input::lastYCoordClicked(Uint8 _mouseButton)
{
	for(int i = 0; i < m_downMouseButtonEvents.size(); i++)
	{
		if (m_downMouseButtonEvents.at(i).button == _mouseButton)
		{
			return m_downMouseButtonEvents.at(i).y;
		}
	}
	return NULL;
}

//Run every frame. Checks for input from user such as keyboard and mouse presses and movements.
void Input::Update()
{
	SDL_Event event;
	while( SDL_PollEvent( &event ) )
	{
		switch ( event.type )
		{
		case SDL_KEYDOWN:
			//Add any downed keys to the downKey vector and the key vector
			jutiny::engine::Application::KeyboardDown( (unsigned char)SDL_GetKeyName( event.key.keysym.sym ) );
			break;
		case SDL_KEYUP:
			//Add any upped keys to the upKey vector and the key vector
			jutiny::engine::Application::KeyboardUp( (unsigned char)SDL_GetKeyName( event.key.keysym.sym ) );
			break;
		case SDL_MOUSEMOTION:
			if (event.motion.x != m_mouseXCoord)
			{
				m_mouseXCoord = event.motion.x;
			}
			if (event.motion.y != m_mouseYCoord)
			{
				m_mouseYCoord = event.motion.y;				
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			Application::MouseButtonDown(event.button);
			break;
		case SDL_MOUSEBUTTONUP:
			Application::MouseButtonUp(event.button);
			break;
		case SDL_QUIT:
			Application::Quit();
			break;
		}
	}

}

}

}


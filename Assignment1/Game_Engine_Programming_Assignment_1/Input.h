#ifndef JUTINY_ENGINE_INPUT_H
#define JUTINY_ENGINE_INPUT_H

#include <SDL.h>

#include <string>
#include <vector>

namespace jutiny
{

namespace engine
{

class Application;

class Input
{
  // Allow Application to access private static key vectors
  // So that glut can process keyboard events and update input with changes
  friend class jutiny::engine::Application;

public:
	// Check key states
	static bool isKey(int _keyCode); //Is specified key currently down?
	static bool didKeyDown(int _keyCode); // Did the specified key get pressed since last frame?
	static bool didKeyUp(int _keyCode); // Did the specified key get released since last frame?
	
	//Check mouse button states
	static bool isMouseButton(Uint8 _mouseButton); //Is specified mouse button currently down?
	static bool didMouseButtonDown(Uint8 _mouseButton); // Did the specified mouse button get pressed since last frame?
	static bool didMouseButtonUp(Uint8 _mouseButton); // Did the specified mouse button get released since last frame?

	//Check Coordinates of position last clicked by specified mouse button
	static Sint32 lastXCoordClicked(Uint8 _mouseButton);
	static Sint32 lastYCoordClicked(Uint8 _mouseButton);

	//Returns mouse button p
	int getMousePosX() { return m_mouseXCoord; }
	int getMousePosY() { return m_mouseYCoord; }

	static void Update(); //Run every frame

private:

	//Key vectors
	static std::vector<int> m_keys;
	static std::vector<int> m_upKeys;
	static std::vector<int> m_downKeys;

	//Mouse button event vectors
	static std::vector<SDL_MouseButtonEvent> m_mouseButtonEvents;
	static std::vector<SDL_MouseButtonEvent> m_upMouseButtonEvents;
	static std::vector<SDL_MouseButtonEvent> m_downMouseButtonEvents;
	static int m_mouseXCoord;
	static int m_mouseYCoord;

};

}

}

#endif


#ifndef JUTINY_ENGINE_APPLICATION_H
#define JUTINY_ENGINE_APPLICATION_H

#include "platform.h"
#include "Object.h"
#include "Debug.h"
#include "Input.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Renderer.h"
#include "ref.h"
#include "Matrix4x4.h"

#include <SDL.h>

#include <memory>
#include <vector>
#include <string>

namespace jutiny
{

namespace engine
{

class Application;
class Screen;
class Camera;
class Mesh;
class Shader;
class GameObject;
class Input;
class Debug;
class Renderer;

struct Context
{
	bool running;
	std::string dataPath;
	std::string engineDataPath;
	std::vector<shared<GameObject> > gameObjects;

	int argc;
	std::vector<std::string> argv;

	//Resources
	std::vector<std::string> paths;
	std::vector<shared<Object> > objects;

	//Camera
	std::vector<ref<Camera> > allCameras;
	ref<Camera> current;
	ref<Camera> _main;
};

class Application
{
	friend class jutiny::engine::Screen;
	friend class jutiny::engine::Camera;
	friend class jutiny::engine::Input;
	friend class jutiny::engine::GameObject;
	friend class jutiny::engine::Renderer;
	friend class jutiny::engine::Mesh;

public:

	//Initialise the application.
	static bool init(int argc, char* argv[]);

	//Initialise GL.
	static bool InitGL();

	//Make sure everything is deleted to prevent memeory leaks and closes the application.
	static void Destroy();

	//Contains the main game loop.
	static void Run();

	//Stops the game loop and quits the application.
	static void Quit();

	//Returns path to main folder.
	static std::string getDataPath();

	//Returns path to engine folder.
	static std::string getEngineDataPath();

	static int getArgc();
	static std::string getArgv(int i);

	//Sets title of the window to specifed char.
	static void setTitle(const char *_title);
	

private:
	static shared<Context> context;

	static void SetupPaths();
	static std::vector<shared<GameObject> >& getGameObjects();

	//Changes the dimensions of the window to specifed integers.
	static void Reshape(int _width, int _height);

	//Updates the display.
	static void Display(double _amountIntoNextFrame);

	//Functions to add keys to Input class's key vectors
	static void KeyboardDown(unsigned char _key);
	static void KeyboardUp(unsigned char _key);
	static void _keyboardDown(int _key);
	static void _keyboardUp(int _key);


	//Functions to add keys to Input class's mouse button vectors	
	static void MouseButtonDown(SDL_MouseButtonEvent _mouseButton);
	static void MouseButtonUp(SDL_MouseButtonEvent _mouseButton);

	static SDL_Window *m_window;
};

}

}

#endif
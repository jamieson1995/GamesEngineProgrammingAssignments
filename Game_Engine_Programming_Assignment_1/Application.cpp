#include "Application.h"
#include "Screen.h"
#include "Input.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Component.h"

#include "Debug.h"

#include "Exception.h"
#include "platform.h"

#include "glew.h"

#include <SDL.h>
#include <glm.hpp>

#include <windows.h>

namespace jutiny
{

namespace engine
{

shared<Context> Application::context;
SDL_Window* Application::m_window;

bool Application::InitGL()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		std::cerr<<"Error: GLEW failed to initialise with message: "<< glewGetErrorString(err) <<std::endl;
		return false;
	}
	std::cout<<"INFO: Using GLEW "<< glewGetString(GLEW_VERSION)<<std::endl;
	
	std::cout<<"INFO: OpenGL Vendor: "<< glGetString( GL_VENDOR ) << std::endl;
	std::cout<<"INFO: OpenGL Renderer: "<< glGetString( GL_RENDERER ) << std::endl;
	std::cout<<"INFO: OpenGL Version: "<< glGetString( GL_VERSION ) << std::endl;
	std::cout<<"INFO: OpenGL Shading Language Version: "<< glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;
	
	return true;
}

bool Application::init(int argc, char* argv[])
{
  // Create and initialise a new context
  context.reset(new Context());

  context->running = false;
  context->argc = argc;

  for(int i = 0; i < argc; i++)
  {
    context->argv.push_back(argv[i]);
  }
	//Initialise SDL and create a window. 
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout<<"Something went very wrong, cannot initialise SDL."<<std::endl;
		return false;
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	//Set initial screen size and position
	Screen::m_posX = 500;
	Screen::m_posY = 100;
	Screen::m_width = 1024;
	Screen::m_height = 900;
	//Creates new window with specified parameters
	Application::m_window = SDL_CreateWindow("Game_Engine_Programming_Assignment_1",
		Screen::m_posX, Screen::m_posY,
		Screen::m_width, Screen::m_height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	//Creates a 2D rendering context for the specified window.
	Screen::m_renderer = SDL_CreateRenderer( Application::m_window, -1, 0 );

	//Creates an OpenGL contect for use with the specified OpenGL window.
	Screen::m_glContext = SDL_GL_CreateContext( Application::m_window );

	//Initialises glew and GL.
	if( !InitGL() )
	{
		return false;
	}

	SetupPaths();

	return true;
}

void Application::setTitle(const char *_title)
{
	SDL_SetWindowTitle(Application::m_window, _title);
}

void Application::SetupPaths()
{
  context->engineDataPath = "./resources/jutiny";
  context->dataPath = "./resources";
}

void Application::Destroy()
{
  // TODO: Running is a flag, not a reliable state
  if(context->running == true)
  {
    throw Exception("Immediate shutdown not supported");
  }

  SDL_GL_DeleteContext( Screen::m_glContext );
  SDL_DestroyWindow(Application::m_window);

  context.reset();

  SDL_Quit();
  
}

void Application::Run()
{
  if(context->running == true)	
  {
    return;
  }

	context->running = true;
	double previous = SDL_GetTicks();
	double lag = 0.0;
	double MS_PER_UPDATE = 16;
	int currXPos = 0;
	int currYPos = 0;
	Camera::getCurrent()->setBackgroundColor(Colour(100,0,0,255));	
	while(context->running == true)
	{
		double current = SDL_GetTicks();
		float deltaTime = (float) (current - previous) / 1000.0f;
		previous = current;
		lag+=deltaTime;
		Input::Update();
		for(size_t i = 0; i < context->gameObjects.size(); i++)
		{
			context->gameObjects.at(i)->update();
		}
		lag -= MS_PER_UPDATE;			
		Application::Display(lag / MS_PER_UPDATE);

		// Clear up and down keys and mouse buttons each frame.
		Input::m_downKeys.clear();
		Input::m_upKeys.clear();
		Input::m_downMouseButtonEvents.clear();
		Input::m_upMouseButtonEvents.clear();
  }

  context->running = false;
}

void Application::Quit()
{
  context->running = false;

}

std::string Application::getDataPath()
{
  return context->dataPath;
}

std::string Application::getEngineDataPath()
{
  return context->engineDataPath;
}

std::vector<shared<GameObject> >& Application::getGameObjects()
{
  return context->gameObjects;
}

int Application::getArgc()
{
  return context->argc;
}

std::string Application::getArgv(int i)
{
  return context->argv.at(i);
}

void Application::Reshape(int _width, int _height)
{
  Screen::m_width = _width;
  Screen::m_height = _height;

  SDL_SetWindowSize(Application::m_window, _width, _height);
}

void Application::Display(double _amountIntoNextFrame)
{
	glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, Screen::getWidth(), Screen::getHeight());

   for(size_t h = 0; h < Camera::getAllCameras().size(); h++)
  {
    if(Camera::getAllCameras().at(h)->getGameObject()->getActive() == false)
    {
      continue;
    }
	context->current = Camera::getAllCameras().at(h);
	Colour clearColour = Camera::getCurrent()->getBackgroundColor();
    glClearColor(clearColour.R, clearColour.G, clearColour.B, clearColour.A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	for(size_t i = 0; i < context->gameObjects.size(); i++)
    {
      if((Camera::getCurrent()->getCullMask() & context->gameObjects.at(i)->getLayer()) !=
        context->gameObjects.at(i)->getLayer())
      {
        continue;
      }
	  context->gameObjects.at(i)->render();
    }

   }

	for(size_t i = 0; i < context->gameObjects.size(); i++)
	{
		context->gameObjects.at(i)->postRender();
	}
  
	SDL_GL_SwapWindow(Application::m_window);
  
}

void Application::KeyboardDown(unsigned char _key)
{
	_keyboardDown(_key);
}

void Application::KeyboardUp(unsigned char _key)
{
	_keyboardUp(_key);
}

void Application::_keyboardDown(int _key)
{
	for(size_t i = 0; i < Input::m_keys.size(); i++)
  {
    if(Input::m_keys.at(i) == _key)
    {
      return;
    }
  }
  Input::m_keys.push_back(_key);
  Input::m_downKeys.push_back(_key);
}

void Application::_keyboardUp(int _key)
{
	for(size_t i = 0; i < Input::m_keys.size(); i++)
  {
    if(Input::m_keys.at(i) == _key)
    {
      Input::m_keys.erase(Input::m_keys.begin() + i);
      i--;
    }
  }
	Input::m_upKeys.push_back(_key);
}

void Application::MouseButtonDown(SDL_MouseButtonEvent _mouseButtonEvent)
{
	for(size_t i = 0; i < Input::m_mouseButtonEvents.size(); i++)
  {
    if(Input::m_mouseButtonEvents.at(i).button == _mouseButtonEvent.button)
    {
      return;
    }
  }
  Input::m_mouseButtonEvents.push_back(_mouseButtonEvent);
  Input::m_downMouseButtonEvents.push_back(_mouseButtonEvent);
}

void Application::MouseButtonUp(SDL_MouseButtonEvent _mouseButtonEvent)
{
	for(size_t i = 0; i < Input::m_mouseButtonEvents.size(); i++)
  {
    if(Input::m_mouseButtonEvents.at(i).button == _mouseButtonEvent.button)
    {
      Input::m_mouseButtonEvents.erase(Input::m_mouseButtonEvents.begin() + i);
      i--;
    }
  }
	Input::m_upMouseButtonEvents.push_back(_mouseButtonEvent);
}
  
} // End engine namespace

} // End mutiny namespace
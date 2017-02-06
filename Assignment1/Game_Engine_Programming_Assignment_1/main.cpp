#include "Exception.h"
#include "platform.h"

#include "GameObject.h"

#include "windows.h"
#include <SDL.h>
#include <glm.hpp>


#include <iostream>
using namespace jutiny::engine;

#undef main
void safe_main(int argc, char* argv[])
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 15 );
	if ( Application::init(argc, argv) == false)
	{
		  std::cout << "Something went wrong! Cannot initialise the application!" << std::endl;
		  return;
	}

	ref<GameObject> camera = GameObject::create("camera");
	Camera::setCurrent( camera->addComponent<Camera>() );
	camera->getComponent<Camera>()->setOrthoView(true);

	ref<GameObject> cube = GameObject::create("Cube");
	ref<Shader> shader = cube->addComponent<Shader>();

	shader->setvShaderText("#version 430 core\n\
							 layout(location = 0) in vec4 vPosition;\n\
							 layout(location = 1) in vec4 vColourIn;\n\
							 \n\
							 out vec4 vColour;\n\
							 \n\
							 uniform mat4 modelMat;\n\
							 uniform mat4 viewMat;\n\
							 uniform mat4 projMat;\n\
							 \n\
							 void main()\n\
							 {\n\
									gl_Position = projMat * viewMat * modelMat * vPosition;\n\
									vColour = vColourIn;\n\
							 }");
	shader->setfShaderText("#version 430 core\n\
							 in vec4 vColour;\n\
							 out vec4 fColor;\n\
							 void main(){ fColor = vColour; }");

	ref<Renderer> renderer= cube->addComponent<Renderer>();
	renderer->AddShader(shader);
	cube->addComponent<Mesh>();
	cube->getComponent<Mesh>()->LoadOBJFromPath("Cube.obj");	
	Debug::Log("This is a message.");
	Debug::LogWarning("This is a warning message.");
	Debug::LogError("This is an error message.");
	shader->LoadShader();
	Application::Run();

	Application::Destroy();
}

int main(int argc, char* argv[])
{
    safe_main(argc, argv);

    return 0;
}

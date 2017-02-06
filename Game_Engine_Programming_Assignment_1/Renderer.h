#ifndef RENDERER_H
#define RENDERER_H

#include "Application.h"
#include "Behaviour.h"
#include "GameObject.h"

#include <glm.hpp>

#include "glew.h"

namespace jutiny
{

namespace engine
{

class Renderer : public Behaviour
{
	friend class jutiny::engine::Application;

public:

	virtual ~Renderer();

	//Adds a shader to this Renderer.
	void AddShader(ref<Shader> _shader);

private:

	Matrix4x4 m_modelMatrix;

	Matrix4x4 m_viewMatrix;

	ref<Shader> m_shader;

	//Draws the VAOTris for this Renderer based upon specified parameters.
	void DrawVAOTris(GLuint _VAO, int _out_vertices, GLuint _shaderProgram);

	virtual void onStart();
	virtual void render();

};

}

}

#endif

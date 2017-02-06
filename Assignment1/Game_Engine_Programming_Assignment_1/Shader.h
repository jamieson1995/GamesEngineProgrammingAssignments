#ifndef JUTINY_ENGINE_SHADER_H
#define JUTINY_ENGINE_SHADER_H

#include "Behaviour.h"

#include "glew.h"

namespace jutiny
{

namespace engine
{

class Application;

class Shader : public Behaviour
{
	friend class jutiny::engine::Application;

public:

	void LoadShader();

	void setvShaderText(const char* _text);
	void setfShaderText(const char* _text);

	GLuint getShaderInfo() { return m_shaderInfo; }

	int getShaderModelMatLocation() { return m_shaderModelMatLocation; }
	int getShaderViewMatLocation() { return m_shaderViewMatLocation; }
	int getShaderProjMatLocation() { return m_shaderProjMatLocation; }

	virtual ~Shader();

private:

	GLuint _loadShader();

	const GLchar *m_vShaderText;
	const GLchar *m_fShaderText;

	int m_shaderModelMatLocation;
	int m_shaderViewMatLocation;
	int m_shaderProjMatLocation;

	void setShaderMatLocations();

	GLuint m_shaderInfo;

	bool CheckShaderCompiled(GLuint _shader);

	virtual void onAwake();
	virtual void onDestroy();
};

}

}

#endif
#include "Shader.h"
#include "Debug.h"
#include "GameObject.h"

namespace jutiny
{

namespace engine
{

GLuint Shader::_loadShader()
{
	GLuint program = glCreateProgram();

	GLuint vShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vShader, 1, &m_vShaderText, NULL );
	glCompileShader( vShader );
	if( !CheckShaderCompiled( vShader ) )
	{
		return 0;
	}
	glAttachShader( program, vShader );

	GLuint fShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fShader, 1, &m_fShaderText, NULL );
	glCompileShader( fShader );
	if( !CheckShaderCompiled( fShader ) )
	{
		return 0;
	}
	glAttachShader( program, fShader );

	glLinkProgram( program );
	GLint linked;
	glGetProgramiv( program, GL_LINK_STATUS, &linked );
	if ( !linked )
	{
		GLsizei len;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( program, len, &len, log );
		Debug::LogError("Shader linking failed: ");
		Debug::LogError(log);
		delete [] log;

		return 0;
	}

	return program;
}

bool Shader::CheckShaderCompiled(GLuint _shader)
{
	GLint compiled;
	glGetShaderiv( _shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled )
	{
		GLsizei len;
		glGetShaderiv( _shader, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( _shader, len, &len, log );
		Debug::LogError("Shader compilation failed: ");
		Debug::LogError(log);
		delete [] log;

		return false;
	}

	return true;
}

Shader::~Shader()
{

}

void Shader::setvShaderText(const char* _text)
{
	m_vShaderText = _text;
}

void Shader::setfShaderText(const char* _text)
{
	m_fShaderText = _text;
}

void Shader::onAwake()
{
	m_vShaderText = NULL;
	m_fShaderText = NULL;
}

void Shader::LoadShader()
{
	bool error = false;
	if (m_vShaderText == NULL)
	{
		Debug::LogError("m_vShaderText not set");
		error = true;
	}
	if (m_fShaderText == NULL)
	{
		Debug::LogError("m_fShaderText not set");
		error = true;
	}
	if (error == true)
	{
		return;
	}

	m_shaderInfo = _loadShader();

	setShaderMatLocations();
	glEnable(GL_DEPTH_TEST);
}

void Shader::setShaderMatLocations()
{
	glUseProgram( m_shaderInfo );
	m_shaderModelMatLocation = glGetUniformLocation( m_shaderInfo, "modelMat" );
	m_shaderViewMatLocation = glGetUniformLocation( m_shaderInfo, "viewMat" );
	m_shaderProjMatLocation = glGetUniformLocation( m_shaderInfo, "viewMat" );
}

void Shader::onDestroy()
{
	m_vShaderText = NULL;
	m_fShaderText = NULL;
	m_shaderInfo = NULL;
}

}

}

#include "Renderer.h"
#include "Mesh.h"
#include "Debug.h"
#include "Transform.h"

#include <glm.hpp>

#include "glew.h"

namespace jutiny
{

namespace engine
{

Renderer::~Renderer()
{

}

void Renderer::DrawVAOTris(GLuint _VAO, int _out_vertices, GLuint _shaderProgram)
{
	glUseProgram( _shaderProgram );
	glBindVertexArray( _VAO );
	glDrawArrays(GL_TRIANGLES, 0, _out_vertices);
	glBindVertexArray( 0 );
	glUseProgram( 0 );
}

void Renderer::AddShader(ref<Shader> _shader)
{
	m_shader = _shader;
}

void Renderer::onStart()
{
	m_viewMatrix = Matrix4x4::getTrs( 
	Camera::getCurrent()->getGameObject()->getTransform()->getPosition(),
	Camera::getCurrent()->getGameObject()->getTransform()->getRotation(),
    Vector3(1, 1, 1) * Vector3(1, 1, -1) 
	).inverse();

	ref<Transform> transform = getGameObject()->getTransform();
	m_modelMatrix = Matrix4x4::getTrs( transform->getPosition(), transform->getRotation(), Vector3(1, 1, 1) * Vector3(1, 1, 1)
		
  );
}

void Renderer::render()
{
	glUseProgram( m_shader->getShaderInfo() );
	glUniformMatrix4fv(m_shader->getShaderModelMatLocation(), 1, GL_FALSE, m_modelMatrix.getValue() );
	glUniformMatrix4fv(m_shader->getShaderViewMatLocation(), 1, GL_FALSE, m_viewMatrix.getValue() );
	glUniformMatrix4fv(m_shader->getShaderProjMatLocation(), 1, GL_FALSE, Camera::getCurrent()->getProjectionMatrix().getValue() );

	DrawVAOTris(getGameObject()->getComponent<Mesh>()->getVAO(), getGameObject()->getComponent<Mesh>()->getVertices().size(), m_shader->getShaderInfo());


}

}

}

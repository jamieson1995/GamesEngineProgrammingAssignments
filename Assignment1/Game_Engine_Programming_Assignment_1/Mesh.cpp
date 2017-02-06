#include "Mesh.h"
#include "Application.h"
#include "GameObject.h"
#include "Debug.h"
#include "Exception.h"

#include <iostream>
#include <memory>

namespace jutiny
{

namespace engine
{
	
ref<Mesh> Mesh::LoadOBJFromPath(const char* _path){
	ref<Mesh> mesh = Load(_path, m_vertices);

	m_VAO = CreateVAO(m_vertices);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), &m_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return mesh;
}

ref<Mesh> Mesh::Load(const char* _path, std::vector <Vector3> & _out_vertices)
{
	int vertices = 0;
	int faces = 0;

	//These are temporary variables which are used to store the .obj information
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vector3> temp_vertices;
	std::vector<Vector2> temp_uvs;
	std::vector<Vector3> temp_normals;

	//This line opens the file
	FILE * file = fopen(_path, "r");	
	if (file == NULL){
		Debug::LogError("Cannot open file!");
		return NULL;
	}
	//This while loop will continue until it is told to break
	while (true){

		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		//The loop will break when it reaches the end of the file
		if (res == EOF)
			break;
		//This deals with the vertices information, the floats are read and added to the vertices vector
		if ( strcmp( lineHeader, "v") == 0){
			Vector3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
			vertices++;
		//This deals with the uv information, the floats are read and added to the uv vector
		}else if (strcmp( lineHeader, "vt") == 0){
			Vector2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		//This deals with the normal information, the floats are read and added to the normal vector
		}else if (strcmp( lineHeader, "vn") == 0){
			Vector3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
			faces++;
		//This deals with the faces information, it reads the information and the floats get added to the correct vector
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
	       std::string vertex1, vertex2, vertex3;
	       unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
	       int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
	       if (matches != 9){
			  return NULL;
	       }
		   vertexIndices.push_back(vertexIndex[0]);
	       vertexIndices.push_back(vertexIndex[1]);
	       vertexIndices.push_back(vertexIndex[2]);
	       uvIndices.push_back(uvIndex[0]);
	       uvIndices.push_back(uvIndex[1]);
	       uvIndices.push_back(uvIndex[2]);
	       normalIndices.push_back(normalIndex[0]);
	       normalIndices.push_back(normalIndex[1]);
	       normalIndices.push_back(normalIndex[2]);
		}
	}
	//This goes through each vertex of each face of the object and it is manipulated and then stored in the final vector out_vertices
	for (unsigned int i=0; i<vertexIndices.size(); i++){
		unsigned int vertexIndex = vertexIndices[i];
		Vector3 vertex = temp_vertices[vertexIndex-1];
		_out_vertices.push_back(vertex);
	}

  ref<Mesh> mesh = new Mesh();
  mesh->setVertices(temp_vertices);
  mesh->setNormals(temp_normals);
  mesh->setUv(temp_uvs);

  return mesh;
}

GLuint Mesh::CreateVAO(std::vector <Vector3> & _out_vertices)
{
GLuint VAO = 0;
glGenVertexArrays( 1, &VAO );
glBindVertexArray( VAO );
GLuint buffer = 0;
glGenBuffers(1, &buffer);
glBindBuffer(GL_ARRAY_BUFFER, buffer);
glBufferData(GL_ARRAY_BUFFER, _out_vertices.size() * sizeof(Vector3), &_out_vertices[0], GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
glEnableVertexAttribArray(0);
glVertexAttrib4f(1, 0.0f, 0.0f, 1.0f, 1.0f);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray( 0 );
glDisableVertexAttribArray(0);
return VAO;
}

void Mesh::setVertices(std::vector<Vector3> vertices)
{
  this->m_vertices = vertices;
}

void Mesh::setUv(std::vector<Vector2> uv)
{
  this->m_uv = uv;
}

void Mesh::setNormals(std::vector<Vector3> normals)
{
  this->m_normals = normals;
}

std::vector<Vector3>& Mesh::getVertices()
{
  return m_vertices;
}

std::vector<Vector2>& Mesh::getUv()
{
  return m_uv;
}

std::vector<Vector3>& Mesh::getNormals()
{
  return m_normals;
}

void Mesh::recalculateBounds()
{
  if(m_vertices.size() < 1)
  {
    bounds = Bounds(Vector3(), Vector3());
  }

  float minX = m_vertices.at(0).x; float maxX = m_vertices.at(0).x;
  float minY = m_vertices.at(0).y; float maxY = m_vertices.at(0).y;
  float minZ = m_vertices.at(0).z; float maxZ = m_vertices.at(0).z;

  for(size_t i = 0; i < m_vertices.size(); i++)
  {
    if(m_vertices.at(i).x < minX)
    {
      minX = m_vertices.at(i).x;
    }

    if(m_vertices.at(i).x > maxX)
    {
      maxX = m_vertices.at(i).x;
    }

    if(m_vertices.at(i).y < minY)
    {
      minY = m_vertices.at(i).y;
    }

    if(m_vertices.at(i).y > maxY)
    {
      maxY = m_vertices.at(i).y;
    }

    if(m_vertices.at(i).z < minZ)
    {
      minZ = m_vertices.at(i).z;
    }

    if(m_vertices.at(i).z > maxZ)
    {
      maxZ = m_vertices.at(i).z;
    }
  }

  float midX = (maxX + minX) / 2.0f;
  float midY = (maxY + minY) / 2.0f;
  float midZ = (maxZ + minZ) / 2.0f;

  float sizeX = maxX - minX;
  float sizeY = maxY - minY;
  float sizeZ = maxZ - minZ;

  bounds = Bounds(Vector3(midX, midY, midZ), Vector3(sizeX, sizeY, sizeZ));
}

Bounds Mesh::getBounds()
{
  return bounds;
}

}

}

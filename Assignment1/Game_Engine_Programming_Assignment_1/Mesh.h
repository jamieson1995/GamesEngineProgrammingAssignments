#ifndef JUTINY_ENGINE_MESH_H
#define JUTINY_ENGINE_MESH_H

#include "Vector3.h"
#include "Vector2.h"
#include "Bounds.h"
#include "Behaviour.h"
#include "Colour.h"

#include "glew.h"

#include <vector>
#include <string>
#include <memory>

namespace jutiny
{

namespace engine
{

class Renderer;

class Mesh : public Behaviour
{

  friend class jutiny::engine::Renderer;

public:
  void recalculateNormals();
  void recalculateBounds();

  ref<Mesh> LoadOBJFromPath(const char* _path);

  void setVertices(std::vector<Vector3> _vertices);
  void setUv(std::vector<Vector2> _uv);
  void setNormals(std::vector<Vector3> _normals);

  GLuint CreateVAO(std::vector <Vector3> & _out_vertices);

  std::vector<Vector3>& getVertices();
  std::vector<Vector2>& getUv();
  std::vector<Vector3>& getNormals();

  GLuint getVAO() { return m_VAO; }

  Bounds getBounds();

private:
  static ref<Mesh> Load(const char* _path, std::vector <Vector3> & _out_vertices);

  std::vector<Vector3> m_vertices;
  std::vector<Vector2> m_uv;
  std::vector<Vector3> m_normals;

  GLuint m_VAO;

  Bounds bounds;

};

}

}

#endif


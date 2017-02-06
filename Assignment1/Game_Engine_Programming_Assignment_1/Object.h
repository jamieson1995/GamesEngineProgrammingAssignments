#ifndef JUTINY_ENGINE_OBJECT_H
#define JUTINY_ENGINE_OBJECT_H

#include "ref.h"

#include <string>

namespace jutiny
{

namespace engine
{

class Application;
class GameObject;

class Object : public enable_ref
{
  friend class Application;
  friend class GameObject;

public:
	//Won't destroy the GameObject when changes scene.
  static void dontDestroyOnLoad(ref<Object> _object);
  static void dontDestroyOnLoad(ref<GameObject> _object);

  static void destroy(ref<Object> _object);
  static void destroy(ref<GameObject> _object);

  Object();
  virtual ~Object();

  void setName(std::string _name);
  std::string getName();

private:
  std::string m_name;
  bool m_destroyOnLoad;
  bool m_destroyed;

};

}

}

#endif


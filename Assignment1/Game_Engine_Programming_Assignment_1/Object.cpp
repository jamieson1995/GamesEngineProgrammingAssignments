#include "Object.h"
#include "GameObject.h"

namespace jutiny
{

namespace engine
{

void Object::dontDestroyOnLoad(ref<Object> _object)
{
  _object->m_destroyOnLoad = false;
}

void Object::dontDestroyOnLoad(ref<GameObject> _object)
{
  _object->m_destroyOnLoad = false;
}

void Object::destroy(ref<Object> _object)
{
  _object->m_destroyed = true;
}

void Object::destroy(ref<GameObject> _object)
{
  _object->m_destroyed = true;
}

Object::Object()
{
  m_destroyed = false;
  m_destroyOnLoad = true;
}

Object::~Object()
{

}

std::string Object::getName()
{
  return m_name;
}

void Object::setName(std::string _name)
{
  this->m_name = _name;
}

}

}
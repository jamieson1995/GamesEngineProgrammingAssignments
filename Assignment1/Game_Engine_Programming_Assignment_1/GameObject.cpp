#include "GameObject.h"
#include "Transform.h"
#include "Application.h"

#include "Debug.h"

namespace jutiny
{

namespace engine
{

GameObject::GameObject(std::string _name)
{
  setName(_name);
  addComponent<Transform>(); // Add a transform component to all GameObjects
  Application::getGameObjects().push_back(shared<GameObject>(this)); // Add shared_ptr to created GameObject to vector in Application 
																	 //allowing easy update/rendering/etc of all GameObjects at once
  m_activeSelf = true; // Start active                                    
  m_layer = 1 << 0;    // Default layer
}

GameObject::GameObject()
{
  // As above, but without specified name
  ref<Transform> transform = addComponent<Transform>();
  transform->setPosition(Vector3(0,0,0));
  Application::getGameObjects().push_back(shared<GameObject>(this));
  m_activeSelf = true;
  m_layer = 1 << 0;
}

ref<GameObject> GameObject::create(std::string _name)
{
  ref<GameObject> temp = create(); // Use below function to create new Gameobject
  temp->m_name = _name; // Allocate name

  return temp;
}

ref<GameObject> GameObject::create()
{
  ref<GameObject> temp; // Create a GameObject ref

  temp = new GameObject(); // Assign a new GameObject (created with default constructor)

  return temp;
}

GameObject::~GameObject()
{

}

void GameObject::setLayer(int _layer)
{
  this->m_layer = _layer;
}

int GameObject::getLayer()
{
  return m_layer;
}

void GameObject::awake()
{
  for(size_t i = 0; i < m_components.size(); i++)
  {
    m_components.at(i)->awake();
  }
}

void GameObject::start()
{
  for(size_t i = 0; i < m_components.size(); i++)
  {
    m_components.at(i)->start();
  }
}

void GameObject::update()
{
  for(size_t i = 0; i < m_components.size(); i++)
  {
    // Check each component has not been destroyed before updating
    if(m_components.at(i)->m_destroyed == true)
    {
      // If it has, remove the reference from this GameObject
      m_components.at(i)->destroy();
      m_components.erase(m_components.begin() + i);
      i--;
    }
    else
    {
      m_components.at(i)->update();
    }
  }
}

ref<Transform> GameObject::getTransform()
{
  return getComponent<Transform>();
}

void GameObject::render()
{
  for(size_t i = 0; i < m_components.size(); i++)
  {
    m_components.at(i)->render();
  }
}

void GameObject::postRender()
{
  for(size_t i = 0; i < m_components.size(); i++)
  {
    m_components.at(i)->postRender();
  }
}

void GameObject::destroy()
{
  for(size_t i = 0; i < m_components.size(); i++)
  {
    m_components.at(i)->destroy();
  }
}

void GameObject::setActive(bool active)
{
  this->m_activeSelf = active;
}

bool GameObject::getActiveSelf()
{
  return m_activeSelf;
}

bool GameObject::getActive()
{
  return m_activeSelf;
}

std::string GameObject::getTag()
{
  return m_tag;
}

void GameObject::setTag(std::string tag)
{
  this->m_tag = tag;
}

}

}
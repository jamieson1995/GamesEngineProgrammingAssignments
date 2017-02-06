#ifndef JUTINY_ENGINE_GAMEOBJECT_H
#define JUTINY_ENGINE_GAMEOBJECT_H

#include "Component.h"
#include "Application.h"

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

namespace jutiny
{

namespace engine
{

class Component;
class Transform;


class GameObject : public Object
{
  friend class jutiny::engine::Application;

public:

	//Creates a GameObject reference, and calls the GameObject Constructor.
	static ref<GameObject> create();	

	//Creates a GameObject reference, and calls the GameObject Constructor withspecified name.
	static ref<GameObject> create(std::string _name);


	//Creates a new GameObject, attaches a transform component, and sets the coordinates to (0,0,0).
	GameObject();	
	
	//Creates a new GameObject, attaches a transform component, sets the coordinates to (0,0,0), and names the GameObject uses the specified string.
	GameObject(std::string _name);
	~GameObject();

	//Returns the transform.
	ref<Transform> getTransform();

	void setActive(bool _active);
	bool getActive();

	//Returns whether this GameObject is active.
	bool getActiveSelf();

	int getLayer();
	void setLayer(int _layer);	
 
	void setTag(std::string _tag);
	std::string getTag();

	template <class T>
	ref<T> addComponent()
	{
		shared<T> c(new T()); // Create new component of specified type (T)

		m_components.push_back(c); // Add shared ptr for GameObject to access
		c->gameObject = this;    // Attach component to GameObject
		c->awake();              // Activate component by calling awake

		return c; // Return ref to the component to allow immediate use/allocation (e.g. auto camera = this->addComponent<Camera>() )
	 }

	 template<class T>
	 ref<T> getComponent()
	 {
	   for(int i = 0; i < m_components.size(); i++) // Search components attached to GameObject
	   {
	     ref<T> t = dynamic_cast<T*>(m_components.at(i).get()); // Get ref for current component

	     if(t.valid())
	     {
	       return t; // Return the ref to the component if found
	     }
	   }

	   return ref<T>(); // Else return new/empty ref (NULL)
	 }

private:
	std::vector<shared<Component> > m_components;
	bool m_activeSelf;
	int m_layer;
	std::string m_tag;

	virtual void awake();
	virtual void start();
	virtual void update();
	virtual void render();
	virtual void postRender();
	virtual void destroy();
};

}

}

#endif
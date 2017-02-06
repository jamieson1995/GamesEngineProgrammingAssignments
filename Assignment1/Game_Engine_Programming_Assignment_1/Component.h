#ifndef JUTINY_ENGINE_COMPONENT_H
#define JUTINY_ENGINE_COMPONENT_H

#include "Object.h"

namespace jutiny
{

namespace engine
{

class GameObject;
class Application;

class Component : public Object
{
  friend class GameObject;
  friend class Application;

public:
  virtual ~Component();

  ref<GameObject> getGameObject();

private:
  ref<GameObject> gameObject;

  //Runs when first instantiated.
  virtual void awake();
  //Runs before the first update function.
  virtual void start();
  //Runs every frame.
  virtual void update();
  //Runs during the render sequence.
  virtual void render();
  //Runs after Rendering.
  virtual void postRender();
  //Runs when instance is flagged to be destroyed.
  virtual void destroy();
};

}

}

#endif
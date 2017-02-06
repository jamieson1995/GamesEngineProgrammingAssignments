#include "Component.h"

namespace jutiny
{

namespace engine
{

Component::~Component()
{

}

ref<GameObject> Component::getGameObject()
{
  return gameObject;
}

void Component::awake()
{

}

void Component::start()
{

}

void Component::update()
{

}

void Component::destroy()
{

}

void Component::render()
{

}

void Component::postRender()
{

}

}

}


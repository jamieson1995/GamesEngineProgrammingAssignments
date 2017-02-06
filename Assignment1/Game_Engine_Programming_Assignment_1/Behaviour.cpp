#include "Behaviour.h"
#include "Debug.h"

namespace jutiny
{

namespace engine
{

Behaviour::~Behaviour()
{

}

void Behaviour::awake()
{
  m_started = false;
  onAwake();
}

void Behaviour::update()
{
  if(m_started == false)
  {
    onStart();
    m_started = true;
  }

  onUpdate();
}

void Behaviour::postRender()
{
  if(m_started == false)
  {
    return;
  }

  onPostRender();
}

void Behaviour::destroy()
{
  onDestroy();
}

void Behaviour::onAwake()
{

}

void Behaviour::onStart()
{

}

void Behaviour::onUpdate()
{

}

void Behaviour::onPostRender()
{

}

void Behaviour::onDestroy()
{

}

}

}
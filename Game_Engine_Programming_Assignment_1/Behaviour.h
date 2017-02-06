#ifndef JUTINY_ENGINE_BEHAVIOUR_H
#define JUTINY_ENGINE_BEHAVIOUR_H

#include "Component.h"

namespace jutiny
{

namespace engine
{

class Behaviour : public Component
{
  friend class GameObject;

public:
  virtual ~Behaviour();

  //Runs when first instantiated.
  virtual void onAwake();
  //Runs before the first update function.
  virtual void onStart();
  //Runs every frame.
  virtual void onUpdate();
  //Runs after Rendering.
  virtual void onPostRender();
  //Runs when instance is flagged to be destroyed.
  virtual void onDestroy();

private:
	//Indicates whether this is the first frame or not.
  bool m_started;

  //Runs before the onAwake().
  void awake();
  //Runs before onStart().
  void update();
  //Runs before onPostRender().
  void postRender();
  //Runs before onDestroy().
  void destroy();
};

}

}

#endif
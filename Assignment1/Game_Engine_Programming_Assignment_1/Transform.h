#ifndef JUTINY_ENGINE_TRANSFORM_H
#define JUTINY_ENGINE_TRANSFORM_H

#include "Behaviour.h"
#include "Vector3.h"

#include <vector>

namespace jutiny
{

namespace engine
{

class Transform : public Behaviour
{
public:
  virtual ~Transform();

  Vector3 getPosition();
  Vector3 getRotation();
  Vector3 getScale();
  void setPosition(Vector3 _position);
  void setRotation(Vector3 _rotation);
  void setScale(Vector3 _scale);

  Vector3 getLocalPosition();
  Vector3 getLocalRotation();
  void setLocalPosition(Vector3 _position);
  void setLocalRotation(Vector3 _rotation);
  void setLocalScale(Vector3 _scale);

  //Loops through all children of this transform and sets their parent to NULL
  void detachChildren();

  //Returns the transform parent.
  ref<Transform> getParent();
  void setParent(ref<Transform> _transform);

  //Returns number of children of this transform.
  int getChildCount();

  ref<Transform> getChild(int _index);

  //Goes back up the hierarchy until a transform is reached without a parent.
  ref<Transform> getRoot();

  //Search for a child witha specified name.
  ref<Transform> find(std::string _name);

  void rotate(Vector3 _eulerAngles);
  void translate(Vector3 _translation);
  void lookAt(Vector3 _worldPosition);
  void rotateAround(Vector3 _center, Vector3 _axis, float _amount);

  Vector3 getForward();
  Vector3 getRight();

private:
  Vector3 m_localPosition;
  Vector3 m_localRotation;
  Vector3 m_localScale;
  ref<Transform> parent;
  std::vector<ref<Transform> > children;

  virtual void onAwake();
  virtual void onDestroy();
};

}

}

#endif
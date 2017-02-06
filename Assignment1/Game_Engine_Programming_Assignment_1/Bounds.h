#ifndef JUTINY_ENGINE_BOUNDS_H
#define JUTINY_ENGINE_BOUNDS_H

#include "Vector3.h"

namespace jutiny
{

namespace engine
{

class Bounds
{
public:
  Vector3 center;
  Vector3 size;
  Vector3 extents;
  Vector3 min;
  Vector3 max;

  Bounds();
  Bounds(Vector3 _center, Vector3 _size);

  bool intersects(Bounds _target);
  void setMinMax(Vector3 _min, Vector3 _max);

  void debug();

};

}

}

#endif


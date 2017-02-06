#include "Bounds.h"
#include "Debug.h"

#include <sstream>
#include <iostream>

namespace jutiny
{

namespace engine
{

Bounds::Bounds()
{

}

Bounds::Bounds(Vector3 _center, Vector3 _size)
{
  this->center = _center;
  this->size = _size;
  this->extents = _size / 2.0f;
  this->min = _center - extents;
  this->max = _center + extents;
}

void Bounds::setMinMax(Vector3 _min, Vector3 _max)
{
  center = (_min + _max) / 2.0f;
  extents = _max - center;
  size = extents * 2.0f;
  this->min = center - extents;
  this->max = center + extents;
}

void Bounds::debug()
{
  std::cout << "Center: " << center.x << " " << center.y << " " << center.z << std::endl;
  std::cout << "Size: " << size.x << " " << size.y << " " << size.z << std::endl;
  std::cout << "Extents: " << extents.x << " " << extents.y << " " << extents.z << std::endl;
  std::cout << "Min: " << min.x << " " << min.y << " " << min.z << std::endl;
  std::cout << "Max: " << max.x << " " << max.y << " " << max.z << std::endl;
}

bool Bounds::intersects(Bounds _target)
{
  bool collidingX = false;
  bool collidingY = false;
  bool collidingZ = false;

  if(min.x < _target.min.x)
  {
    if(max.x >= _target.min.x)
    {
      collidingX = true;
    }
  }
  else
  {
    if(_target.max.x >= min.x)
    {
      collidingX = true;
    }
  }

  if(min.y < _target.min.y)
  {
    if(max.y >= _target.min.y)
    {
      collidingY = true;
    }
  }
  else
  {
    if(_target.max.y >= min.y)
    {
      collidingY = true;
    }
  }

  if(min.z < _target.min.z)
  {
    if(max.z >= _target.min.z)
    {
      collidingZ = true;
    }
  }
  else
  {
    if(_target.max.z >= min.z)
    {
      collidingZ = true;
    }
  }

  if(collidingX == true && collidingY == true && collidingZ == true)
  {
    return true;
  }

  return false;
}

}

}


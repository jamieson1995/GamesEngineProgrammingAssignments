#ifndef JUTINY_ENGINE_MATHF_H
#define JUTINY_ENGINE_MATHF_H

namespace jutiny
{

namespace engine
{

class Mathf
{
public:
  static float pi;

  static int nextPowerOfTwo(int _value);	
  static float deg2Rad(float _degrees);

};

}

}

#endif
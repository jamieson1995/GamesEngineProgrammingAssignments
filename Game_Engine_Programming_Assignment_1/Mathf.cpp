#include "Mathf.h"

namespace jutiny
{

namespace engine
{

float Mathf::pi = 3.14159265358979f;

int Mathf::nextPowerOfTwo(int _value)
{
  if( _value != 0 )
  {
   _value--;
   _value |= (_value >> 1); //Or first 2 bits
   _value |= (_value >> 2); //Or next 2 bits
   _value |= (_value >> 4); //Or next 4 bits
   _value |= (_value >> 8); //Or next 8 bits
   _value |= (_value >> 16); //Or next 16 bits
   _value++;
  }

  return _value;
}

float Mathf::deg2Rad(float _degrees)
{
  return (_degrees / 180) * Mathf::pi;
}

}

}
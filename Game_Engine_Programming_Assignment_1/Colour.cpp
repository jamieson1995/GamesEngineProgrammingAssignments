#include "Colour.h"

namespace jutiny
{

namespace engine
{

Colour::Colour()
{
  this->R = 0.0f;
  this->G = 0.0f;
  this->B = 0.0f;
  this->A = 0.0f;
}

Colour::Colour(float _R, float _G, float _B)
{
  this->R= _R;
  this->G= _G;
  this->B= _B;
  this->A= 1.0f;
}

Colour::Colour(float _R, float _G, float _B, float _A)
{
  this->R = _R;
  this->G = _G;
  this->B = _B;
  this->A = _A;
}

}

}
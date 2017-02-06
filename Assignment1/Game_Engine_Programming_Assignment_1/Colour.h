#ifndef JUTINY_ENGINE_COLOUR_H
#define JUTINY_ENGINE_COLOUR_H

namespace jutiny
{

namespace engine
{

class Colour
{
public:
  float R;
  float G;
  float B;
  float A;

  Colour();
  Colour(float _R, float _G, float _B);
  Colour(float _R, float _G, float _B, float _A);

};

}

}

#endif
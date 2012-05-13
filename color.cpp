#include "color.h"

Color::Color (const Color &c) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
  v[0] = c.v[0];
  v[1] = c.v[1];
  v[2] = c.v[2];
  v[3] = c.v[3];
}

Color::  Color(float red, float green, float blue, float alpha)
  : r(v[0]), g(v[1]), b(v[2]), a(v[3]) 
{
  v[0] = red;
  v[1] = green;
  v[2] = blue;
  v[3] = alpha;
}

Color::Color() 
  : r(v[0]), g(v[1]), b(v[2]), a(v[3]) 
{
  v[0] = v[1] = v[2] = 0;
  v[3] = 1;
}

Color& Color::operator=(const Color& c)
{
  v[0] = c.v[0];
  v[1] = c.v[1];
  v[2] = c.v[2];
  v[3] = c.v[3];
  return *this;
}

ostream& operator<< (ostream &os, const Color &c) 
{
  os << c.v[0] << ", " << c.v[1] << ", " << c.v[2] << ", " << c.v[3] << endl;
  return os;
}


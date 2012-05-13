#include "face.h"
#include <cmath>

Face::Face() 
{}

Face::Face(int i1, int i2, int i3, int i4)
{
  vertices.push_back(i1);
  vertices.push_back(i2);
  vertices.push_back(i3);
  if (i4!=-1) vertices.push_back(i4);
}




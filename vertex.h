#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "point.h"

// Vertex - representa un vertex d'un objecte 3D
class Vertex
{
 public:
  Vertex(const Point& coordenades);

  // atributs
  Point coord;		// coordenades del vertex
};
#endif

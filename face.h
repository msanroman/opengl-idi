#ifndef _FACE_H_
#define _FACE_H_

#include <vector>

using namespace std;

// Face - representa una cara d'un objecte 3D
class Face
{
 public:
  Face();

  // constructor a partir de 3 o 4 indexs a vertex
  Face(int i1, int i2, int i3, int i4=-1); 

  // atributs
  int material;	       // ID del material (index del material)
  vector<int> vertices;  // vector amb els indexs dels vertexs de la cara
};
#endif

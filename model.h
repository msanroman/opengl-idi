#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "vertex.h"
#include "box.h"
#include "face.h"
#include "material_lib.h"

using namespace std;

// Model - permet representar un objecte 3D
class Model
{
 public:
  Model(std::string);

  // llegeix un model en format OBJ
  void readObj(const char* filename, MaterialLib& matlib);

  // calcula la capsa del model
  void updateBoundingBox();

  // retorna la capsa del model (previament s'ha d'haver calculat)
  Box boundingBox() const;

  void Render();

 private:
  void make_face ( char **words, int nwords, int material );
  void netejaDades ();

 public:
  vector<Vertex> vertices;  // vector amb els vertexs de l'objecte
  vector<Face> faces;       // vector amb les cares de l'objecte

 private: 
  std::string name;
  Box _boundingBox;   // caixa contenidora de l'objecte.
};


#endif

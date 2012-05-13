#ifndef _Scene_H_
#define _Scene_H_
#include "objectInstance.h"
#include "model.h"
#include "ground.h"
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#  include <GL/gl.h>
#endif

class Scene
{
  friend class XML;
 private:

  // Aix� �s per a millorar la cerca dels objectes dins del vector.
  static int LEAVES;
  static int STEM;
  static int CASA1;
  static int CASA2;
  static int CASA3;
  static int OBELISC;
  static int FAROLA;

  Ground ground;
  bool load;
	
  // Tindrem un vector amb els models geom�trics dels objectes urbans
  // b�sics (o primitius) i un altre amb inst�ncies seves (inst�ncies o 
  // refer�ncies a objectes).
  std::vector<Model> lmodels;
  std::vector<ObjectInstance> lobjectsInstances;

  void computeTransformedBox(ObjectInstance &oref);
  void transformPoint(ObjectInstance &oref, GLfloat p[4]);

 public:
  Box capsa;
  static MaterialLib matlib;	  // col�lecci� de materials 
  Scene();
  void Init();
  void Render();
  void AddModel(Model &);
  void AddObject(ObjectInstance &);
  void computeTransformedBoxes();
  void CalculaEsfera (double &radi, Point &centreEscena);
  void InitGround(double sx, double sz);
  static void transformPoint(Point &p);
  int dolphinPos;
  void moveDolphinForward();
  void rotateDolphinLeft();
  void rotateDolphinRight();

};

#endif

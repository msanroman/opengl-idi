#ifndef _objectInstance_H_
#define _objectInstance_H_

#include <vector>
#include "point.h"
#include "model.h"
#include "box.h"

class ObjectInstance
{
 private:
  int object;   // identificador de l'objecte
  Point pos;    // posicio sobre el terra
  Vector size;	   // mida en unitats
  float orientation;  //orientació respecte Y
  float x_orientation;
  Box _transBox;      // caixa contenidora de l'objecte transformat.

 public:
  ObjectInstance(int idob, Point p, Vector sz, float ori);
  ObjectInstance(int idob, Point p, Vector sz, float ori, float ori_x);
  ~ObjectInstance(void);

  void Render(std::vector<Model> &);

  int getObjectId();
  void computeTransformedBox(Model &obj);

  Box & getTransformedBox ();
  void moveForward();
  void rotateRight();
  void rotateLeft();
};

#endif

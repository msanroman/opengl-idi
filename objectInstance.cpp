#include "objectInstance.h"
#include "cameraIDI.h"
#include "scene.h"

ObjectInstance::ObjectInstance(int ob, Point p, Vector sz, float ori):
  object(ob), pos(p), size(sz), orientation(ori)
{}

ObjectInstance::ObjectInstance(int ob, Point p, Vector sz, float ori, float ori_x):
  object(ob), pos(p), size(sz), orientation(ori), x_orientation(ori_x)
{}

  ObjectInstance::~ObjectInstance(void)
{}


void ObjectInstance::Render(std::vector<Model> &lmodels) 
{
  // Cal aplicar les transformacions de model necessàries i pintar l'objecte
	
  Model &o=lmodels[object];
  Box box=o.boundingBox();
	
  //CENTRE DE LA BASE DE LA CAIXA CONTENIDORA (BOUNDING BOX)
  Point centreBB;
  centreBB.x = (box.maxb.x+box.minb.x)/2;
  centreBB.z = (box.maxb.z+box.minb.z)/2;
	
  //MIDA EN COORDENADES DE LA CAIXA CONTENIDORA
  float midaX=box.maxb.x-box.minb.x;
  float midaY=box.maxb.y-box.minb.y;
  float midaZ=box.maxb.z-box.minb.z;


  cameraIDI camAux;

  camAux.iniciTGModelat();
  camAux.trasllada(pos.x, pos.y, pos.z);
  camAux.rota(orientation, 0.0, 1.0, 0.0);
  camAux.rota(x_orientation, 1.0, 0.0, 0.0);
  camAux.escala(size.x/midaX, size.y/midaY, size.z/midaZ);
  camAux.trasllada(-centreBB.x, -box.minb.y, -centreBB.z);
  //Pintem l'objecte
  o.Render();	
  camAux.fiTGModelat();

  //  	_transBox.Render();  // descomentar si es vol pintar la capsa englobant
}


int ObjectInstance::getObjectId()
{
  return object;
}

// Calculem la caixa transformada a partir de la caixa original
// de l'objecte
void ObjectInstance::computeTransformedBox(Model &obj)
{
  Box b = obj.boundingBox();
  float sa, sb, sc;
  sa=b.maxb.x-b.minb.x;	
  sb=b.maxb.y-b.minb.y;	
  sc = b.maxb.z - b.minb.z;	

  cameraIDI camAux;
  camAux.iniciTGModelat();
  camAux.identitat();

  camAux.trasllada(pos.x, pos.y, pos.z);
  camAux.rota(orientation, 0, 1, 0);
  camAux.escala(size.x/sa, size.y/sb, size.z/sc);
  camAux.trasllada(-0.5*(b.maxb.x + b.minb.x), -b.minb.y, -0.5*(b.maxb.z + b.minb.z));

  vector<Vertex> &verts = obj.vertices;
  Point punt(verts[0].coord.x, verts[0].coord.y, verts[0].coord.z);
  Scene::transformPoint(punt);
  _transBox.init(punt);

  for (unsigned int i=1; i<verts.size(); ++i)
    {
      Point punt(verts[i].coord.x, verts[i].coord.y, verts[i].coord.z);
      Scene::transformPoint(punt);
      _transBox.update(punt);
    }
  camAux.fiTGModelat();
}

Box & ObjectInstance::getTransformedBox ()
{
  return _transBox;
}

void ObjectInstance::moveForward()
{
    this->pos.z -= 1;
}

void ObjectInstance::rotateRight()
{
    this->orientation -= 10;
}

void ObjectInstance::rotateLeft()
{
    this->orientation += 10;
}

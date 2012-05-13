#include "scene.h"
#include "XML.h"
#include <cmath>

int Scene::CASA1=0;
int Scene::CASA2=1;
int Scene::CASA3=2;
int Scene::OBELISC=3;

MaterialLib Scene::matlib;

Scene::Scene() {
  load=false;
}

void Scene::Init()
{
  XML xmlloader;
  xmlloader.LoadSceneDescription(this, "escena.xml");
}

// Modifica un punt donat aplicant-li la transformació que es té guardada
// a la matriu MODELVIEW
void Scene::transformPoint(Point &p)
{
  GLfloat m[16];
  GLfloat p1[16];

  int i; 
  for (i=4; i<16; ++i) p1[i]=0.0f;

  p1[0] = p.x; 
  p1[1] = p.y; 
  p1[2] = p.z; 
  p1[3] = 1;

  glPushMatrix();
  glMultMatrixf(p1);
  glGetFloatv(GL_MODELVIEW_MATRIX, m);
  p.x = m[0];
  p.y = m[1];
  p.z = m[2];
  glPopMatrix();
}

// Mètode que pinta l'escena: el terra, els objectes i el que calgui
void Scene::Render() {

  //pintem el terra
  ground.Render();
	
  // Cal pintar tots els objectes de l'escena que es troben al vector
  //recorrem tots els objects i fem per cada object un object.Render()
  for (unsigned int i = 0; i < lobjectsInstances.size(); ++i) 
    {
//      if (i%3 == 0)
	lobjectsInstances[i].Render(lmodels);
		
    }
}

//----------------------------------------------------------------------------------------
void Scene::AddModel(Model &o)
{
  lmodels.push_back(o);
}

void Scene::AddObject(ObjectInstance &oref)
{
  lobjectsInstances.push_back(oref);
  this->dolphinPos = lobjectsInstances.size() - 1;
}

// Calcula les caixes contenidores dels objectes de l'escena
// un cop s'han fet les transformacions de model
void Scene::computeTransformedBoxes()
{
  std::vector<ObjectInstance>::iterator ito;
  for (ito=lobjectsInstances.begin(); ito!=lobjectsInstances.end(); ito++)
    {
      (*ito).computeTransformedBox(lmodels[(*ito).getObjectId()]);
    }
}

void Scene::CalculaEsfera (double &radi, Point &centreEscena)
{
  // creem la capsa inicialment amb els vèrtexs mínim i màxim del terra
  Box capsaEscena (Point (0.0, -ground.MidaY(), 0.0),
		   Point (ground.MidaX(), 0.0, ground.MidaZ()));

  // actualitzem la capsa amb tots els objectes de l'escena
  std::vector<ObjectInstance>::iterator ito;
  for (ito=lobjectsInstances.begin(); ito!=lobjectsInstances.end(); ito++)
    {
      Point punts[8];
      punts[0] = (*ito).getTransformedBox().minb;
      punts[7] = (*ito).getTransformedBox().maxb;

      punts[1].x = punts[7].x;
      punts[1].y = punts[0].y;
      punts[1].z = punts[0].z;
    
      punts[2].x = punts[0].x;
      punts[2].y = punts[7].y;
      punts[2].z = punts[0].z;
    
      punts[3].x = punts[0].x;
      punts[3].y = punts[0].y;
      punts[3].z = punts[7].z;
    
      punts[4].x = punts[7].x;
      punts[4].y = punts[7].y;
      punts[4].z = punts[0].z;

      punts[5].x = punts[0].x;
      punts[5].y = punts[7].y;
      punts[5].z = punts[7].z;
    
      punts[6].x = punts[7].x;
      punts[6].y = punts[0].y;
      punts[6].z = punts[7].z;

      for (int i=0; i<8; ++i)
	capsaEscena.update(punts[i]);
    }  
  centreEscena =  (capsaEscena.minb + capsaEscena.maxb)/2;
  radi = (capsaEscena.maxb-capsaEscena.minb).length()/2.f;
  this->capsa = capsaEscena;
}

//--------------------------------------------------------------------------------------------
void Scene::InitGround(double sx, double sz)
{
  ground.Init(sx,sz);
}

void Scene::moveDolphinForward()
{
  lobjectsInstances[dolphinPos].moveForward();
}

void Scene::rotateDolphinLeft()
{
  lobjectsInstances[dolphinPos].rotateLeft();
}

void Scene::rotateDolphinRight()
{
  lobjectsInstances[dolphinPos].rotateRight();
}

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "color.h"
#include <string>

// Material - permet representar les propietats optiques d'un material
class Material
{
 public:
  Material(const string& _name="default", 
	   const Color& _ka=Color(0.2f, 0.2f, 0.2f), 
	   const Color& _kd=Color(0.8f, 0.8f, 0.8f),
	   const Color& _ks=Color(1.0f, 1.0f, 1.0f),
	   float _shininess=10.f);

  string name;
  Color ka, kd, ks;
  float shininess; 
};

ostream& operator<< (ostream &os, const Material &m);
#endif

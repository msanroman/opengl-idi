#ifndef _MATERIAL_LIB_H_
#define _MATERIAL_LIB_H_

#include "material.h"

#include <vector>
#include <map>
using namespace std;

class MaterialLib
{
 public:
  MaterialLib();

  // llegeix els materials d'un fitxer .mtl, afegint-los a la biblioteca 
  void readMtl(const char* filename);

  // retorna el material corresponent a un index donat;
  // si no hi ha cap material amb aquest index, es retorna el material per defecte (index 0)
  const Material& material(int index) const;

  // donat un nom de material, retorna el seu index
  int index(const string& name) const; 

 private:
  vector<Material> materials;
  mutable map<string, int> dict;

  friend ostream& operator<< (ostream &os, const MaterialLib &m);
};

ostream& operator<< (ostream &os, const MaterialLib &m);

#endif

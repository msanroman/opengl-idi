#include "material.h"

Material::Material(const string& _name, const Color& _ka, const Color& _kd, const Color& _ks, float _shininess)
  : name(_name), ka(_ka), kd(_kd), ks(_ks), shininess(_shininess) 
{}

ostream& operator<< (ostream &os, const Material &m) 
{
  os << "Material: " << m.name << endl;
  os << " Ka " << m.ka << endl;
  os << " Kd " << m.kd << endl;
  os << " Ks " << m.ks << endl;
  os << " Shininess " << m.shininess << endl;
  return os;
}


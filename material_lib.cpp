#include "material_lib.h"
#include <fstream>

MaterialLib::MaterialLib()
{
  // afegeix un material per defecte a la posicio 0
  dict["material per defecte"]=0;
  materials.push_back(Material("material per defecte"));
  // afegeix un segon material (vermell) a la posicio 1 
  dict["material vermell"]=1;
  materials.push_back(Material("material vermell", Color(.4,0,0),Color(.8,0,0))); 

}

void MaterialLib::readMtl(const char* filename)
{
  ifstream f(filename); 	

  if (f.fail()) 
    {
      cerr << "No puc obrir el fitxer de materials <" << filename << ">" << endl;
    }
  else
    {
      Material* mat=0; // apuntador al material que estem llegint
      string cad;
      f >> cad;
      while (!f.eof())
	{
	  if (cad=="newmtl") 
	    {
	      // crear nou material
	      string name;
	      f >> name;
	      dict[name]=materials.size();
	      materials.push_back(Material(name));
	      mat = &materials[materials.size()-1];
	    }
	  else if (cad=="Ka")
	    {
	      f >> mat->ka.r >> mat->ka.g >> mat->ka.b; 
	    }
	  else if (cad=="Kd")
	    {
	      f >> mat->kd.r >> mat->kd.g >> mat->kd.b; 
	    }
	  else if (cad=="Ks")
	    {
	      f >> mat->ks.r >> mat->ks.g >> mat->ks.b; 
	    }
	  else if (cad=="d")
	    {
	      float alfa;
	      f >> alfa;
	      mat->ka.a = mat->kd.a = mat->ks.a = alfa;
	    }
	  else if (cad=="Ns")
	    {
	      f >> mat->shininess;
	    }

	  f >> cad;
	}
    }
}

const Material& MaterialLib::material(int index) const
{
  if (index >=0 && index < int(materials.size()))
    return materials[index];
  else return materials[0];
}

int MaterialLib::index(const string& name) const
{
  return dict[name];
}

ostream& operator<< (ostream &os, const MaterialLib &m) 
{
  os << "Material Lib: " << endl;
  for (unsigned int i=0; i<m.materials.size(); i++)  os << m.materials[i] << endl;
  return os;
}

#if !defined(_XML_H)
#define _XML_H
#include "tinyxml.h"
#include "scene.h"

class Scene;

class XML
{
 private:
  const char * getIndent( unsigned int numIndents );
  const char * getIndentAlt( unsigned int numIndents );
  int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent);
  void dump_to_stdout( TiXmlNode* pParent, unsigned int indent=0);
  void ProcessFile(Scene *, TiXmlNode* pParent, unsigned int indent=0);
  void ProcessObject(Scene *scene, TiXmlNode* pParent);
  void ProcessScene(Scene *scene, TiXmlNode* pParent);
	
  bool AttributeExists(TiXmlElement* , const char *);
  int getIdObject(std::string n);

 public:
  XML(void);
  ~XML(void);
  bool LoadSceneDescription(Scene *, const char *);
};

#endif

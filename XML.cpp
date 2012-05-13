#include "XML.h"
#include "model.h"
#include "objectInstance.h"

const unsigned int NUM_INDENTS_PER_SPACE=2;

XML::XML(void)
{}

XML::~XML(void)
{}

bool XML::LoadSceneDescription(Scene *scene, const char *file)
{
  TiXmlDocument doc(file);
  bool loadOkay = doc.LoadFile();
  if (loadOkay)
    {
      printf("\n%s:\n", file);
      ProcessFile(scene, &doc ); // defined later in the tutorial
    }
  else
    {
      printf("Failed to load file \"%s\"\n", file);
    }
  return loadOkay;
}


void XML::ProcessFile(Scene *scene, TiXmlNode* pParent, unsigned int indent )
{
  if ( !pParent ) return;
  
  TiXmlNode* pChild;
  const char *valor;

  int t = pParent->Type();
  switch ( t )
    {
    case TiXmlNode::ELEMENT: 
      valor=pParent->Value();
      if (strcmp(valor,"object")==0)
	ProcessObject(scene, pParent);
      if (strcmp(valor,"objectref")==0)
	ProcessScene(scene, pParent);
      break;
    case TiXmlNode::TEXT: 
      break;
    }
  for (pChild = pParent->FirstChild(); pChild != 0; 
       pChild = pChild->NextSibling()) 
    {
      ProcessFile( scene, pChild, indent+1 );
    }
}

void XML::ProcessObject(Scene *scene, TiXmlNode* pParent)
{
  TiXmlElement *sonel;
  std::string nom, filename;
  

  sonel=pParent->ToElement();
  nom=sonel->Attribute("name");	
  if (AttributeExists(sonel, "file"))
    {
      std::string k=sonel->Attribute("file");
      // filename="resources\\"+k;
      filename="resources/"+k;
      Model o(nom);
      o.readObj(filename.c_str(), scene->matlib);
      o.updateBoundingBox();
      scene->AddModel(o);
    }
  else
    scene->InitGround(atof(sonel->Attribute("sx")), atof(sonel->Attribute("sz")));
}

int XML::getIdObject(std::string n)
{
  if (n=="CASA1") return Scene::CASA1;
  if (n=="CASA2") return Scene::CASA2;
  if (n=="CASA3") return Scene::CASA3;
  if (n=="OBELISC") return Scene::OBELISC;
  
  return 0;
}

void XML::ProcessScene(Scene *scene, TiXmlNode* pParent)
{
  int idobj;
  float xpos, ypos, zpos, orientation;
  float sizex, sizey, sizez;

  TiXmlElement *name_node=pParent->ToElement();
  std::string nomobj=name_node->Attribute("object");
  idobj=getIdObject(nomobj);

  TiXmlNode *pos_node=pParent->FirstChild();   //Això obtè el node <position>
  xpos=atof(pos_node->ToElement()->Attribute("x"));
  ypos=atof(pos_node->ToElement()->Attribute("y"));
  zpos=atof(pos_node->ToElement()->Attribute("z"));

  TiXmlNode *size_nodex=pos_node->NextSibling();
  sizex=atof(size_nodex->ToElement()->GetText());
  
  TiXmlNode *size_nodey=size_nodex->NextSibling();
  sizey=atof(size_nodey->ToElement()->GetText());
  
  TiXmlNode *size_nodez=size_nodey->NextSibling();
  sizez=atof(size_nodez->ToElement()->GetText());

  TiXmlNode *orient_node=size_nodez->NextSibling();
  orientation=atof(orient_node->ToElement()->GetText());

  ObjectInstance oref(idobj, Point(xpos, ypos, zpos),
		      Vector(sizex, sizey, sizez), orientation);


  scene->AddObject(oref);
}

const char * XML::getIndent( unsigned int numIndents )
{
  static const char * pINDENT="                                      + ";
  static const unsigned int LENGTH=strlen( pINDENT );
  unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
  if ( n > LENGTH ) n = LENGTH;
  
  return &pINDENT[ LENGTH-n ];
}

// same as getIndent but no "+" at the end
const char * XML::getIndentAlt( unsigned int numIndents )
{
  static const char * pINDENT="                                        ";
  static const unsigned int LENGTH=strlen( pINDENT );
  unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
  if ( n > LENGTH ) n = LENGTH;
  
  return &pINDENT[ LENGTH-n ];
}

int XML::dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent)
{
  if ( !pElement ) return 0;

  TiXmlAttribute* pAttrib=pElement->FirstAttribute();
  int i=0;
  int ival;
  double dval;
  const char* pIndent=getIndent(indent);
  printf("\n");
  while (pAttrib)
    {
      printf( "%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());
    
      if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)    printf( " int=%d", ival);
      if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) printf( " d=%1.1f", dval);
      printf( "\n" );
      i++;
      pAttrib=pAttrib->Next();
    }
  return i;	
}

bool XML::AttributeExists(TiXmlElement* son, const char *at)
{
  const char *aux;
  aux=son->Attribute(at);
  if (aux!=0) return true;
  else return false;
}

void XML::dump_to_stdout( TiXmlNode* pParent, unsigned int indent )
{
  if ( !pParent ) return;
  
  TiXmlNode* pChild;
  TiXmlText* pText;
  int t = pParent->Type();
  printf( "%s", getIndent(indent));
  int num;
  
  switch ( t )
    {
    case TiXmlNode::DOCUMENT:
      printf( "Document" );
      break;

    case TiXmlNode::ELEMENT:
      printf( "Element [%s]", pParent->Value() );
      num=dump_attribs_to_stdout(pParent->ToElement(), indent+1);
      switch(num)
	{
        case 0:  printf( " (No attributes)"); break;
        case 1:  printf( "%s1 attribute", getIndentAlt(indent)); break;
        default: printf( "%s%d attributes", getIndentAlt(indent), num); break;
	}
      break;
      
    case TiXmlNode::COMMENT:
      printf( "Comment: [%s]", pParent->Value());
      break;
      
    case TiXmlNode::UNKNOWN:
      printf( "Unknown" );
      break;
      
    case TiXmlNode::TEXT:
      pText = pParent->ToText();
      printf( "Text: [%s]", pText->Value() );
      break;

    case TiXmlNode::DECLARATION:
      printf( "Declaration" );
      break;
    default:
      break;
    }
  printf( "\n" );
  for (pChild = pParent->FirstChild(); pChild != 0; 
       pChild = pChild->NextSibling()) 
    {
      dump_to_stdout( pChild, indent+1 );
    }
}


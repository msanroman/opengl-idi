#include "model.h"
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <QtOpenGL/qgl.h>
#include "scene.h"

using namespace std;

Model::Model(std::string n):name(n)
{}

Box Model::boundingBox() const
{
  return _boundingBox;
}

void Model::updateBoundingBox()
{
  if (vertices.size())
    {
      Point p = vertices[0].coord;
      _boundingBox=Box(p, p);
      for (unsigned int i=1; i<vertices.size(); i++)
	_boundingBox.update(vertices[i].coord);
    }
}


void Model::Render() {
  for (unsigned int i = 0; i < faces.size(); ++i) {
    const Material& mat = Scene::matlib.material(faces[i].material);

    glBegin(GL_POLYGON);
    glColor3f(mat.kd.r, mat.kd.g, mat.kd.b);
    // Per a pintar del color adequat, heu de fer servir
    // mat.kd amb els seus canals corresponents en comptes
    // d'utilitzar el color per defecte que hem posat...
	
    for(unsigned int j = 0; j < faces[i].vertices.size(); ++j) {

      glVertex3f(vertices[faces[i].vertices[j]].coord.x, 
		 vertices[faces[i].vertices[j]].coord.y, 
		 vertices[faces[i].vertices[j]].coord.z);
    }
    glEnd();
  }
}




/*
  Lectura d'un fitxer OBJ

  Conté fragments de codi de obj_2_ply.c (C) Greg Turk

  -----------------------------------------------------------------------
  Copyright (c) 1998 Georgia Institute of Technology.  All rights reserved.   

  Permission to use, copy, modify and distribute this software and its   
  documentation for any purpose is hereby granted without fee, provided   
  that the above copyright notice and this permission notice appear in   
  all copies of this software and that you do not sell the software.   
*/


/* for file reading */
static char **words;
static int max_words = 0;
static int num_words = 0;
#define BIG_STRING 4096
static char str[BIG_STRING];
static char str_orig[BIG_STRING];

void get_indices ( char *word, int *vindex, int *tindex, int *nindex )

/******************************************************************************

GET_INDICES breaks up a word that may have slash-separated numbers into one or more
numbers.

Entry:
word - word to break up

Exit:
vindex - first number (vertex index)
tindex - second number (texture index)
nindex - third number (normal vector index)
******************************************************************************/
{
  const char *null = " ";
  char *ptr;
  const char *tp;
  const char *np;

  /* by default, the texture and normal pointers are set to the null string */

  tp = null;
  np = null;

  /* replace slashes with null characters and cause tp and np to point */
  /* to character immediately following the first or second slash */

  for (ptr = word; *ptr != '\0'; ptr++) {
    if (*ptr == '/') {
      if (tp == null)
	tp = ptr + 1;
      else
	np = ptr + 1;
      
      *ptr = '\0';
    }
  }

  *vindex = atoi (word);
  *tindex = atoi (tp);
  *nindex = atoi (np);
}

void Model::make_face ( char **words, int nwords, int currentMaterial )
{
  Face face;
  for (int i = 0; i < nwords; i++) 
    {
      int vindex;
      int nindex;
      int tindex;

      if ((words[i][0]>='0')&&(words[i][0]<='9'))
	{
	  get_indices (words[i], &vindex, &tindex, &nindex);
      
#if 0
	  printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

	  /* store the vertex index */

	  if (vindex > 0)       /* indices are from one, not zero */
	    face.vertices.push_back(vindex - 1);
	  else if (vindex < 0)  /* negative indices mean count backwards */
	    face.vertices.push_back(vertices.size() + vindex);
	  else 
	    {
	      fprintf (stderr, "Zero indices not allowed: '%s'\n", str_orig);
	      exit (-1);
	    }

	  /*
	    if ((tindex != 0 || nindex != 0) && warning == 0) {
	    fprintf (stderr, "\n");
	    fprintf (stderr, "Warning: textures and normals currently ignored.\n");
	    fprintf (stderr, "\n");
	    warning = 1;
	    }
	  */
	}
    }
  face.material = currentMaterial;
  
  faces.push_back(face);
}

char *fetch_line ( FILE *fp )
{
  //int i,j;
  char *ptr;
  char *ptr2;
  char *result;
  //char *comment_ptr;
  
  /* read in a line */
  result = fgets (str, BIG_STRING, fp);
  
  /* return NULL if we're at the end-of-file */
  if (result == NULL)
    return ((char *) -1);
  
  /* convert line-feed and tabs into spaces */
  /* (this guarentees that there will be a space before the */
  /*  null character at the end of the string) */
  
  str[BIG_STRING-2] = ' ';
  str[BIG_STRING-1] = '\0';
  
  for (ptr = str; *ptr != '\0'; ptr++) {
    if (*ptr == '\t') {
      *ptr = ' ';
    }
    else if (*ptr == '\n') {
      *ptr = ' ';
      break;
    }
  }

  /* copy the line */
  for (ptr = str, ptr2 = str_orig; *ptr != '\0'; ptr++, ptr2++)
    *ptr2 = *ptr;
  *ptr2 = '\0';
  
  /* look to see if this is a comment line (first non-space is '#') */
  
  for (ptr = str; *ptr != '\0'; ptr++) {
    if (*ptr == '#') {
      ptr++;
      while (*ptr == ' ')
	ptr++;
      return (ptr);
    }
    else if (*ptr != ' ') {
      break;
    }
  }

  /* if we get here, we've got a non-comment line */

  /* strip off trailing comments */

  while (*ptr != '\0') {
    if (*ptr == '#') {
      *ptr++ = ' ';
      *ptr = '\0';
      break;
    }
    ptr++;
  }

  return (NULL);
}

int fetch_words ( void )
{
  char *ptr;

  /* allocate room for words if necessary */
  if (max_words == 0) {
    max_words = 20;
    words = (char **) malloc (sizeof (char *) * max_words);
  }

  /* find the words in the line */
  
  ptr = str;
  num_words = 0;
  
  while (*ptr != '\0') {
    /* jump over leading spaces */
    while (*ptr == ' ')
      ptr++;

    /* break if we reach the end */
    if (*ptr == '\0')
      break;
    
    /* allocate more room for words if necessary */
    if (num_words >= max_words) {
      max_words += 10;
      words = (char **) realloc (words, sizeof (char *) * max_words);
    }
    
    /* save pointer to beginning of word */
    words[num_words++] = ptr;
    
    /* jump over non-spaces */
    while (*ptr != ' ')
      ptr++;
    
    /* place a null character here to mark the end of the word */
    *ptr++ = '\0';
  }

  /* return the number of words */
  return (num_words);
}

string getPath(const string& filename)
{
  int i=filename.length()-1;
  bool found = false;
  while (i>=0 && !found)
    {
      if (filename[i]=='/' || filename[i]=='\\') found=true;
      else --i;
    }
  return filename.substr(0, i+1);
}

// llegeix tots els fitxers .mtl i els afegeix a matlib
void read_mtllib( char **words, int nwords, MaterialLib& matlib, 
		  const string& filename )
{
  string path = getPath(filename);
  for (int i = 0; i < nwords; i++) 
    {
      int size = strlen(words[i])-1;
      while (size && (words[i][size]=='\n' || words[i][size]=='\r') ) words[i][size--]=0;
      matlib.readMtl((path+words[i]).c_str());
    }
}

// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), tambe es llegeixen. 
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
//  

void Model::readObj(const char* filename, MaterialLib& matlib)
{
  char* locale = setlocale(LC_ALL,NULL); 
  setlocale(LC_NUMERIC, "C"); 
  int currentMaterial = -1;  
  
  FILE *fp = fopen(filename,"rb");
  if (!fp)
    {
      cout << "No puc obrir el fitxer " << filename << endl;
    }
  else {
    netejaDades();
    while (true) 
      {
	char *comment_ptr = fetch_line (fp);
      
	if (comment_ptr == (char *) -1)  /* end-of-file */
	  break;
    
	/* did we get a comment? */
	if (comment_ptr) {
	  //make_comment (comment_ptr);
	  continue;
	}
    
	/* if we get here, the line was not a comment */
	int nwords = fetch_words();
      
	/* skip empty lines */
	if (nwords == 0)
	  continue;
    
	char *first_word = words[0];
      
	if (!strcmp (first_word, "v")) 
	  {
	    if (nwords < 4) 
	      {
		fprintf (stderr, "Too few coordinates: '%s'", str_orig);
		exit (-1);
	      }
	    float x = atof (words[1]);
	    float y = atof (words[2]);
	    float z = atof (words[3]);
	
	    if (nwords == 5) 
	      {
		float w = atof (words[4]);
		x/=w;
		y/=w;
		z/=w;
	      }
	
	    //addVertex(Vertex(Point(x,y,z)));
	    vertices.push_back(Vertex(Point(x,y,z)));
	  }
	else if (!strcmp (first_word, "vn")) {
	}
	else if (!strcmp (first_word, "vt")) {
	}
	else if (!strcmp (first_word, "f")) {
	  make_face (&words[1], nwords-1, currentMaterial);
	}
	// added 
	else if (!strcmp (first_word, "mtllib")) {
	  read_mtllib (&words[1], nwords-1, matlib, filename);
	}
	else if (!strcmp (first_word, "usemtl")) {
	  int size = strlen(words[1])-1;
	  while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
	  currentMaterial = matlib.index(words[1]);
	}
	// fadded
	else {
	  //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
	}  
      }
  }
  setlocale(LC_ALL, locale);
}

// Netela les dades de l'objecte per a poder carregar un nou model
void Model::netejaDades ()
{
  vertices.clear();
  faces.clear();
  _boundingBox.init(Point());
}

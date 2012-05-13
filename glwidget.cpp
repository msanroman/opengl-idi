#include "glwidget.h"

#include <stdlib.h>
#define _USE_MATH_DEFINES 1
#include <cmath>

// Constructora amb format per defecte
GLWidget::GLWidget(QWidget * parent)
  : QGLWidget (parent)
{

  // Cal activar el timer per generar animacions a l'escena
  connect( &timer, SIGNAL(timeout()), this, SLOT(updateGL()) );
  timer.start(0);
  usingFog = false;
  DoingInteractive = NONE;  
}

// initializeGL() - Aqui incloem les inicialitzacions del context grafic.
void GLWidget::initializeGL()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_DEPTH_TEST);
  // inicialitzem també l'escena
  scene.Init();
  scene.computeTransformedBoxes();
  double radi;
  Point centreEscena;
  scene.CalculaEsfera(radi, centreEscena);
  // dimensions escena i camera inicial
  cam.computeDefaultCamera(radi, centreEscena);
 // Posem boira blava per simular l'efecte "sota l'aigua"
  glFogi(GL_FOG_MODE, GL_EXP2);
  GLfloat fogColor[4] = {0.0, 0.3, 0.6, 1.0};
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_DENSITY, 0.02);
  glHint(GL_FOG_HINT, GL_NICEST);
  glClearColor(fogColor[0], fogColor[1], fogColor[2], fogColor[3]);
}

// paintGL() - callback cridat cada cop que cal refrescar la finestra. 
void GLWidget::paintGL( void ) { 
  // Esborrem els buffers
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  cam.setProjection(w, h);
  cam.setModelview();

  // dibuixar eixos aplicacio
  glBegin(GL_LINES);
  glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(20,0,0); // X
  glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,20,0); // Y
  glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,20); // Z
  glEnd();

  // pintem l'escena: terra, objectes i el que calgui
  scene.Render();
}

// resizeGL() - Cridat quan es canvia el tamany del viewport.
void GLWidget::resizeGL (int width, int height) {
  glViewport (0, 0, width, height);
  w = width;
  h = height;
}

// help() - Surt per la terminal des de la que hem 
// engegat el programa. En la versio amn interficie 
// hauria de crear una nova finestra amb la informacio...
void GLWidget::help( void ){
  cout<<"Tecles definides: \n";
  cout<<"f         Pinta en filferros\n";
  cout<<"s         Pinta amb omplert de polígons\n";
  cout<<"h,H,?     Imprimir aquesta ajuda\n";
  // Completar amb altres tecles que definiu...
  //
}

/*--------------------
 *
 *  teclat()
 *
 *  callback per quan hom prem una tecla.
 *
 */
void GLWidget::keyPressEvent(QKeyEvent *e)
{
  switch( e->key() ) {
  case Qt::Key_F: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    updateGL();
    break;
  case Qt::Key_S: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    updateGL();
    break;
  case Qt::Key_G: usingFog = not usingFog;
    if (usingFog) glEnable(GL_FOG);
    else glDisable(GL_FOG);
    updateGL();
    break;
  case  'h'  : case  'H'  : case  '?'  :  help();
    break;
  case Qt::Key_Up:
    scene.moveDolphinForward();
    updateGL();
    break;
  case Qt::Key_Left:
      scene.rotateDolphinLeft();
      updateGL();
      break;
  case Qt::Key_Right:
      scene.rotateDolphinRight();
      updateGL();
      break;
  default: e->ignore(); // el propaguem cap al pare...
  }
}

/*--------------------
 * mousePressEvent()
 */
void GLWidget::mousePressEvent( QMouseEvent *e){
  xClick = e->x();
  yClick = e->y();

  if (e->button()&Qt::LeftButton &&
      ! (e->modifiers()&(Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
    {
      DoingInteractive = ROTATE;
    }
  else if (e->button()&Qt::LeftButton &&  e->modifiers() &Qt::ShiftModifier)
    {
      DoingInteractive = ZOOM;
    }
}

/*--------------------
 *
 * mouseReleaseEvent()
 *
 * Callback Qt cridat quan es deixa anar el botó del
 * ratolí.
 *
 */
void GLWidget::mouseReleaseEvent( QMouseEvent *) {
  DoingInteractive = NONE;
}

/*--------------------
 *
 * mouseMoveEvent()
 *
 * Callback Qt cridat quan s'arrosega el ratoli amb
 * algun boto premut.
 *
 */
void GLWidget::mouseMoveEvent(QMouseEvent *e) {
  // Aquí cal que es calculi i s'apliqui la rotació o el zoom
  // com s'escaigui...
  int newXClick, newYClick;
  newXClick = e->x();
  newYClick = e->y();
  Point centreEscena;
  double radi;
  scene.CalculaEsfera(radi, centreEscena);
  if (DoingInteractive==ROTATE) {
    // Rotar la camera
    this->rotateCam(xClick - newXClick, newYClick - yClick);
  }

  if (DoingInteractive==ZOOM) {
    // Fer zoom
    cam.updateAnglecam(newYClick - yClick);
  }

  this->updateClickCoordinades(newXClick, newYClick);

  updateGL();

}

void GLWidget::updateClickCoordinades(float newXClick, float newYClick) {

    this->xClick = newXClick;
    this->yClick = newYClick;
}

void GLWidget::rotateCam(float xIncrement, float yIncrement) {

  float originalAngleX = cam.getAngleX();
  float originalAngleY = cam.getAngleY();
  cam.setAngleX(originalAngleX + yIncrement);
  cam.setAngleY(originalAngleY + xIncrement);
}

void GLWidget::resetCam() {	
  cam.resetCam();
  updateGL();
}

void GLWidget::loadModel() {

    Model loadedModel = loadModelFromFile();

    scene.AddModel(loadedModel);
    Point sceneCenter = getSceneCenter();
    float dolphin_y = getDiagonalLength()/20;
    Vector dolphinSize = Vector(1,dolphin_y, 1);
    ObjectInstance dolphin(4, sceneCenter, dolphinSize, 0, -90);
    scene.AddObject(dolphin);
    scene.Render();
}

float GLWidget::getDiagonalLength() {

    Box capsa = scene.capsa;
    Point maxb = capsa.maxb;
    Point minb = capsa.minb;
    Vector distance = maxb-minb;
    float diagonalLength = distance.length();

    return diagonalLength;
}

Point GLWidget::getSceneCenter() {

    Point sceneCenter;
    double radi;
    scene.CalculaEsfera(radi, sceneCenter);
    return sceneCenter;
}

Model GLWidget::loadModelFromFile() {

    QString fileName = QFileDialog::getOpenFileName();
    Model loadedModel(fileName.toStdString());
    loadedModel.readObj(fileName.toAscii().data(), scene.matlib);
    loadedModel.updateBoundingBox();

    return loadedModel;
}

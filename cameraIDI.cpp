#include "cameraIDI.h"
#include <QtOpenGL/qgl.h>
#include <cmath>

void cameraIDI::computeDefaultCamera(double radi, Point VRP)
{

  this->VRP = VRP;/*VRP = Point(20., 3., 20.)*/;
  this->dist = radi*2;
  //  dist = 50.;
  _anterior = 3.;
  _posterior = 150.;
  anglecam = 60;

  // inicialitzem els angles per a veure-ho des d'un cert punt de vista   
  angleX = 45;
  angleY = 45;
  angleZ = 0;
  zoom=0;
}

void cameraIDI::setModelview() 
{
  glMatrixMode(GL_MODELVIEW); //Modifiquem matriu ModelView (Camera)      
  glLoadIdentity(); //Coloquem camera a l'origent (punt per defecte)
  trasllada(0, 0, -(this->dist));
  rota(angleZ, 0, 0, 1);
  rota(angleX, 1, 0, 0);
  rota(-angleY, 0, 1, 0);
  trasllada(-VRP.x, -VRP.y, -VRP.z);
}

void cameraIDI::setProjection(int width, int height) 
{
  float aspect=float(width)/float(height); //relació d'aspecte = amplada / alçada   
  float newAnglecam;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(aspect < 1)
      newAnglecam = computeNewAngleCam(aspect);
  else newAnglecam = anglecam;
  gluPerspective(newAnglecam, aspect, _anterior, _posterior);
}

float cameraIDI::computeNewAngleCam(float aspect) {

    float anglecamTangent = tan(convertToRadians(anglecam));
    return convertToDegrees(atan(anglecamTangent)/aspect);
}

float cameraIDI::convertToRadians(float angle) {

    return angle/360*M_PI;
}

float cameraIDI::convertToDegrees(float angle) {

    return angle*360/M_PI;
}

void cameraIDI::resetCam() 
{
  angleX = 45;
  angleY = 45;
  angleZ = 0;
  anglecam=60;
}

void cameraIDI::iniciTGModelat()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
}

void cameraIDI::identitat()
{
  glLoadIdentity();
}

void cameraIDI::fiTGModelat()
{
  glPopMatrix();
}

void cameraIDI::trasllada(float tx, float ty, float tz)
{
  glTranslatef(tx, ty, tz);
}

void cameraIDI::escala(float sx, float sy, float sz)
{
  glScalef(sx, sy, sz);
}

void cameraIDI::rota(float graus, float rx, float ry, float rz)
{
  glRotatef(graus, rx, ry, rz);
}

void cameraIDI::setAngleX(float angleX)
{
    this->angleX = angleX;
}

void cameraIDI::setAngleY(float angleY)
{
    this->angleY = angleY;
}

void cameraIDI::updateAnglecam(float anglecam)
{
    this->anglecam += anglecam;
    this->normalizeAnglecam();
}

void cameraIDI::normalizeAnglecam()
{
    if (this->anglecam >= 180)
        this->anglecam = 179;

    if (this->anglecam <= 0)
        this->anglecam = 1;
}

float cameraIDI::getAngleX()
{
    return this->angleX;
}

float cameraIDI::getAngleY()
{
    return this->angleY;
}

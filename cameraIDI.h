#ifndef _CAMERAIDI_H_
#define _CAMERAIDI_H_

#include "point.h"

class cameraIDI{
  float anglecam;
  double _anterior, _posterior; 
  Point VRP;
  double dist; 
  float angleX, angleY, angleZ;
  float zoom;

 public:  
  void iniciTGModelat();
  void identitat();
  void fiTGModelat();
  void trasllada(float tx, float ty, float tz);
  void escala(float sx, float sy, float sz);
  void rota(float graus, float rx, float ry, float rz);
  void resetCam();
  void computeDefaultCamera(double radi, Point VRP);
  void setModelview();
  void setProjection(int width, int height);
  double anterior() {return _anterior;}
  double posterior() {return _posterior;}
  float getAngleX();
  void setAngleX(float angleX);
  float getAngleY();
  void setAngleY(float angleY);
  void updateAnglecam(float zoom);
private:
  float convertToRadians(float angle);
  float convertToDegrees(float angle);
  float computeNewAngleCam(float aspect);
  void normalizeAnglecam();
};
#endif

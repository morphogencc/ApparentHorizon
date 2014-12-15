#pragma once

#include "ofMain.h"
#include "Shape.h"
#include "horizonRect.h"
#include "horizonTriangle.h"
#include "horizonRightTriangle.h"
#include "horizonCube.h"
#include "pingPong.h"
#include <deque>

class Perspective {
 public:
  Perspective();
  ~Perspective();
  void beginProjection();
  void endProjection();
  void addRect();
  void addTriangle();
  void addTriangle(int type);
  void addRightTriangle();
  void addRightTriangle(int type);
  void addCube();
  void update(double time);
  void draw();
  void drawGrid();
  void translateCamera(float newZ);
 private:
  float width, height;
  int mGridZ;
  int mGridXY;
  float mHorizonDistance;
  double mOpenTime;
  double mElapsedTime;
  double fNear, fFar, fFov;  
  ofVec3f mPosition;
  ofVec3f mCameraDirection;
   deque<Shape*> mShapes;
};

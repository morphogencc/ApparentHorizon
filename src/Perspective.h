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
  void beginProjection(float rotationAngle);
  void endProjection();
  void addRect();
  void addRect(int type, int hue);
  void addTriangle();
  void addTriangle(int type);
  void addRightTriangle();
  void addRightTriangle(int type);
  void addCube();
  void update(double time);
  void draw();
  void reset();
  void drawShapes();
  void drawGrid();
  void setShapeSpeed(float newSpeed);
  void setShapeRotationSpeed(float newSpeed);
  void translateCamera(float newZ);
  void setCameraSpeed(float velocity);
  void setCameraDirectionX(float direction_x);
  void setCameraDirectionY(float direction_y);  
 private:
  float width, height;
  ofFbo mLeftFbo;
  ofFbo mRightFbo;
  int mGridZ;
  int mGridXY;
  float mHorizonDistance;
  double mOpenTime;
  double mElapsedTime;
  double fNear, fFar, fFov;  
  ofVec3f mPosition;
  float mZoomSpeed;
  ofVec3f mCameraDirection;
   deque<Shape*> mShapes;
};

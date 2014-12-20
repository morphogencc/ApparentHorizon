#pragma once
#include "ofMain.h"

class Shape {
 public:
  Shape(ofVec3f position, float horizon);
  ~Shape();
  void update(double time);
  virtual void draw();
  double getElapsedTime();
  ofVec3f getPosition();
  void setColor(float hue, float saturation, float brightness);
  void setHue(float hue);
  void setSaturation(float sat);
  void setRotation(float rotation);
 protected:
  float mInitialPositionZ;
  float mDepth;
  float mWidth;
  float mHeight;
  ofColor mInitialColor;
  ofColor mColor;
  ofVec3f mPosition;
  float mHorizon;
  float mRotation;
  double mOpenTime;
  double mElapsedTime;  
  float mTimeToHorizon;
};

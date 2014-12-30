#pragma once
#include "ofMain.h"

class Shape {
 public:
  Shape(ofVec3f position, float horizon);
  ~Shape();
  void update(double time, float cameraPosition);
  virtual void draw(float alpha);
  double getElapsedTime();
  ofVec3f getPosition();
  bool isAlive();
  void setSpeed(float newSpeed);
  void setRotationSpeed(float newSpeed);
  void setHue(int hue);
  void setSaturation(float sat);
  void setRotation(float rotation);
 protected:
  float mDistanceFromCamera;
  float mInitialPositionZ;
  float mDepth;
  float mWidth;
  float mHeight;
  float mSpeed;
  float mRotationSpeed;
  float mHue;
  float mSaturation;
  float mBrightness;
  float mAlpha;
  int mLowerHueThreshold;
  int mUpperHueThreshold;
  ofVec3f mPosition;
  float mHorizon;
  float mRotation;
  double mOpenTime;
  double mElapsedTime;  
  float mTimeToHorizon;
};

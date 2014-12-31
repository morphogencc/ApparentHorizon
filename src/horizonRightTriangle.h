#pragma once
#include "ofMain.h"
#include "Shape.h"

class horizonRightTriangle : public Shape {
 public:
  horizonRightTriangle(ofVec3f position, float horizon);
  horizonRightTriangle(ofVec3f position, float horizon, int type);
  ~horizonRightTriangle();
  void draw(float alpha);
 private:
  int mTriangleType;
};

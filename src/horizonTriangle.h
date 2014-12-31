#pragma once
#include "ofMain.h"
#include "Shape.h"

class horizonTriangle : public Shape {
 public:
  horizonTriangle(ofVec3f position, float horizon);
  horizonTriangle(ofVec3f position, float horizon, int type);
  ~horizonTriangle();
  void draw(float alpha);
 private:
  int mTriangleType;
};

#pragma once
#include "ofMain.h"
#include "Shape.h"

class horizonCube : public Shape {
 public:
  horizonCube(ofVec3f position, ofVec3f dimensions, float horizon);
  ~horizonCube();
  void draw();
 private:
};

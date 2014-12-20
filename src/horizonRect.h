#pragma once
#include "ofMain.h"
#include "Shape.h"

class horizonRect : public Shape {
 public:
  horizonRect(ofVec3f position, float horizon);
  horizonRect(ofVec3f position, float horizon, int type);
  ~horizonRect();
  void draw();
 private:
};

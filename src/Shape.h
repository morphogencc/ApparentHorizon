#include "ofMain.h"

class Shape {
 public:
  Shape(ofVec3f position);
  ~Shape();
  void update(double time);
  void draw();
  double getElapsedTime();
 private:
  float mWidth, mHeight;
  ofColor mColor;
  ofVec3f mPosition;
  double mOpenTime;
  double mElapsedTime;  
};

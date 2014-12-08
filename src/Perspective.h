#include "ofMain.h"
#include "Shape.h"
#include <deque>

class Perspective {
 public:
  Perspective();
  ~Perspective();
  void beginProjection();
  void endProjection();
  void addShape();
  void update(double time);
  void draw();
  void drawGrid();
 private:
  double mOpenTime;
  double mElapsedTime;
  double headX, headY, headZ;  
  double fNear, fFar, fFov;  
  ofVec3f objPos[10];
  ofColor colors[10][4];
  deque<Shape*> mShapes;
};

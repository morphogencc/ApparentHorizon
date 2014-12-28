#include "horizonRect.h"

horizonRect::horizonRect(ofVec3f position, float horizon) : Shape(position, horizon) {

}

horizonRect::horizonRect(ofVec3f position, float horizon, int type) : Shape(position, horizon) {
  mWidth = 0.33;
  mHeight = 0.33;
  switch(type) {
  case 0:
    mWidth = 1.0;
    mHeight = 1.0;
    break;
  case 1:
    mPosition[0] = -0.67;
    mPosition[1] = 0.67;
    break;
  case 2:
    mPosition[0] = 0.0;
    mPosition[1] = 0.67;
    break;
  case 3:
    mPosition[0] = 0.67;
    mPosition[1] = 0.67;
    break;
  case 4:
    mPosition[0] = -0.67;
    mPosition[1] = 0;
    break;
  case 5:
    mPosition[0] = 0;
    mPosition[1] = 0;
    break;
  case 6:
    mPosition[0] = 0.67;
    mPosition[1] = 0;
    break;
  case 7:
    mPosition[0] = -0.67;
    mPosition[1] = -0.67;
    break;
  case 8:
    mPosition[0] = 0;
    mPosition[1] = -0.67;
    break;
  case 9:
    mPosition[0] = 0.67;
    mPosition[1] = -0.67;
    break;
  }
}

horizonRect::~horizonRect() {
  
}

void horizonRect::draw() {
  ofPushMatrix();
  ofPushStyle();
  ofRotateZ(mRotation);
  ofNoFill();
  ofSetColor(mColor);
  ofSetLineWidth(ofMap(mDistanceFromCamera, 0.0, mHorizon, 3.0, 0.0));
  ofTranslate(mPosition[0], mPosition[1], mPosition[2]);  
  ofLine(-mWidth, -mHeight,  mWidth, -mHeight);  
  ofLine( mWidth, -mHeight,  mWidth,  mHeight);  
  ofLine( mWidth,  mHeight, -mWidth,  mHeight);  
  ofLine(-mWidth,  mHeight, -mWidth, -mHeight);
  ofPopStyle();
  ofPopMatrix();
}

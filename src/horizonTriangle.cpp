#include "horizonTriangle.h"

horizonTriangle::horizonTriangle(ofVec3f position, float horizon) : Shape(position, horizon) {
  mTriangleType = floor(ofRandom(0, 4));
}

horizonTriangle::horizonTriangle(ofVec3f position, float horizon, int type) : Shape(position, horizon) {
  mTriangleType = type;
}

horizonTriangle::~horizonTriangle() {
  
}

void horizonTriangle::draw() {
  ofPushMatrix();
  ofPushStyle();
  ofRotateZ(mRotation);
  ofNoFill();
  ofSetColor(mColor);
  ofSetLineWidth(ofMap(mPosition[2], 0, -mHorizon, 3.0, 0.0));
  ofTranslate(mPosition[0], mPosition[1], mPosition[2]);  
  switch(mTriangleType) {
  case 0: //bottom
    ofLine(0, 0, mWidth, -mHeight);
    ofLine(mWidth, -mHeight, -mWidth, -mHeight);
    ofLine(-mWidth, -mHeight, 0, 0);
    break;
  case 1: //right
    ofLine(0, 0, mWidth, mHeight);
    ofLine(mWidth, mHeight, mWidth, -mHeight);
    ofLine(mWidth, -mHeight, 0, 0);
    break;
  case 2: //top
    ofLine(0, 0, mWidth, mHeight);
    ofLine(mWidth, mHeight, -mWidth, mHeight);
    ofLine(-mWidth, mHeight, 0, 0);
    break;
  case 3: //left
    ofLine(0, 0, -mWidth, mHeight);
    ofLine(-mWidth, mHeight, -mWidth, -mHeight);
    ofLine(-mWidth, -mHeight, 0, 0);
    break;
  }
  ofPopStyle();
  ofPopMatrix();
}

#include "horizonRightTriangle.h"

horizonRightTriangle::horizonRightTriangle(ofVec3f position, float horizon) : Shape(position, horizon) {
  mTriangleType = floor(ofRandom(0, 4));
}

horizonRightTriangle::horizonRightTriangle(ofVec3f position, float horizon, int type) : Shape(position, horizon) {
  mTriangleType = type;
}

horizonRightTriangle::~horizonRightTriangle() {
  
}

void horizonRightTriangle::draw(float alpha) {
  ofPushMatrix();
  ofPushStyle();
  ofRotateZ(mRotation);
  ofNoFill();
  ofSetColor(ofColor::fromHsb(mHue, mSaturation, mBrightness, mAlpha*alpha));
  ofSetLineWidth(ofMap(mElapsedTime, 0, mTimeToHorizon, 3.0, 0.0));
  ofTranslate(mPosition[0], mPosition[1], mPosition[2]);  
  switch(mTriangleType) {
  case 0: //bottom left
    ofLine(-mWidth, -mHeight, mWidth, -mHeight);
    ofLine(mWidth, -mHeight, -mWidth, mHeight);
    ofLine(-mWidth, mHeight, -mWidth, -mHeight);
    break;
  case 1: //top left
    ofLine(-mWidth, -mHeight, mWidth, mHeight);
    ofLine(mWidth, mHeight, -mWidth, mHeight);
    ofLine(-mWidth, mHeight, -mWidth, -mHeight);
    break;
  case 2: //top right
    ofLine(-mWidth, mHeight, mWidth, mHeight);
    ofLine(mWidth, mHeight, mWidth, -mHeight);
    ofLine(mWidth, -mHeight, -mWidth, mHeight);
    break;
  case 3: //bottom right
    ofLine(mWidth, mHeight, mWidth, -mHeight);
    ofLine(mWidth, -mHeight, -mWidth, -mHeight);
    ofLine(-mWidth, -mHeight, mWidth, mHeight);
    break;
  }
  ofPopStyle();
  ofPopMatrix();
}

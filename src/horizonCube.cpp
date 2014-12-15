#include "horizonCube.h"

horizonCube::horizonCube(ofVec3f position, ofVec3f dimensions, float horizon) : Shape(position, horizon) {
  mWidth = dimensions[0];
  mHeight = dimensions[1];
  mDepth = dimensions[2];
}

horizonCube::~horizonCube() {
  
}

void horizonCube::draw() {
  ofPushMatrix();
  ofPushStyle();
  ofRotateZ(mRotation);
  ofNoFill();
  ofSetColor(mColor);
  ofSetLineWidth(ofMap(mPosition[2], 0, -mHorizon, 3.0, 0.0));
  ofTranslate(mPosition[0], mPosition[1], mPosition[2]);  
  ofScale(mWidth, mHeight, mDepth);
  ofBoxPrimitive();
  ofPopStyle();
  ofPopMatrix();
}

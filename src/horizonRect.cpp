#include "horizonRect.h"

horizonRect::horizonRect(ofVec3f position, float horizon) : Shape(position, horizon) {

}

horizonRect::~horizonRect() {
  
}

void horizonRect::draw() {
  ofPushMatrix();
  ofPushStyle();
  ofRotateZ(mRotation);
  ofNoFill();
  ofSetColor(mColor);
  ofSetLineWidth(ofMap(mPosition[2], 0, -mHorizon, 3.0, 0.0));
  ofTranslate(mPosition[0], mPosition[1], mPosition[2]);  
  ofLine(-mWidth, -mHeight,  mWidth, -mHeight);  
  ofLine( mWidth, -mHeight,  mWidth,  mHeight);  
  ofLine( mWidth,  mHeight, -mWidth,  mHeight);  
  ofLine(-mWidth,  mHeight, -mWidth, -mHeight);
  ofPopStyle();
  ofPopMatrix();
}

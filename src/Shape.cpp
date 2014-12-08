#include "Shape.h"

Shape::Shape(ofVec3f position) {
  mOpenTime = ofGetElapsedTimef();
  mColor = ofColor(160, 255, 160, 80);
  mPosition = position;
  mWidth = 2.0;
  mHeight = 2.0;
}

Shape::~Shape() {
}

void Shape::update(double time) {
  mElapsedTime = ofGetElapsedTimef() - mOpenTime;
  mPosition[2] = ofMap(mElapsedTime, 0.0, 1.0, 0.0, -10.0);
}

void Shape::draw() {
  ofPushMatrix();
  ofColor(mColor);
  ofSetLineWidth(10);
  ofTranslate(mPosition[0], mPosition[1], mPosition[2]);  
  ofLine(-mWidth/2.0, -mHeight/2.0,  mWidth/2.0, -mHeight/2.0);  
  ofLine( mWidth/2.0, -mHeight/2.0,  mWidth/2.0,  mHeight/2.0);  
  ofLine( mWidth/2.0,  mHeight/2.0, -mWidth/2.0,  mHeight/2.0);  
  ofLine(-mWidth/2.0,  mHeight/2.0, -mWidth/2.0, -mHeight/2.0);
  ofPopMatrix();
}

double Shape::getElapsedTime() {
  return mElapsedTime;
}

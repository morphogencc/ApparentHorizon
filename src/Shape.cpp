#include "Shape.h"

Shape::Shape(ofVec3f position, float horizon) {
  mOpenTime = ofGetElapsedTimef();
  mElapsedTime = 0.0;
  mColor.setHsb(128, 255, 255, 255);
  mInitialColor.setHsb(128, 255, 255, 255);
  mRotation = 0;
  mPosition = position;
  mInitialPositionZ = mPosition[2];
  mHorizon = horizon;
  mDepth = 1.0;
  mWidth = 1.0;
  mHeight = 1.0;
  mTimeToHorizon = 10.0;
  mSpeed = -0.25;
  mRotationSpeed = 0.0;
  mAlpha = 255;
}

Shape::~Shape() {

}

void Shape::update(double time, float cameraPosition) {
  mDistanceFromCamera = abs(cameraPosition + mPosition[2]);
  mElapsedTime = ofGetElapsedTimef() - mOpenTime;
  mPosition[2] += mSpeed;
  mColor.setBrightness(ofMap(mDistanceFromCamera, 0.0, mHorizon, mInitialColor[3], 10.0));
  mRotation += mRotationSpeed;
}

void Shape::draw() {
  ofPushMatrix();
  ofPushStyle();
  ofEnableAlphaBlending();
  ofRotateZ(mRotation);
  ofSetColor(mColor);
  ofSetLineWidth(ofMap(mDistanceFromCamera, 0.0, mHorizon, 3.0, 0.0));
  ofTranslate(mPosition[0], mPosition[1], mPosition[2]);
  ofLine(-mWidth, -mHeight,  mWidth, -mHeight);  
  ofLine( mWidth, -mHeight,  mWidth,  mHeight);  
  ofLine( mWidth,  mHeight, -mWidth,  mHeight);  
  ofLine(-mWidth,  mHeight, -mWidth, -mHeight);
  ofDisableAlphaBlending();
  ofPopStyle();
  ofPopMatrix();
}

bool Shape::isAlive() {
  if(mElapsedTime > mTimeToHorizon) {
    return true;
  }
  return false;
}

void Shape::setSpeed(float newSpeed) {
  mSpeed = newSpeed;
}

void Shape::setRotationSpeed(float newSpeed) {
  mRotationSpeed = newSpeed;
}

double Shape::getElapsedTime() {
  return mElapsedTime;
}

ofVec3f Shape::getPosition() {
  return mPosition;
}

void Shape::setColor(float hue, float saturation, float brightness) {
  mColor.setHsb(hue, saturation, brightness);
}

void Shape::setHue(float hue) {
  mColor.setHue(hue);
}

void Shape::setSaturation(float sat) {
  mColor.setSaturation(sat);
}

void Shape::setRotation(float rotation) {
  mRotation = rotation;
}

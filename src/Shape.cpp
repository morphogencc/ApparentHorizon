#include "Shape.h"

Shape::Shape(ofVec3f position, float horizon) {
  mOpenTime = ofGetElapsedTimef();
  mElapsedTime = 0.0;
  mRotation = 0;
  mPosition = position;
  mInitialPositionZ = mPosition[2];
  mHorizon = horizon;
  mDepth = 1.0;
  mWidth = 1.0;
  mHeight = 1.0;
  mTimeToHorizon = 15.0;
  mSpeed = -0.25;
  mRotationSpeed = 0.0;
  mHue = 0;
  Shape::setHue(ofRandom(3));
  mSaturation = 255;
  mBrightness = 255;
  mAlpha = 255;
}

Shape::~Shape() {

}

void Shape::update(double time, float cameraPosition) {
  mDistanceFromCamera = abs(cameraPosition + mPosition[2]);
  mElapsedTime = ofGetElapsedTimef() - mOpenTime;
  mPosition[2] += mSpeed;
  mAlpha = ofMap(mDistanceFromCamera, 0.0, mHorizon, 255.0, 10.0);
  mRotation += mRotationSpeed;
}

void Shape::draw(float alpha) {
  ofPushMatrix();
  ofPushStyle();
  ofEnableAlphaBlending();
  ofRotateZ(mRotation);
  //set buffer alpha
  ofSetColor(ofColor::fromHsb(mHue, mSaturation, mBrightness, mAlpha*alpha));
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

void Shape::setHue(int hue) {
  hue = hue % 3;
  switch(hue) {
  case 0:
    mHue = 173.541;
    break;
  case 1:
    mHue = 204.415;
    break;
  case 2:
    mHue = 141.667;
    break;
  }

}

void Shape::setSaturation(float sat) {
  mSaturation = sat;
}

void Shape::setRotation(float rotation) {
  mRotation = rotation;
}

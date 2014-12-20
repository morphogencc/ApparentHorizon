#include "Perspective.h"

Perspective::Perspective() {
  mOpenTime = 0;
  mElapsedTime = 0;
  mGridZ = 10;
  mGridXY = 1;

  mHorizonDistance = 100.0f;
  mCameraDirection = ofVec3f(0, 0, -2.0);
  mPosition = ofVec3f(0, 0, -2.0);
  width = ofGetWidth();
  height = ofGetHeight();
}

void Perspective::beginProjection() {   
  mFbo.begin();
  glMatrixMode(GL_PROJECTION);  
  glPushMatrix();  

  glMatrixMode(GL_MODELVIEW);  
  glPushMatrix(); 

  fNear = 0.5f;  
  fFov = 0.5;
  //fFov = tan(30 * PI / 360);  
  //fFov = tan(90 * PI / 360.0 );
             
  float ratio = ofGetWidth() / ofGetHeight();  

  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();  
          
  glFrustum(fNear*(-fFov * ratio + mCameraDirection[0]),  
	    fNear*(fFov * ratio + mCameraDirection[0]),  
	    fNear*(-fFov + mCameraDirection[1]),  
	    fNear*(fFov + mCameraDirection[1]),  
	    fNear, mHorizonDistance);  
          
  glMatrixMode(GL_MODELVIEW);  
  glLoadIdentity();  

  gluLookAt(mCameraDirection[0]*mCameraDirection[2], 
	    mCameraDirection[1]*mCameraDirection[2], 
	    0, 
	    mCameraDirection[0]*mCameraDirection[2], 
	    mCameraDirection[1]*mCameraDirection[2], 
	    -1, 
	    0, 
	    1, 
	    0);

  glTranslatef(mPosition[0], mPosition[1], mPosition[2]);
}  

void Perspective::endProjection() {  
  glMatrixMode(GL_PROJECTION);  
  glPopMatrix();  
  glMatrixMode(GL_MODELVIEW);  
  glPopMatrix(); 
}

void Perspective::addRect() {
  mShapes.push_back(new horizonRect(ofVec3f(0, 0, 0), mHorizonDistance));
}

void Perspective::addRect(int type, int hue) {
  horizonRect* r = new horizonRect(ofVec3f(0, 0, 0), mHorizonDistance, type);
  r->setHue(ofMap(hue, 0, 127, 64, 255));
  mShapes.push_back(r);
}

void Perspective::addTriangle() {
  mShapes.push_back(new horizonTriangle(ofVec3f(0, 0, 0), mHorizonDistance));
}

void Perspective::addTriangle(int type) {
  mShapes.push_back(new horizonTriangle(ofVec3f(0, 0, 0), mHorizonDistance, type));
}

void Perspective::addRightTriangle() {
  mShapes.push_back(new horizonRightTriangle(ofVec3f(0, 0, 0), mHorizonDistance));
}

void Perspective::addRightTriangle(int type) {
  mShapes.push_back(new horizonRightTriangle(ofVec3f(0, 0, 0), mHorizonDistance, type));
}

void Perspective::addCube() {
  mShapes.push_back(new horizonCube(ofVec3f(0, 0, 0), ofVec3f(0.25, 0.25, 0.25), mHorizonDistance));
}

void Perspective::update(double time) {
  for(deque<Shape*>::iterator it = mShapes.begin(); it != mShapes.end(); ) {
    if((*it)->getPosition()[2] > mHorizonDistance) {
      it = mShapes.erase(it);
    }
    else {
      (*it)->update(time);
      //(*it)->setRotation(ofMap((*it)->getElapsedTime(), 0, 1, 0, 180));
      ++it;
    }
  }
  mFbo.end();
}

void Perspective::draw(float x, float y) {
  mFbo.draw(x, y);
}

void Perspective::drawShapes() {
  for(deque<Shape*>::iterator it = mShapes.begin(); it != mShapes.end(); ++it) {
    (*it)->draw();
  }
}

void Perspective::drawGrid() {  
  float stepSize = mHorizonDistance / (mGridZ);
  float frameW = 1.0;  
  float frameH = 1.0;

  ofPushStyle();  
  for (int i = 0; i < mGridZ; i++) {  
    ofSetLineWidth(1);
    ofSetColor(255,255,255,80);  
    ofPushMatrix();  
    ofTranslate(.0f, .0f, -(i*stepSize));  
    ofLine(-frameW, -frameH,  frameW, -frameH);  
    ofLine( frameW, -frameH,  frameW,  frameH);  
    ofLine( frameW,  frameH, -frameW,  frameH);  
    ofLine(-frameW,  frameH, -frameW, -frameH);
    ofPopMatrix();
  }
  for (int i = 0; i < mGridXY; i++) {
    double _x = i*frameW/(double)mGridXY - 1.0;
    double _y = i*frameH/(double)mGridXY - 1.0;
    ofLine(-_x, -frameH, 0.0, -_x, -frameH, -mHorizonDistance);
    ofLine( _x,  frameH, 0.0,  _x,  frameH, -mHorizonDistance);
    ofLine( frameW, -_y, 0.0,  frameW, -_y, -mHorizonDistance);
    ofLine(-frameW,  _y, 0.0, -frameW,  _y, -mHorizonDistance);
  }
  ofPopStyle();
}

void Perspective::translateCamera(float newZ) {
  mPosition[2] = newZ;
}

void Perspective::setCameraDirectionX(float direction_x) {
  mCameraDirection[0] = direction_x;
 }

void Perspective::setCameraDirectionY(float direction_y) {
  mCameraDirection[1] = direction_y;
}

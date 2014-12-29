#include "Perspective.h"

Perspective::Perspective() {
  mOpenTime = 0;
  mElapsedTime = 0;
  mGridZ = 10;
  mGridXY = 1;

  mHorizonDistance = 100.0f;
  mCameraDirection = ofVec3f(0, 0, -1.0);
  mPosition = ofVec3f(0, 0, -1.0);
  mZoomSpeed = 0.0;
  width = ofGetWidth();
  height = ofGetHeight();
  mLeftFbo.allocate(width / 2.0, height);
  mRightFbo.allocate(width / 2.0, height);
}

void Perspective::beginProjection(float rotationAngle) {   
  glMatrixMode(GL_PROJECTION);  
  glPushMatrix();  

  glMatrixMode(GL_MODELVIEW);  
  glPushMatrix(); 

  fNear = 0.5f;  
  fFov = 0.5;
  //fFov = tan(30 * PI / 360);  
  //fFov = tan(90 * PI / 360.0 );
             
  float ratio = 0.5 * ofGetWidth() / ofGetHeight();  

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

  glRotatef(rotationAngle, 0, 1, 0);
}  

void Perspective::endProjection() {  
  glMatrixMode(GL_PROJECTION);  
  glPopMatrix();  
  glMatrixMode(GL_MODELVIEW);  
  glPopMatrix(); 
}

void Perspective::addRect() {
  mShapes.push_back(new horizonRect(ofVec3f(0, 0, -mPosition[2]), mHorizonDistance));
}

void Perspective::addRect(int type, int hue) {
  horizonRect* r = new horizonRect(ofVec3f(0, 0, -mPosition[2]), mHorizonDistance, type);
  r->setHue(ofMap(hue, 0, 127, 64, 255));
  mShapes.push_back(r);
}

void Perspective::addTriangle() {
  mShapes.push_back(new horizonTriangle(ofVec3f(0, 0, -mPosition[2]), mHorizonDistance));
}

void Perspective::addTriangle(int type) {
  mShapes.push_back(new horizonTriangle(ofVec3f(0, 0, -mPosition[2]), mHorizonDistance, type));
}

void Perspective::addRightTriangle() {
  mShapes.push_back(new horizonRightTriangle(ofVec3f(0, 0, -mPosition[2]), mHorizonDistance));
}

void Perspective::addRightTriangle(int type) {
  mShapes.push_back(new horizonRightTriangle(ofVec3f(0, 0, -mPosition[2]), mHorizonDistance, type));
}

void Perspective::addCube() {
  mShapes.push_back(new horizonCube(ofVec3f(0, 0, -mPosition[2]), ofVec3f(0.25, 0.25, 0.25), mHorizonDistance));
}

void Perspective::update(double time) {
  for(deque<Shape*>::iterator it = mShapes.begin(); it != mShapes.end(); ) {
    if((*it)->isAlive()) {
      it = mShapes.erase(it);
    }
    else {
      (*it)->update(time, mPosition[2]);
      //(*it)->setRotation(ofMap((*it)->getElapsedTime(), 0, 1, 0, 180));
      ++it;
    }
  }
  mPosition[2] += mZoomSpeed;
}

void Perspective::draw() {
  mLeftFbo.begin();
  ofBackground(0);
  beginProjection(0);
  drawGrid();
  drawShapes();
  endProjection();
  mLeftFbo.end();

  mRightFbo.begin();
  ofBackground(0);
  beginProjection(90);
  drawGrid();
  drawShapes();
  endProjection();
  mRightFbo.end();

  mLeftFbo.draw(0, 0, width/2, height);
  mRightFbo.draw(width/2, 0, width/2, height);
}

void Perspective::reset() {
  mOpenTime = 0;
  mElapsedTime = 0;
  mGridZ = 10;
  mGridXY = 1;

  mHorizonDistance = 100.0f;
  mCameraDirection = ofVec3f(0, 0, -1.0);
  mPosition = ofVec3f(0, 0, -1.0);
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

  float cameraOffset = mPosition[2] - fmodf(mPosition[2],mGridZ) - mGridZ;
  
  ofPushStyle();  
  for (int i = 0; i < mGridZ; i++) {  
    ofSetLineWidth(1);
    ofSetColor(255,255,255,80);  
    ofPushMatrix();  
    ofTranslate(.0f, .0f, -(i*stepSize) - cameraOffset);
    ofLine(-frameW, -frameH,  frameW, -frameH);  
    ofLine( frameW, -frameH,  frameW,  frameH);  
    ofLine( frameW,  frameH, -frameW,  frameH);  
    ofLine(-frameW,  frameH, -frameW, -frameH);
    ofPopMatrix();
  }
  for (int i = 0; i < mGridXY; i++) {
    double _x = i*frameW/(double)mGridXY - 1.0;
    double _y = i*frameH/(double)mGridXY - 1.0;
    ofLine(-_x, -frameH, -cameraOffset, -_x, -frameH, -mHorizonDistance - cameraOffset);
    ofLine( _x,  frameH, -cameraOffset,  _x,  frameH, -mHorizonDistance - cameraOffset);
    ofLine( frameW, -_y, -cameraOffset,  frameW, -_y, -mHorizonDistance - cameraOffset);
    ofLine(-frameW,  _y,  -cameraOffset, -frameW,  _y, -mHorizonDistance - cameraOffset);
  }
  ofPopStyle();
}

void Perspective::setShapeSpeed(float newSpeed) {
  for(deque<Shape*>::iterator it = mShapes.begin(); it != mShapes.end(); ++it) {
    (*it)->setSpeed(newSpeed);
  }
}

void Perspective::setShapeRotationSpeed(float newSpeed) {
  for(deque<Shape*>::iterator it = mShapes.begin(); it != mShapes.end(); ++it) {
    (*it)->setRotationSpeed(newSpeed);
  }
}

void Perspective::translateCamera(float newZ) {
  mPosition[2] = newZ;
}

void Perspective::setCameraSpeed(float velocity) {
  mZoomSpeed = velocity;
}

void Perspective::setCameraDirectionX(float direction_x) {
  mCameraDirection[0] = direction_x;
 }

void Perspective::setCameraDirectionY(float direction_y) {
  mCameraDirection[1] = direction_y;
}

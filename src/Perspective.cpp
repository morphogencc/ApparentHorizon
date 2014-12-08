#include "Perspective.h"

Perspective::Perspective() {
  mOpenTime = 0;
  mElapsedTime = 0;
}

void Perspective::beginProjection() {   
  glMatrixMode(GL_PROJECTION);  
  glPushMatrix();  
  glMatrixMode(GL_MODELVIEW);  
  glPushMatrix(); 

  fNear = 0.5f;  
  fFar = 1000.0f;  
  fFov = tan(30 * PI / 360);  
  fFov = 0.5;
             
  float ratio = ofGetWidth() / ofGetHeight();  
    
  double _mx = (double)ofGetMouseX();
  double _my = (double)ofGetMouseY();
  double _w  = (double)ofGetWidth();
  double _h  = (double)ofGetHeight();

  headX = (_mx / _w) - 0.5;  
  headY = ((_h - _my) / _h) - 0.5;  
  headZ = -2.0;

  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();  
          
  glFrustum(fNear*(-fFov * ratio + headX),  
	    fNear*(fFov * ratio + headX),  
	    fNear*(-fFov + headY),  
	    fNear*(fFov + headY),  
	    fNear, fFar);  
          
  glMatrixMode(GL_MODELVIEW);  
  glLoadIdentity();  
  gluLookAt(headX*headZ, headY*headZ, 0, headX*headZ, headY*headZ, -1, 0, 1, 0);
  glTranslatef(0.0,0.0,headZ);
}  

void Perspective::endProjection() {  
  glMatrixMode(GL_PROJECTION);  
  glPopMatrix();  
  glMatrixMode(GL_MODELVIEW);  
  glPopMatrix(); 
}

void Perspective::addShape() {
  mShapes.push_back(new Shape(ofVec3f(0, 0, 0)));
  ofLog() << "New shape added!" << std::endl;
}

void Perspective::update(double time) {
  for(deque<Shape*>::iterator it = mShapes.begin(); it != mShapes.end(); ) {
    if((*it)->getElapsedTime() > 1.0) {
      it = mShapes.erase(it);
      ofLog() << "Shape deleted!";
    }
    else {
      (*it)->update(time);
      ofLog() << "Shape->update()";
      ++it;
    }
  }
}

void Perspective::draw() {
  for(deque<Shape*>::iterator it = mShapes.begin(); it != mShapes.end(); ++it) {
    (*it)->draw();
    ofLog() << "Shape->draw()";
  }
}

void Perspective::drawGrid() {  
  int nbOfSteps = 50;  
  float frameW = 1.0;  
  float frameH = 1.0;

  ofPushStyle();  
  for (int i = 0; i < nbOfSteps; i++) {  
    ofSetLineWidth(1);
    ofSetColor(255,255,255,80);  
    ofPushMatrix();  
    ofTranslate(.0f, .0f, i * -0.2f);  
    ofLine(-frameW, -frameH,  frameW, -frameH);  
    ofLine( frameW, -frameH,  frameW,  frameH);  
    ofLine( frameW,  frameH, -frameW,  frameH);  
    ofLine(-frameW,  frameH, -frameW, -frameH);
    ofPopMatrix();
    for (int i = 0; i < nbOfSteps*2; i++) {
      double _x = frameW/(double)nbOfSteps*(double)i-1.0;
      double _y = frameH/(double)nbOfSteps*(double)i-1.0;
      ofLine(-_x, -frameH, 0.0, -_x, -frameH, -10.0);
      ofLine( _x,  frameH, 0.0,  _x,  frameH, -10.0);
      ofLine( frameW, -_y, 0.0,  frameW, -_y, -10.0);
      ofLine(-frameW,  _y, 0.0, -frameW,  _y, -10.0);
    }
  }
  ofPopStyle();
}
  

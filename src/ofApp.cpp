
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  oscPort = 7000;
  ofLog() << "Listening for OSC messages on port " << oscPort << "\n";
  receiver.setup(oscPort);

  p = new Perspective(0, 90);
  q = new Perspective(-90, 0);
  r = new Perspective(-45, 45);
  pAlpha = 0;
  qAlpha = 0;
  rAlpha = 1;
  p->setAlpha(pAlpha);
  q->setAlpha(qAlpha);
  r->setAlpha(rAlpha);

  mFPS = true;
}

//--------------------------------------------------------------
void ofApp::update() {
  mElapsedTime = ofGetElapsedTimef();

  p->update(mElapsedTime);
  q->update(mElapsedTime);
  r->update(mElapsedTime);

  while(receiver.hasWaitingMessages()) {
    int pitch, velocity;
    ofxOscMessage m;
    
    receiver.getNextMessage(&m);

    if(m.getAddress() == "/create/rect") {
      if(m.getNumArgs() == 0) {
	p->addRect();
	q->addRect();
	r->addRect();
      }
      else {  
	if(m.getArgType(0) == OFXOSC_TYPE_INT32) { 
	  pitch = m.getArgAsInt32(0);
	  ofLog(OF_LOG_VERBOSE, "Pitch: %d", pitch);
	}
	if(m.getArgType(1) == OFXOSC_TYPE_INT32) {
	  velocity = m.getArgAsInt32(1);
	  ofLog(OF_LOG_VERBOSE, "Velocity: %d", pitch);
	}
	p->addRect(pitch, velocity);
	q->addRect(pitch, velocity);
	r->addRect(pitch, velocity);
      }
    }    
    else if(m.getAddress() == "/create/triangle") {
      if(m.getNumArgs() == 0) {
	p->addTriangle();
	q->addTriangle();
	r->addTriangle();
      }
      else {
	if(m.getArgType(0) == OFXOSC_TYPE_INT32) { 
	  pitch = m.getArgAsInt32(0);
	  ofLog(OF_LOG_VERBOSE, "Pitch: %d", pitch);
	}
	if(m.getArgType(1) == OFXOSC_TYPE_INT32) {
	  velocity = m.getArgAsInt32(1);
	  ofLog(OF_LOG_VERBOSE, "Velocity: %d", pitch);
	}
	p->addTriangle(pitch, velocity);
	q->addTriangle(pitch, velocity);
	r->addTriangle(pitch, velocity);
      }
    }
    else if(m.getAddress() == "/create/righttriangle") {
      if(m.getNumArgs() == 0) { 
	p->addRightTriangle();
	q->addRightTriangle();
	r->addRightTriangle();
      }
      else {
	if(m.getArgType(0) == OFXOSC_TYPE_INT32) { 
	  pitch = m.getArgAsInt32(0);
	  ofLog(OF_LOG_VERBOSE, "Pitch: %d", pitch);
	}
	if(m.getArgType(1) == OFXOSC_TYPE_INT32) {
	  velocity = m.getArgAsInt32(1);
	  ofLog(OF_LOG_VERBOSE, "Velocity: %d", pitch);
	}
	p->addRightTriangle(pitch, velocity);
	q->addRightTriangle(pitch, velocity);
	r->addRightTriangle(pitch, velocity);
      }
    }
    
    else if(m.getAddress() == "/camera/speed") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) { 
	float speed = ofMap(m.getArgAsInt32(0), 0, 127, -1.0, 1.0);
	if(m.getArgAsInt32(0) >= 63 && m.getArgAsInt32(0) <= 65) {
	  speed = 0;
	}
	p->setCameraSpeed(speed);
	q->setCameraSpeed(speed);
	r->setCameraSpeed(speed);
      }
    }
    else if(m.getAddress() == "/camera/heading/x") {
     //change x heading
      int heading = m.getArgAsInt32(0);
      p->setCameraDirectionX(ofMap(heading, 0, 127, -.75, .75));
      q->setCameraDirectionX(ofMap(heading, 0, 127, -.75, .75));
	  r->setCameraDirectionX(ofMap(heading, 0, 127, -.75, .75));
    }
    else if(m.getAddress() == "/camera/heading/y") {
      //change y heading
      int heading = m.getArgAsInt32(0);
      p->setCameraDirectionY(ofMap(heading, 0, 127, -.75, .75));
      q->setCameraDirectionY(ofMap(heading, 0, 127, -.75, .75));
	  r->setCameraDirectionY(ofMap(heading, 0, 127, -.75, .75));

    }
    else if(m.getAddress() == "/shape/speed") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float speed = ofMap(m.getArgAsInt32(0), 0, 127, -1.0, 1.0);
	if(m.getArgAsInt32(0) >= 63 && m.getArgAsInt32(0) <= 65) {
	  speed = 0;
	}
	p->setShapeSpeed(speed);
	q->setShapeSpeed(speed);
	r->setShapeSpeed(speed);
      }
    }
    else if(m.getAddress() == "/shape/rotationspeed") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float speed = ofMap(m.getArgAsInt32(0), 0, 127, -1.0, 1.0);
	if(m.getArgAsInt32(0) >= 63 && m.getArgAsInt32(0) <= 65) {
	  speed = 0;
	}
	p->setShapeRotationSpeed(speed);
	q->setShapeRotationSpeed(speed);
	r->setShapeRotationSpeed(speed);
      }
    }
    else if(m.getAddress() == "/color/saturation") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float saturation = ofMap(m.getArgAsInt32(0), 0, 127, 0, 255);
	p->setShapeSaturation(saturation);
	q->setShapeSaturation(saturation);
	r->setShapeSaturation(saturation);
      }
    }

    else if(m.getAddress() == "/perspective/p/alpha") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float alpha = ofMap(m.getArgAsInt32(0), 0, 127, 0, 1.0);
	if(alpha < 0.02) {
	  alpha = 0;
	}
	if(alpha > 0.98) {
	  alpha = 1.0;
	}
	p->setAlpha(alpha);
      }
    }

    else if(m.getAddress() == "/perspective/q/alpha") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float alpha = ofMap(m.getArgAsInt32(0), 0, 127, 0, 1.0);
	if(alpha < 0.02) {
	  alpha = 0;
	}
	if(alpha > 0.98) {
	  alpha = 1.0;
	}
	q->setAlpha(alpha);
      }
    }

	else if(m.getAddress() == "/perspective/r/alpha") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float alpha = ofMap(m.getArgAsInt32(0), 0, 127, 0, 1.0);
	if(alpha < 0.02) {
	  alpha = 0;
	}
	if(alpha > 0.98) {
	  alpha = 1.0;
	}
	r->setAlpha(alpha);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);

  ofEnableAlphaBlending();
  if(p->getAlpha() > 0) {
    p->draw();    
  }
  if(q->getAlpha() > 0) {
    q->draw();    
  }
  if(r->getAlpha() > 0) {
    r->draw();    
  }
  ofDisableAlphaBlending();
  
  if(mFPS) {
    string info = ofToString(ofGetFrameRate(), 2)+"\n";
    ofDrawBitmapStringHighlight(info, 30, 30);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == ' ') {
    p->reset();
    q->reset();
	r->reset();
  }
  if(key == 't') {
    p->addTriangle();
    q->addTriangle();
	r->addTriangle();

  }
  if(key == 'r') {
    p->addRect();
    q->addRect();
	r->addRect();
}
  if(key == 's') {
    ofSaveFrame();
  }
  if(key == 'f') {
    mFPS = !mFPS;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  double _mx = (double)ofGetMouseX();
  double _my = (double)ofGetMouseY();
  double _w  = (double)ofGetWidth();
  double _h  = (double)ofGetHeight();
  
  ofVec2f heading = ofVec2f((_mx / _w) - 0.5, 
			    ((_h - _my) / _h) - 0.5);

  //p->setCameraDirectionX(heading[0]);
  //p->setCameraDirectionY(heading[1]);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}

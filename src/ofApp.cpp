
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  oscPort = 7000;
  ofLog() << "Listening for OSC messages on port " << oscPort << "\n";
  receiver.setup(oscPort);

  p = new Perspective();
}

//--------------------------------------------------------------
void ofApp::update() {
  mElapsedTime = ofGetElapsedTimef();
  p->update(mElapsedTime);
  while(receiver.hasWaitingMessages()) {
    int pitch, velocity;
    ofxOscMessage m;
    
    receiver.getNextMessage(&m);
    ofLog(OF_LOG_VERBOSE, "OSC Message: %s", m);

    if(m.getAddress() == "/create/rect") {
      if(m.getNumArgs() == 0) {
	p->addRect();
      }
      else {  
	if(m.getArgType(0) == OFXOSC_TYPE_INT32) { 
	  pitch = m.getArgAsInt32(0);
	  ofLog(OF_LOG_VERBSE, "Pitch: %d", pitch);
	}
	if(m.getArgType(1) == OFXOSC_TYPE_INT32) {
	  velocity = m.getArgAsInt32(1);
	  ofLog(OF_LOG_VERBSE, "Velocity: %d", pitch);
	}
	p->addRect(pitch, velocity);
      }
    }    
    else if(m.getAddress() == "/create/triangle") {
      if(m.getNumArgs() == 0) {
	p->addTriangle();
      }
      else {
	if(m.getArgType(0) == OFXOSC_TYPE_INT32) { 
	  pitch = m.getArgAsInt32(0);
	  ofLog(OF_LOG_VERBSE, "Pitch: %d", pitch);
	}
	if(m.getArgType(1) == OFXOSC_TYPE_INT32) {
	  velocity = m.getArgAsInt32(1);
	  ofLog(OF_LOG_VERBSE, "Velocity: %d", pitch);
	}
	p->addTriangle(pitch, velocity);
      }
    }
    else if(m.getAddress() == "/create/righttriangle") {
      if(m.getNumArgs() == 0) { 
	p->addRightTriangle();
      }
      else {
	if(m.getArgType(0) == OFXOSC_TYPE_INT32) { 
	  pitch = m.getArgAsInt32(0);
	  ofLog(OF_LOG_VERBSE, "Pitch: %d", pitch);
	}
	if(m.getArgType(1) == OFXOSC_TYPE_INT32) {
	  velocity = m.getArgAsInt32(1);
	  ofLog(OF_LOG_VERBSE, "Velocity: %d", pitch);
	}
	p->addRightTriangle(pitch, velocity);
      }
    }
    
    else if(m.getAddress() == "/camera/speed") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) { 
	float speed = ofMap(m.getArgAsInt32(0), 0, 127, -1.0, 1.0);
	if(m.getArgAsInt32(0) >= 63 && m.getArgAsInt32(0) <= 65) {
	  speed = 0;
	}
	p->setCameraSpeed(speed);
      }
    }
    else if(m.getAddress() == "/camera/heading/x") {
     //change x heading
	  int heading = m.getArgAsInt32(0);
	  p->setCameraDirectionX(ofMap(heading, 0, 127, -0.5, 0.5));
	}
	else if(m.getAddress() == "/camera/heading/y") {
	  //change y heading
	  int heading = m.getArgAsInt32(0);
	  p->setCameraDirectionY(ofMap(heading, 0, 127, -0.5, 0.5));
	}
    else if(m.getAddress() == "/shape/speed") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float speed = ofMap(m.getArgAsInt32(0), 0, 127, -1.0, 1.0);
	if(m.getArgAsInt32(0) >= 63 && m.getArgAsInt32(0) <= 65) {
	  speed = 0;
	}
	p->setShapeSpeed(speed);
      }
    }
    else if(m.getAddress() == "/shape/rotationspeed") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float speed = ofMap(m.getArgAsInt32(0), 0, 127, -1.0, 1.0);
	if(m.getArgAsInt32(0) >= 63 && m.getArgAsInt32(0) <= 65) {
	  speed = 0;
	}
	p->setShapeRotationSpeed(speed);
      }
    }
    else if(m.getAddress() == "/color/saturation") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float saturation = ofMap(m.getArgAsInt32(0), 0, 127, 0, 255);
	p->setShapeSaturation(saturation);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  ofEnableAlphaBlending();
  p->draw();
  ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == ' ') {
    p->reset();
  }
  if(key == 't') {
    p->addTriangle();
  }
  if(key == 'r') {
    p->addRightTriangle();
  }
  if(key == 's') {
    ofSaveFrame();
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

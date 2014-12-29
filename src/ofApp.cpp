
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  oscPort = 7000;
  ofLog() << "Listening for OSC messages on port " << oscPort << "\n";
  receiver.setup(oscPort);

  p = new Perspective(0, 90);
  q = new Perspective(-90, 0);
  pAlpha = 0;
  qAlpha = 1;
  p->setAlpha(pAlpha);
  q->setAlpha(qAlpha);
}

//--------------------------------------------------------------
void ofApp::update() {
  mElapsedTime = ofGetElapsedTimef();

  p->update(mElapsedTime);
  q->update(mElapsedTime);

  while(receiver.hasWaitingMessages()) {
    int pitch, velocity;
    ofxOscMessage m;
    
    receiver.getNextMessage(&m);

    if(m.getAddress() == "/create/rect") {
      if(m.getNumArgs() == 0) {
	p->addRect();
	q->addRect();
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
      }
    }    
    else if(m.getAddress() == "/create/triangle") {
      if(m.getNumArgs() == 0) {
	p->addTriangle();
	q->addTriangle();
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
      }
    }
    else if(m.getAddress() == "/create/righttriangle") {
      if(m.getNumArgs() == 0) { 
	p->addRightTriangle();
	q->addRightTriangle();
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
      }
    }
    else if(m.getAddress() == "/camera/heading/x") {
     //change x heading
      int heading = m.getArgAsInt32(0);
      p->setCameraDirectionX(ofMap(heading, 0, 127, -0.5, 0.5));
      q->setCameraDirectionX(ofMap(heading, 0, 127, -0.5, 0.5));
    }
    else if(m.getAddress() == "/camera/heading/y") {
      //change y heading
      int heading = m.getArgAsInt32(0);
      p->setCameraDirectionY(ofMap(heading, 0, 127, -0.5, 0.5));
      q->setCameraDirectionY(ofMap(heading, 0, 127, -0.5, 0.5));
    }
    else if(m.getAddress() == "/shape/speed") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float speed = ofMap(m.getArgAsInt32(0), 0, 127, -1.0, 1.0);
	if(m.getArgAsInt32(0) >= 63 && m.getArgAsInt32(0) <= 65) {
	  speed = 0;
	}
	p->setShapeSpeed(speed);
	q->setShapeSpeed(speed);
      }
    }
    else if(m.getAddress() == "/shape/rotationspeed") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float speed = ofMap(m.getArgAsInt32(0), 0, 127, -1.0, 1.0);
	if(m.getArgAsInt32(0) >= 63 && m.getArgAsInt32(0) <= 65) {
	  speed = 0;
	}
	p->setShapeSpeed(speed);
	q->setShapeSpeed(speed);
      }
    }
    else if(m.getAddress() == "/color/saturation") {
      if(m.getArgType(0) == OFXOSC_TYPE_INT32) {
	float saturation = ofMap(m.getArgAsInt32(0), 0, 127, 0, 255);
	p->setShapeSaturation(saturation);
	q->setShapeSaturation(saturation);
      }
    }
    else if(m.getAddress() == "/perspective/left/alpha") {
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
    else if(m.getAddress() == "/perspective/right/alpha") {
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
  ofDisableAlphaBlending();

  string info = ofToString(ofGetFrameRate(), 2)+"\n";
  ofDrawBitmapStringHighlight(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == ' ') {
    p->reset();
    q->reset();
  }
  if(key == 't') {
    p->addTriangle();
    q->addTriangle();
  }
  if(key == 'r') {
    p->addRightTriangle();
    q->addRightTriangle();
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

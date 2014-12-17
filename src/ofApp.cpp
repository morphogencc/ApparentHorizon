#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  mElapsedTime = 0.0;
  mZoom = -2.0;

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
    ofxOscMessage m;
    receiver.getNextMessage(&m);
    ofLog() << "Message: " << m.getAddress();
    if(m.getNumArgs() > 0) {
      ofLog() << "Value: " << m.getArgAsString(0);
      ofLog() << "Value type: " << m.getArgType(0);
    }
    if(m.getAddress() == "/create/rect") {
      p->addRect();
    }    
    else if(m.getAddress() == "/create/triangle") {
      if(m.getNumArgs() > 0) {
	//TODO -- osc to float
	p->addTriangle();
      }
      else {
	p->addTriangle();
      }
    }
    
    else if(m.getAddress() == "/create/cube") {
      p->addCube();
    }    
    else if(m.getAddress() == "/camera/position") {
      if(m.getArgType(0) == OFXOSC_TYPE_FLOAT) { 
	p->translateCamera(m.getArgAsFloat(0));
      }
    }
    else if(m.getAddress() == "/camera/heading/x") {
      if(m.getArgType(0) == OFXOSC_TYPE_FLOAT) { 
	p->setCameraDirectionX(m.getArgAsFloat(0) - 0.5);
      }
    }
    else if(m.getAddress() == "/camera/heading/y") {
      if(m.getArgType(0) == OFXOSC_TYPE_FLOAT) { 
	p->setCameraDirectionY(m.getArgAsFloat(0) - 0.5);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  ofEnableAlphaBlending();
  p->beginProjection();
  p->drawGrid();
  p->draw();
  p->endProjection();
  ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if(key == ' ') {
    p->addRect();
  }
  if(key == 't') {
    p->addTriangle();
  }
  if(key == 'c') {
    p->addCube();
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

  //p->changeCameraDirection(heading);
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

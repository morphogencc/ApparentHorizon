#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  /*
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofDisableArbTex();
  ofEnableDepthTest();

  img.loadImage("test.jpg");
  model.loadModel("single_screen.obj");
  fbo.allocate(img.width, img.height);
  mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
  8?

  */

  //----------
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
      //TODO: string to float
      //p->translateCamera(atof(m.getArgAsString(0)));
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
    p->addTriangle();
  }
  if(key == 'c') {
    p->addCube();
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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

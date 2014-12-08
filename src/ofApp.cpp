#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  ofDisableArbTex();
  ofEnableDepthTest();

  img.loadImage("test.jpg");
  model.loadModel("single_screen.obj");
  fbo.allocate(img.width, img.height);
  mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

  //----------
  mElapsedTime = 0.0;
  
  oscPort = 7000;
  ofLog() << "Listening for OSC messages on port " << oscPort << "\n";
  receiver.setup(oscPort);

  for(int i = 0; i < 10; i++) {
    double _x = ofRandomf();
    double _y = ofRandomf();
    double _z = ofRandomf()-1.0;
    
    objPos[i] = ofVec3f(_x,_y,_z);
    
    for(int j = 0; j < 4; j++) {
      ofColor _color;
      _color.set((unsigned char)255.0*ofRandomf(), (unsigned char)255.0*ofRandomf(), (unsigned char)255.0*ofRandomf(), (unsigned char)255.0*0.4);
      colors[i][j] = _color;
    }
  }

  p = new Perspective();
}

//--------------------------------------------------------------
void ofApp::update(){
  mElapsedTime = ofGetElapsedTimef();
  p->update(mElapsedTime);
  while(receiver.hasWaitingMessages()) {
    ofxOscMessage m;
    receiver.getNextMessage(&m);
    ofLog() << "Message: " << m.getAddress();
    //vector<std::string> address = ofSplitString(m.getAddress(), "/");
    //ofLog() << "Command: " << address.at(0);
    //ofLog() << "Value: " << address.at(1);
    if(m.getAddress() == "/create/shape") {
      p->addShape();
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
    p->addShape();
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

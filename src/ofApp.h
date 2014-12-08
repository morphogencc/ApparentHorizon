#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "atlasSyphonClient.h"
#include "Perspective.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

 public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

 private:
		float width, height;
		ofxAssimpModelLoader model;
		ofImage img;
		ofMesh mesh;
		ofFbo fbo;
		ofEasyCam camera;
		ofLight light;
		ofxOscReceiver receiver;
		//-----------
		int oscPort;
		double mElapsedTime;
		ofVec3f objPos[10];
		ofColor colors[10][4];
		Perspective* p;
};

#endif

#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "Perspective.h"
#include "ofxOsc.h"
#include "ofxUI.h"

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
		ofMesh mMesh;
		float mMaxDistance;
		//-----------
		ofxOscReceiver receiver;
		int oscPort;
		double mElapsedTime;
		Perspective* p;
		Perspective* q;
		float mZoom;
		bool mDebug;
		bool mFPS;
		float pAlpha, qAlpha;
};

#endif

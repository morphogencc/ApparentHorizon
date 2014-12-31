#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
  //We want to leave this as OF_Window because fullscreen ends up using the full resolution of the triplehead when we only want to use 2 out of the 3 monitors
  ofSetupOpenGL(1600, 600, OF_WINDOW);			// <-------- setup the GL context
  //Setting window position moves the window past the first monitor and directly onto the second monitor. 
  //Set to (1920, 0) for Adam's laptop
  ofSetWindowPosition(1920,0);
  
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());
}

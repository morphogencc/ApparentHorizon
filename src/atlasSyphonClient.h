/*
atlasSyphonClient
nathan lachenmyer
april 2014

extends the ofxSyphonClient class so that the texture attribute can be extracted and used as a texture for mapping.
*/

#include "ofxSyphon.h"

class atlasSyphonClient : public ofxSyphonClient {
 public:
  atlasSyphonClient();
    
  ofTexture& getTexture() { 
    return mTex; 
  }
  
  int getTextureId() { 
    return mTex.getTextureData().textureID; 
  }

};


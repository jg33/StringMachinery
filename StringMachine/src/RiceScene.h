//
//  RiceScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/14/14.
//
//

#ifndef __StringMachine__RiceScene__
#define __StringMachine__RiceScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "Rice.h"
#include "ofxColourTheory.h"
#include "ofxSyphon.h"

class RiceScene : public ofxScene{
    
public:
    RiceScene():ofxScene("Rice"){setSingleSetup(false);};
    RiceScene(ofxSyphonServer * _syphon):ofxScene("Rice"){syphon = _syphon; setSingleSetup(false);};

    void setup();
    void update();
    void draw();
    
    void setWind(ofVec3f _wind);
    
private:
    
    ofxParticleManager pBoss;
    
    ofxColourTheory colorMaker;
    vector<ofColor> pallette;

    ofVec3f wind;
    
    ofxSyphonServer * syphon;
    
};

#endif /* defined(__StringMachine__RiceScene__) */

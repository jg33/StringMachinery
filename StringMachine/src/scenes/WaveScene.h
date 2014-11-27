//
//  WaveScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 11/26/14.
//
//

#ifndef __StringMachine__WaveScene__
#define __StringMachine__WaveScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"

class Wave{
    
public:
    Wave(){setup();};
    ofVec3f baseLoc;
    
    void setup();
    void draw();
    void update();
    
    
private:
    
    int numBasePoints = 6;
    
    vector<ofPoint> basePoints;
    ofPolyline line;
    
};


class WaveScene : public ofxScene{
    
public:
    WaveScene():ofxScene("Waves"){};
    WaveScene(ofxSyphonServer* _syphon):ofxScene("Waves"){syphon=_syphon;setup();};
    
    
    void setup();
    void draw();
    void update();
    
    
private:
    ofxSyphonServer * syphon;
    
    deque<Wave> waves;
    
};

#endif /* defined(__StringMachine__WaveScene__) */

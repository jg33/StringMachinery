//
//  PulseScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 4/3/15.
//
//

#ifndef __StringMachine__PulseScene__
#define __StringMachine__PulseScene__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAppUtils.h"
#include "ofxSvg.h"
#include "Fragment.h"
#include "ofxSyphon.h"


class PulseScene : public ofxScene{
    
public:
    PulseScene():ofxScene("Fragments"){setSingleSetup(false);};
    PulseScene(ofxSyphonServer* _syphon):ofxScene("Pulse"){syphon = _syphon; setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
    inline void setMaxBrightness(float _brightness){maxBrightness = _brightness;
        
        maxBrightness = ofMap(maxBrightness, 0.001, 1, 0, 255);
        for(int i=0;i<fragments.size();i++){
            fragments[i].setMaxBrightness(maxBrightness);
        }
    };
    
    inline void setSpeed(float speed){
        speed = ofMap(speed, 0.001, 1, 0.1,3);
        for(int i=0;i<fragments.size();i++){
            fragments[i].setPulseSpeed(speed);
        }
    };
    
private:
    vector<Fragment> fragments;
    ofxSVG image;
    ofxSyphonServer * syphon;
    
    float maxBrightness = 150;
};



#endif /* defined(__StringMachine__PulseScene__) */

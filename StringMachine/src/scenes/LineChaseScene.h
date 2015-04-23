//
//  LineChaseScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 11/11/14.
//
//

#ifndef __StringMachine__LineChaseScene__
#define __StringMachine__LineChaseScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "ofxSvg.h"

#include "Fragment.h"
#include "LineChaser.h"

#define NUM_LINES 4

class LineChaseScene : public ofxScene{
    
public:
    LineChaseScene():ofxScene("LineChase"){};
    LineChaseScene(ofxSyphonServer* _syphon1, ofxSyphonServer* _syphon2):ofxScene("Metal and Wood"){syphon1=_syphon1; syphon2 = _syphon2; setSingleSetup(false);};

    
    void setup();
    void draw();
    void update();
    void exit(){
        lines.clear();
    }
    
    void setSpeed(float spd){
        for (int i = 0; i<lines.size(); i++) {
            lines[i].setSpeed(spd);
        }
    }
    
    void setHome(float x){
        for (int i = 0; i<lines.size(); i++) {
            lines[i].setHomeX(x);
        }
    }

    
    void setLineDisp(int i, float d);
    
    void fire(float freq, float amp);
    void fireRandom();
    void fireRandom(float size);
    
private:
    ofxSyphonServer * syphon1, *syphon2;
    ofFbo drawer;
    
    vector <LineChaser> lines;
    
    vector<Fragment> fragments;
    ofxSVG image;
    
};


#endif /* defined(__StringMachine__LineChaseScene__) */

//
//  Fragment.h
//  StringMachine
//
//  Created by Jesse Garrison on 11/5/14.
//
//

#ifndef __StringMachine__Fragment__
#define __StringMachine__Fragment__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAppUtils.h"


class Fragment{
    
public:
    Fragment(){setup();};
    Fragment(ofPath _path){shape =_path;setup();};
    void setup();
    void update();
    void draw();
    
    void fire(int level);
    inline void setDecay(float _decay){decay = _decay;};
    inline void setMaxBrightness(int max){maxBrightness=max;};
    inline void setPulseMode(bool pulse){isPulseMode=pulse;};
    inline void setPulseSpeed(float speed){pulseSpeed=basePulseSpeed*speed;};

    
    bool isPulseMode = false;
    float pulseSpeed = 1;
    
private:
    
    ofVec3f loc;
    
    ofPath shape;
    vector<ofPolyline> outlines;
    
    float brightness, maxBrightness;
    float decay;
    
    int seed;
    float basePulseSpeed;
    //ofxTimer timer;
    
    float counter;
    
};


#endif /* defined(__StringMachine__Fragment__) */

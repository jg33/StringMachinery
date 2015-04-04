//
//  SingleStringScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 11/26/14.
//
//

#ifndef __StringMachine__SingleStringScene__
#define __StringMachine__SingleStringScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"

class LittleString{
    
public:
    LittleString(){};
    void setup();
    inline void setup(float _radius){radius=_radius; setup(); };
    void update();
    void draw();
    float radius = 50;
    bool isFilling = true;
    
private:
    float rotation;
    float twist;
    
    int numPoints = 15;
    int seed;
    
    vector<ofVec3f> basePoints, points;
    
    ofPolyline line;
    
};



class SingleStringScene : public ofxScene{
    
public:
    SingleStringScene():ofxScene("Single"){};
    SingleStringScene(ofxSyphonServer* _syphon):ofxScene("SingleString"){syphon=_syphon;};
    
    
    void setup();
    void draw();
    void update();
    
    void setLineDisp(int i, float d);
    
private:
    ofxSyphonServer * syphon;
    
    LittleString little;
    
    
};



#endif /* defined(__StringMachine__SingleStringScene__) */

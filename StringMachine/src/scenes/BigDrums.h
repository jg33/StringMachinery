//
//  BigDrums.h
//  StringMachine
//
//  Created by Jesse Garrison on 4/19/15.
//
//

#ifndef __StringMachine__BigDrums__
#define __StringMachine__BigDrums__

#define NUMCIRCLES 2

#include <stdio.h>
#include "ofMain.h"
#include "ofxAppUtils.h"
#include "Circle.h"
#include "ofxSvg.h"
#include "Fragment.h"
#include "ofxSyphon.h"

class Ring{
    
public:
    Ring(){;};
    Ring(float _vel){
        initialVel = _vel;
        vel = _vel;
        drag = 0.3;
        
    }
    void update(){
        if (vel<=0){
            bWillDie=true;
        } else {
            //age++;
            vel-=drag;
            size+=vel;
            age++;
        }
        
        
        rot = float(size) *0.1;
        
    }
    void draw(){
        ofRotateZ( rot);
        ofNoFill();
        ofSetLineWidth(7);
        ofSetColor(ofMap(vel,initialVel,0,255,0));
        ofSetCircleResolution(8);
        
        ofDrawCircle(0, 0, size);
        
    }
    
    bool bWillDie;
    
    
private:
    
    float size, vel, drag, initialVel, rot;
    int age, life;
    
};




class BigDrums : public ofxScene{
    
public:
    BigDrums():ofxScene("BigDrums"){setSingleSetup(false);};
    
    BigDrums(ofxSyphonServer *_syphon1, ofxSyphonServer *_syphon2, ofxSyphonServer *_syphon3):ofxScene("Big Drums"){
        setSingleSetup(false);
        syphon1 = _syphon1;
        syphon2 = _syphon2;
        syphon3 = _syphon3;
    
    };
    
    
    void setup();
    void update();
    void draw();
    
    void setSizes(vector<float>);
    
    inline void setSize(int i, float amp ){circles[i].setSize(amp);};
    
    void bonkRing(float vel){
        rings.push_back( Ring(  ofMap(vel,0.0001,1,0.1,60)   ) );
    };
    
    void fireRandom();
    void fireRandom(float size);
private:
    vector<Circle> circles;
    
    ofVec2f startLoc;
    vector<Ring> rings;
    vector<Fragment> fragments;
    ofxSVG image;
    
    ofFbo drawer1;
    ofFbo drawer2;
    ofxSyphonServer *syphon1, *syphon2, *syphon3;
    
};



#endif /* defined(__StringMachine__BigDrums__) */

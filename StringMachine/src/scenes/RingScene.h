//
//  RingScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 4/12/15.
//
//

#ifndef __StringMachine__RingScene__
#define __StringMachine__RingScene__

#include <stdio.h>
#include "ofxAppUtils.h"
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



class RingScene: public ofxScene{
    
    
public:
    RingScene() :  ofxScene("Ring"){;};
    RingScene(ofxSyphonServer* _syphon) :  ofxScene("Ring"){
        syphon = _syphon;
        setup();
    };
    void setup();
    void update();
    void draw();
    
    void bonkRing(float vel){
        rings.push_back( Ring(vel) );
    };
    
private:
    ofVec2f startLoc;
    vector<Ring> rings;
    ofxSyphonServer* syphon;
    
};




#endif /* defined(__StringMachine__RingScene__) */

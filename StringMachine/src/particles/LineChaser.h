//
//  LineChaser.h
//  StringMachine
//
//  Created by Jesse Garrison on 11/11/14.
//
//

#ifndef __StringMachine__LineChaser__
#define __StringMachine__LineChaser__

#include <stdio.h>
#include "ofMain.h"


class LineChaser{
public:
    LineChaser(){seed=ofRandom(6000);};
    LineChaser(float _height){
        homebase = ofVec2f(ofGetWidth()/2, _height);
        seed=ofRandom(6000);
        displaceDecay = 0.9;
    };

    
    void update();
    void draw();
    
    void setDisplacement(float d);
    
    void setSpeed(float spd){
        speedMult = spd;
        
    }
    
    void setHomeX(float x){
        
        homebase.x = x;
    }
    
private:
    float seed;
    
    float speed, speedMult = 100;
    float displacement, displaceDecay;
    
    ofVec2f homebase, front;
    vector<ofVec2f> points;
    
    ofPolyline line;
    
    int step = 1;
    
    
};
#endif /* defined(__StringMachine__LineChaser__) */

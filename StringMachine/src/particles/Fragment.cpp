//
//  Fragment.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/5/14.
//
//

#include "Fragment.h"

void Fragment::setup(){
    decay = 10;
    
    loc = ofVec3f(ofRandom(1000), ofRandom(1000));
    outlines = shape.getOutline();
    
    //cout<<shape.getOutline().size()<<endl;
    shape.setFilled(true);
    
    seed = ofRandom(6666);
    basePulseSpeed = ofRandom(0.2, 0.7);
    pulseSpeed = basePulseSpeed;
     
}

void Fragment::update(){
    counter += pulseSpeed;
    //counter *= 1;
    
    if (isPulseMode) {
        brightness = ofMap(sinf((counter+seed)*0.1), -1, 1, 0, maxBrightness);
    } else {
        brightness-=decay;
        if(brightness<0) brightness = 0;
    }
    float scale = ofMap(brightness, 0.0001, maxBrightness, 0, 1);
    
    //shape.close();
    shape.setFillColor(brightness);
    //shape.scale(0.5, 0.5);
    //shape.setStrokeColor(255);
   // shape.setStrokeWidth(2);

    
}

void Fragment::draw(){
    //ofSetColor(255);
    //ofDrawRectangle(loc, 50, 50);
    ofPushStyle();
    ofSetLineWidth(0);

    shape.draw();
    ofPopStyle();

    
}


void Fragment::fire(int level){
    brightness = level;
    
}
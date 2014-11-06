//
//  Fragment.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/5/14.
//
//

#include "Fragment.h"

void Fragment::setup(){
    decay = 1;
    
    loc = ofVec3f(ofRandom(1000), ofRandom(1000));
}

void Fragment::update(){
    brightness -= decay;
}

void Fragment::draw(){
    ofSetColor(brightness);
    ofDrawRectangle(loc, 50, 50);
    
}


void Fragment::fire(int level){
    brightness = level;
    
}
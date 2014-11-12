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
    //outlines = shape.getOutline();
    
    //cout<<shape.getOutline().size()<<endl;
    shape.setFilled(true);
}

void Fragment::update(){
    brightness-=decay;
    if(brightness<0) brightness = 0;
    
    float scale = ofMap(brightness, 0, 255, 0, 1);
    
    //shape.close();
    shape.setFillColor(brightness);
    //shape.scale(0.5, 0.5);
    //shape.setStrokeColor(255);
   // shape.setStrokeWidth(2);

    
}

void Fragment::draw(){
    //ofSetColor(255);
    //ofDrawRectangle(loc, 50, 50);

    shape.draw();
    

    
}


void Fragment::fire(int level){
    brightness = level;
    
}
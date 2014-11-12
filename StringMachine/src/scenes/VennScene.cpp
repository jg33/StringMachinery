//
//  VennScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/12/14.
//
//

#include "VennScene.h"

void VennScene::setup(){
    left = VennCircle(LEFT);
    right = VennCircle(RIGHT);
    
}

void VennScene::update(){
    left.update();
    right.update();
    
    rotation+= rotationSpeed;
}

void VennScene::draw(){
    ofBackground(0);
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofRotate (rotation);
    left.draw();
    right.draw();
    overlapShape.draw();
    
    syphon->publishScreen();
}



///-----///

VennCircle::VennCircle(vennSide _side){
    side = _side;
    
}


void VennCircle::update(){
    //loc = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
    loc = ofVec2f();
    
    switch (side) {
        case LEFT:
            loc.x -= displacement;
            break;
            
        case RIGHT:
            loc.x+= displacement;
            break;
            
        default:
            break;
    }
    
    
    //loc.rotate(rotation, ofVec2f(ofGetWidth()/2,ofGetHeight()/2) );
    
    
    
}

void VennCircle::draw(){
    
    ofSetColor(255);
    ofNoFill();
    ofSetLineWidth(3);
    ofSetCircleResolution(100);
    ofDrawCircle(loc, radius);
    //line.draw();
}
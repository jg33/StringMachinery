//
//  CirclePart.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/10/14.
//
//

#include "CirclePart.h"


void CirclePart::setup(){
    lifespan = ofRandom(10000);
    pos = ofVec3f(ofRandom(ofGetWidth()),ofRandom( ofGetHeight()));
    seed = ofRandom(10000);
    maxSize = 10;
    size = ofRandom(1,maxSize);
    drag = 0.1;
    
    
}

void CirclePart::customUpdate(){
    
    acc = ofVec3f(ofSignedNoise(seed+ofGetElapsedTimeMillis()*0.00009), ofSignedNoise(600+seed+ofGetElapsedTimeMillis()*0.00003), ofSignedNoise(132+seed+ofGetElapsedTimeMillis()*0.00007)  ) ;
    acc *= 0.1;

    if (prevAge>getAge()) {
        bIsSpecial = true;
    } else {
        prevAge = getAge();
    }
}

void CirclePart::draw(){
    ofPushStyle();
    ofFill();
    
    if(bIsSpecial) ofDisableLighting(); else ofEnableLighting();
    
    
    if(getAgeN() < 0.1){
        ofSetColor( color, ofClamp( ofMap(getAgeN(),0,0.1, 0,255) ,0,255) ) ;
    } else{
        ofSetColor( color, ofClamp( ofMap(getAgeN(),0.1,1, 255,0) ,0,255) ) ;
    }
    //ofDrawCircle(pos, size) ;
    ofDrawSphere(pos, size);
    ofPopStyle();
}


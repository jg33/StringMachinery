//
//  Rice.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/14/14.
//
//

#include "Rice.h"


void Rice::setup(){
    size = ofRandom(1,10);
    pos = ofVec3f(ofRandom(500),ofRandom(500));
    lifespan = ofRandom(2000,6000);
    rotationOffset = ofVec3f(ofRandom(180),ofRandom(180),ofRandom(180) );
    //wind = ofVec2f(0.001,0);

}

void Rice::customUpdate(){
    
    
    acc += ofVec2f(0,0.001); //gravity
   // acc += wind;
    
    rotation = rotationOffset+ofVec3f(vel.x*ofGetElapsedTimef(),vel.y*ofGetElapsedTimef(),vel.z*ofGetElapsedTimef() );
    
}

void Rice::draw(){
    //ofBackground(0) ;
    ofPushStyle();
    ofPushMatrix();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofTranslate(pos);
    ofRotateX(rotation.x);
    ofRotateY(rotation.y);
    ofRotateZ(rotation.z);
    ofRect(0,0,0, size, size/2);
    ofPopMatrix();
    ofPopStyle();
}


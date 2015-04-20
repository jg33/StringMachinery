//
//  FlickerScreen.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 4/18/15.
//
//

#include "FlickerScreen.h"


void FlickerScreen::setup(){
    ofDisableLighting();
    ofDisableAlphaBlending();
    cout<<"setup flicker!"<<endl;
    
}

void FlickerScreen::update(){
    
    
}

void FlickerScreen::draw(){
    ofBackground(0) ;
    ofSetColor(255, 0, 0);
    ofDrawRectangle(0, 0, 30,30);
    syphon->publishScreen();
    
    
    ofBackground(brightness);
    ofSetColor(brightness*255);
    ofRect(0,0,ofGetWidth(),ofGetHeight());
}
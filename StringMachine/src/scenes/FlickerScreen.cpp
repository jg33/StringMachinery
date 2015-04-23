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
    
    ofBackground(brightness);
    ofSetColor(brightness*255);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    syphon->publishScreen();

}
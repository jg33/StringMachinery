//
//  WaveFormScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 4/18/15.
//
//

#include "WaveFormScene.h"



void WaveFormScene::setup(){
    ofDisableLighting();
    ofDisableAlphaBlending();
    cout<<"setup waveform!"<<endl;
    
    amp1 = 25;
    scale1 = 250;
    
    amp2 = 25;
    scale2 = 75;
    
    amp3 = 25;
    scale3 = 550;
    
}

void WaveFormScene::update(){
    wave.currentAmp = amp1*scale1;
    wave.update();
    
    wave2.currentAmp = amp1*scale2;
    wave2.xStep = 1;
    wave2.update();
    
    wave3.currentAmp = amp1*scale3;
    wave3.xStep = 10;
    wave3.update();
    
}

void WaveFormScene::draw(){
    ofEnableDepthTest();
    
    ofBackground(0);
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    ofSetColor(255);
    wave.draw();
    
    ofSetColor(200, 0, 0);
    wave2.draw();

    ofSetColor(150, 0, 0);
    wave3.draw();

}


void WaveFormScene::exit(){
    wave.clear();
    wave2.clear();
    wave3.clear();
    
}
//
//  PulseScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 4/3/15.
//
//

#include "PulseScene.h"



void PulseScene::setup(){
    ofDisableLighting();
    image.load("apr12_map_v3.svg");
    fragments.clear();
    for(int i=0;i<image.getNumPath();i++){
        fragments.push_back(Fragment(image.getPathAt(i)));
        fragments[fragments.size()-1].setMaxBrightness(maxBrightness);
        fragments[fragments.size()-1].setPulseMode(true);
    }
    
    cout<<"setup pulses! paths: "<<image.getNumPath()<<endl;
}

void PulseScene::update(){
    for(int i=0;i<fragments.size();i++){
        fragments[i].update();
        
    }
}

void PulseScene::draw(){
    if(ofGetLightingEnabled()) ofDisableLighting();

    ofBackground(0);
    ofSetLineWidth(0);

    for(int i=0;i<fragments.size();i++){
        fragments[i].draw();
        
    }
    
    syphon->publishScreen();
    //image.draw();
    
}

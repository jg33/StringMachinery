//
//  LineChaseScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/11/14.
//
//

#include "LineChaseScene.h"

void LineChaseScene::setup(){
    
    drawer.allocate(ofGetWidth(), ofGetHeight());
    ofDisableLighting();
    ofDisableAlphaBlending();
    cout<<"setup line chase!"<<endl;
    for (int i = 0; i<NUM_LINES; i++) {
        lines.push_back(LineChaser(200+ (i*50) ));
    }
    
    image.load("apr12_map_v3.svg");
    fragments.clear();
    for(int i=0;i<image.getNumPath();i++){
        fragments.push_back(Fragment(image.getPathAt(i)));
        
    }

    
}

void LineChaseScene::update(){
    for (int i = 0; i<lines.size(); i++) {
        lines[i].update();
    }
    
    for(int i=0;i<fragments.size();i++){
        fragments[i].update();
        
    }
    
}


void LineChaseScene::draw(){
    
    drawer.begin();
    ofClear(0);
    ofSetLineWidth(0);
    for(int i=0;i<fragments.size();i++){
        fragments[i].draw();
        
    }
    drawer.end();
    
    
    if(ofGetLightingEnabled()) ofDisableLighting();
    
    ofBackground(0);
    
    for (int i = 0; i<lines.size(); i++) {
        lines[i].draw();
    }
    
    syphon1->publishScreen();
    syphon2->publishTexture(&drawer.getTexture());
}


void LineChaseScene::setLineDisp(int i, float d){
    lines[i].setDisplacement(d);
    
}

void LineChaseScene::fireRandom(){
    fragments[(int)ofRandom(fragments.size())].fire(255);
    
}

void LineChaseScene::fireRandom(int size){
    
}


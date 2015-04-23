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
        lines.push_back(LineChaser(400+ (i*50) ));
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
    d = ofMap(d, -1,1,-250,250);
    lines[i].setDisplacement(d);
    
}

void LineChaseScene::fire(float freq, float amp){
    int num = floor(ofMap(freq, 0.0001, 1, 0, fragments.size()));
    amp = ofMap(amp, 1, 0.0001, 0, 255);
    fragments[num].fire(amp);
    
}

void LineChaseScene::fireRandom(){
    fragments[(int)ofRandom(fragments.size())].fire(255);
    
}

void LineChaseScene::fireRandom(float size){
    fragments[(int)ofRandom(fragments.size())].fire(size);

}


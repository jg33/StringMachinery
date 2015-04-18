//
//  RingScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 4/12/15.
//
//

#include "RingScene.h"

bool checkDead(Ring r){
    return r.bWillDie;
    
}


void RingScene::setup(){
    startLoc = ofVec2f( ofGetWidth()/2, ofGetHeight()/2);
    
}

void RingScene::update(){
    ofRemove(rings, &checkDead);
    for (int i = 0 ; i< rings.size(); i++) {
        rings[i].update();
    }
    
}



void RingScene::draw(){
    ofBackground(0,5) ;
    ofTranslate(startLoc);
    for (int i = 0 ; i< rings.size(); i++) {
        rings[i].draw();
    }
    
}



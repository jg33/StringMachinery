//
//  BoidScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 2/3/15.
//
//

#include "BoidScene.h"


void BoidScene::setup(){
    
    ofEnableSmoothing();
    
}

void BoidScene::update(){
    flock.update();
    flock.updateRibbons();

    
    if(ofGetFrameNum()%5==0 && flock.boids.size()<100){
        flock.addRibbon();
    }
    
}

void BoidScene::draw(){
    ofBackground(0);

    flock.draw();
    
    
    for(int i=0;i<flock.boids.size();i++){
        flock.boids[i].maxspeed = 1000;
        flock.boids[i].maxforce = 0.1;
        flock.boids[i].draw();
        
    }
    syphon->publishScreen();
    
}
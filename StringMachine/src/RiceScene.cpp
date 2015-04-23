//
//  RiceScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/14/14.
//
//

#include "RiceScene.h"

void RiceScene::setup(){
    ofDisableLighting();
    pBoss = ofxParticleManager();
    cout<<"setup rice!"<<endl;
    finishedEntering();
    
    ofColor primaryColor = ofColor::red;
    pallette = colorMaker.createColoursFromStrategy(primaryColor, CT_ANALOGOUS);
    pallette.push_back(primaryColor);
    
    wind = ofVec3f(0.001,0);
}

void RiceScene::update(){
    ofColor thisColor = pallette.at(floor(ofRandom(pallette.size())));
    pBoss.addParticle(new Rice(thisColor));
    
    
    for(int i =0;i<pBoss.getParticlesPtr()->size();i++){
        pBoss.getParticlesPtr()->at(i)->setAcc(pBoss.getParticlesPtr()->at(i)->getAcc()+wind);
        
    }
    
    
    
    pBoss.update();
    
    
}

void RiceScene::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofFill();
    pBoss.draw();
    
    syphon->publishScreen();
    
}

void RiceScene::setWind(ofVec3f _wind){
    
    wind = _wind;
    

}
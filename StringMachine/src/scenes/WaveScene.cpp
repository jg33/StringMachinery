//
//  WaveScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/26/14.
//
//

#include "WaveScene.h"

void Wave::setup(){
    
    for(int i=0;i< numBasePoints;i++){
        basePoints.push_back( ofPoint(i*200,sin(i*10)*200  ) );
    }
    
}

void Wave::update(){
    
    for(int i=0;i< numBasePoints;i++){
        basePoints[i].y = sin( (ofGetElapsedTimef())+i)*400  ;
    }
    
    line.clear();
    for(int i=0;i< numBasePoints;i++){
        line.curveTo(basePoints[i]);
    }
}

void Wave::draw(){
    //ofSetColor(255);
    ofSetLineWidth(3);
    line.draw();
}


void WaveScene::setup(){
    
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    for (int i=0; i<20; i++) {
        waves.push_front(Wave());
    }
    
}

void WaveScene::update(){
    for (int i = 0; i< waves.size(); i++) {
        waves[i].update();
    }
}

void WaveScene::draw(){
    ofBackground(0);
    
    ofTranslate( (ofGetWidth()/2) -600, ofGetHeight()/2);
    for (int i = 0; i< waves.size(); i++) {
        ofTranslate(0,cos(ofGetElapsedTimef())*10,-100);
        ofSetColor( (     (waves.size()-(float)i )  /waves.size()   ) * 255  );
        waves[i].draw();
    }
    
}
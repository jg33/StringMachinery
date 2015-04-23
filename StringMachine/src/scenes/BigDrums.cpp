//
//  BigDrums.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 4/19/15.
//
//

#include "BigDrums.h"

bool checkDead(Ring r){
    return r.bWillDie;
    
}


void BigDrums::setup(){
    ofDisableLighting();
    startLoc = ofVec2f( ofGetWidth()/2, ofGetHeight()/2);

    
    for (int i=0; i<NUMCIRCLES; i++) {
        circles.push_back(Circle());
        
    }
    
    circles[0].setPosition(50, 50, 0);
    circles[1].setPosition(ofGetWidth()/4, ofGetHeight()/4, 0);
    
    
    for (int i = 0; i<circles.size(); i++){
        circles[i].setSize(60);
    }
    
    
    image.load("apr12_map_v3.svg");
    fragments.clear();
    for(int i=0;i<image.getNumPath();i++){
        fragments.push_back(Fragment(image.getPathAt(i)));
        
    }
    
    cout<<"setup drums! paths: "<<image.getNumPath()<<endl;

    drawer1.allocate(ofGetWidth(), ofGetHeight());
    drawer2.allocate(ofGetWidth(), ofGetHeight());

}

void BigDrums::update(){
    ofRemove(rings, &checkDead);
    for (int i = 0 ; i< rings.size(); i++) {
        rings[i].update();
    }
    
    for(int i=0;i<fragments.size();i++){
        fragments[i].update();
        
    }
    
    
}


void BigDrums::draw(){
    if(ofGetLightingEnabled()) ofDisableLighting();
    
    drawer1.begin();
    ofClear(0);
    ofSetColor(255);
    ofFill();
    for (int i=0; i<circles.size(); i++) {
        circles[i].draw();
    }
    drawer1.end();
    
    drawer2.begin();
    ofBackground(0,5) ;
    ofTranslate(startLoc);
    for (int i = 0 ; i< rings.size(); i++) {
        rings[i].draw();
    }
    drawer2.end();
    
    ofBackground(0);
    ofSetLineWidth(0);
    for(int i=0;i<fragments.size();i++){
        fragments[i].draw();
        
    }
    syphon1->publishScreen();
    syphon2->publishTexture(&drawer1.getTexture());
    syphon3->publishTexture(&drawer2.getTexture());

    
}

void BigDrums::setSizes(vector<float> s){
    
    
    for (int i=0; i<circles.size(); i++) {
        try {
            circles[i].setSize(s[i-1]*50);
            
        } catch (exception e) {
            cout<< "except"<< endl;
        }
    }
    
    
    
}

void BigDrums::fireRandom(){
    fragments[(int)ofRandom(fragments.size())].fire(255);
    
}

void BigDrums::fireRandom(float size){
    
    size = ofMap(size,0,1,0,255);
    fragments[(int)ofRandom(fragments.size())].fire(size);

}
    
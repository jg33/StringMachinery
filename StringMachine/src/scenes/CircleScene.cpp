//
//  CircleScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/8/14.
//
//

#include "CircleScene.h"


void CircleScene::setup(){
    ofDisableLighting();

    for (int i=0; i<NUMCIRCLES; i++) {
        circles.push_back(Circle());
        
    }
    
    circles[0].setPosition(50, 50, 0);
    circles[1].setPosition(100, 100, 0);

    
    for (int i = 0; i<circles.size(); i++){
        circles[i].setSize(10);
    }
    
    cout<<"setup circles!"<<endl;
    
}

void CircleScene::update(){

    
}

void CircleScene::setSizes(vector<float> s){
    for (int i=0; i<circles.size(); i++) {
        try {
            circles[i].setSize(s[i-1]*50);

        } catch (exception e) {
            cout<< "except"<< endl;
        }
    }
    
}


void CircleScene::draw(){
    if(ofGetLightingEnabled()) ofDisableLighting();

    ofBackground(0);
    ofSetColor(255);
    ofFill();
    for (int i=0; i<circles.size(); i++) {
        circles[i].draw();
    }
    

    
}
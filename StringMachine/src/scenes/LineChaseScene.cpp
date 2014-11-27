//
//  LineChaseScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/11/14.
//
//

#include "LineChaseScene.h"

void LineChaseScene::setup(){
    cout<<"setup line chase!"<<endl;
    for (int i = 0; i<NUM_LINES; i++) {
        lines.push_back(LineChaser(200+ (i*50) ));
    }
    
}

void LineChaseScene::update(){
    for (int i = 0; i<lines.size(); i++) {
        lines[i].update();
    }
    
}


void LineChaseScene::draw(){
    ofBackground(0);
    
    for (int i = 0; i<lines.size(); i++) {
        lines[i].draw();
    }
    
    syphon->publishScreen();
}


void LineChaseScene::setLineDisp(int i, float d){
    lines[i].setDisplacement(d);
    
}
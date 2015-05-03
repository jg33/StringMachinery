//
//  MeshScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 5/3/15.
//
//

#include "MeshScene.h"

bool killDeadLines(MeshLine l){
    return l.bWillDie;
}

void MeshScene::setup(){
    
}

void MeshScene::update(){
    for(int i = 0; i<lines.size();i++){
        lines[i].update();
    }
    
    ofRemove(lines, &killDeadLines);
}

void MeshScene::draw(){
    ofBackground(0);
    for(int i = 0; i<lines.size();i++){
        lines[i].draw();
    }
    syphon->publishScreen();
}

void MeshScene::addLine(float x, float y, float w){
    
    lines.push_back(MeshLine(ofVec2f(x,y),w));
}
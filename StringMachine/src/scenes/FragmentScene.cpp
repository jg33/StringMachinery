//
//  FragmentScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/5/14.
//
//

#include "FragmentScene.h"


void FragmentScene::setup(){
    ofDisableLighting();
    image.load("apr12_map_v3.svg");
    fragments.clear();
    for(int i=0;i<image.getNumPath();i++){
        fragments.push_back(Fragment(image.getPathAt(i)));
        
    }
    
    cout<<"setup frags! paths: "<<image.getNumPath()<<endl;
}

void FragmentScene::update(){
    for(int i=0;i<fragments.size();i++){
        fragments[i].update();
        
    }
}

void FragmentScene::draw(){
    ofBackground(0);
    
    ofSetLineWidth(0);
    for(int i=0;i<fragments.size();i++){
        fragments[i].draw();
        
    }
    
    syphon->publishScreen();
    //image.draw();
   
}

void FragmentScene::fireRandom(){
    fragments[(int)ofRandom(fragments.size())].fire(255);
    
}

void FragmentScene::fireRandom(float size){
    fragments[(int)ofRandom(fragments.size())].fire(size);
    
}
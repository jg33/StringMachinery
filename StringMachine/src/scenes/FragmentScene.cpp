//
//  FragmentScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/5/14.
//
//

#include "FragmentScene.h"


void FragmentScene::setup(){
    for(int i=0;i<NUM_FRAGMENTS;i++){
        fragments.push_back(Fragment());
        
    }
}

void FragmentScene::update(){
    for(int i=0;i<NUM_FRAGMENTS;i++){
        fragments[i].update();
        
    }
}

void FragmentScene::draw(){
    for(int i=0;i<NUM_FRAGMENTS;i++){
        fragments[i].draw();
        
    }
}

void FragmentScene::fireRandom(){
    fragments[(int)ofRandom(fragments.size())].fire(255);
    
}

void FragmentScene::fireRandom(int size){
    
    
}
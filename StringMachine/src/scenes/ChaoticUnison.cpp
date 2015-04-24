//
//  ChaoticUnison.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 4/22/15.
//
//

#include "ChaoticUnison.h"


void ChaoticUnison::setup(){
    ofDisableLighting();
    ofDisableAlphaBlending();
    cout<<"setup chaos!"<<endl;
    
    bands.clear();
    for(int i = 1; i< NUM_BANDS+1;i++){
        bands.push_back(Band(i*150));
        
    }
    
    
    
}

void ChaoticUnison::update(){
    for(int i = 0; i< bands.size();i++){
        bands[i].update();
        
    }
    
}

void ChaoticUnison::draw(){
    
    ofBackground(0);
    
    for(int i = 0; i< bands.size();i++){
        bands[i].draw();
        
    }
    
    
    syphon->publishScreen();
    
}
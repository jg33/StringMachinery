//
//  WavesOfGrain.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 4/20/15.
//
//

#include "WavesOfGrain.h"


void WavesOfGrain::setup(){
    ofEnableLighting();
    ofEnableAlphaBlending();
    
    drawer.allocate(ofGetWidth(), ofGetHeight());
    
    cout<<"setup waves of grain!"<<endl;
    
    amp1 = 0.5;
    scale1 = 250;
    
    amp2 = 0.5;
    scale2 = 75;
    
    amp3 = 0.5;
    scale3 = 550;
    
    
    light1.setup();
    light1.setPointLight();
    light1.setPosition(ofGetWidth()/2, ofGetHeight()/2, -100);
    light1.setDiffuseColor(ofColor(255));
    light1.setAttenuation();
    
    

    
    
}

void WavesOfGrain::update(){
    
    partMan.update();
    
    wave.currentAmp = amp1*scale1;
    wave.update();
    
    wave2.currentAmp = amp1*scale2;
    wave2.xStep = 1;
    wave2.update();
    
    wave3.currentAmp = amp1*scale3;
    wave3.xStep = 10;
    wave3.update();
}

void WavesOfGrain::draw(){
    drawer.begin();
    ofClear(0);
    ofEnableDepthTest();
    ofDisableLighting();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    ofSetColor(255);
    wave.draw();
    
    ofSetColor(200, 0, 0);
    wave2.draw();
    
    ofSetColor(150, 0, 0);
    wave3.draw();
    
    drawer.end();
    
    
    light1.enable();
    ofBackground(0) ;
    partMan.draw();

    syphon1->publishScreen();
    syphon2->publishTexture(&drawer.getTexture());
    
    
}

void WavesOfGrain::addNote(int note, int velocity){
    partMan.addParticle(new NotePart(note, velocity));
    
}


void WavesOfGrain::exit(){
    wave.clear();
    wave2.clear();
    wave3.clear();
    
}




NotePart::NotePart(int _note, int _velocity){
    note = _note;
    velocity = _velocity;
    
    pos = ofVec3f(ofMap(note, 0, 127, 10, ofGetWidth()-10), ofGetHeight()/2);
    targetSize = ofMap(velocity, 0, 127, 0, 200);
    
    rotationAxis = ofVec3f(ofRandom(360),ofRandom(360),ofRandom(360)   );
    
    lifespan = ofRandom(1000,6000);
    
    material.setDiffuseColor(ofColor(255));
    material.setSpecularColor(ofColor(255));
    material.setShininess(120);
    
}

void NotePart::customUpdate(){
    if(age < 100){
        size = ofMap(age, 0, 100, 0, targetSize);
    } else if(age > 100 && age < 200){
        
    } else{
        acc.z = -0.1;
        rotation++;
        
    }
    
    material.setDiffuseColor(ofColor(255,ofMap(age, 0.00001, lifespan, 255,0)));
    material.setSpecularColor(ofColor(255,ofMap(age, 0.00001, lifespan, 255,0)));
    
}

void NotePart::draw(){
    material.begin();
    ofPushMatrix();
    ofTranslate(pos);
    ofRotate(rotation, rotationAxis.x, rotationAxis.y, rotationAxis.z);
    ofSetColor(255, ofMap(age, 0.00001, lifespan, 255,0));
    ofDrawBox(0,0,0, 3,size,3);
    ofPopMatrix();
    material.end();
    
}
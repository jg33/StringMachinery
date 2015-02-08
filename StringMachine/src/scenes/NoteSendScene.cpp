//
//  noteSendScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/26/14.
//
//

#include "noteSendScene.h"

void NoteSendScene::setup(){
    ofEnableLighting();
    ofEnableAlphaBlending();
    
    light1.setup();
    light1.setPointLight();
    light1.setPosition(ofGetWidth()/2, ofGetHeight()/2, -100);
    light1.setDiffuseColor(ofColor(255));
    light1.setAttenuation();
}

void NoteSendScene::update(){
    
    partMan.update();
}

void NoteSendScene::draw(){
    light1.enable();
    ofBackground(0) ;
    partMan.draw();
    
    syphon->publishScreen();
}

void NoteSendScene::addNote(int note, int velocity){
    partMan.addParticle(new NotePart(note, velocity));
    
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
    
    material.setDiffuseColor(ofColor(255,ofMap(age, 0, lifespan, 255,0)));
    material.setSpecularColor(ofColor(255,ofMap(age, 0, lifespan, 255,0)));

}

void NotePart::draw(){
    material.begin();
    ofPushMatrix();
    ofTranslate(pos);
    ofRotate(rotation, rotationAxis.x, rotationAxis.y, rotationAxis.z);
    ofSetColor(255, ofMap(age, 0, lifespan, 255,0));
    ofDrawBox(0,0,0, 3,size,3);
    ofPopMatrix();
    material.end();
    
}
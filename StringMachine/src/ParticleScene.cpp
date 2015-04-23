//
//  ParticleScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/7/14.
//
//

#include "ParticleScene.h"

void ParticleScene::setup(){

    pBoss = ofxParticleManager();
    //attractive.setup(pBoss.getParticlesPtr());
    cout<<"setup particles!"<<endl;
    finishedEntering();
    
    ofColor primaryColor = ofColor::red;
    //pallette = colorMaker.createColoursFromStrategy(primaryColor, CT_ANALOGOUS);
    pallette.push_back(primaryColor);
    
    light1.setup();
    light1.setPointLight();
    light1.setPosition(ofGetWidth()/2, ofGetHeight(), 0);
    light1.setDiffuseColor(ofColor(255.f));
    light1.setSpecularColor(ofColor(255.f));
    light1.enable();
    light1.setAttenuation(100,100,100);
    
    mat.setShininess(150);
    mat.setDiffuseColor(ofColor::blue);
    mat.setSpecularColor(primaryColor);

    specialColor = ofColor(255);
    
    
}

void ParticleScene::update(){

    ofSeedRandom();
    
    ofColor thisColor = pallette.at(floor(ofRandom(pallette.size())));
    
    
    if(spawnRate<=1){
        if(ofRandomf()<spawnRate){
            pBoss.addParticle(new CirclePart(thisColor));
        }
    } else {
        for (int i; i< floor(spawnRate); i++) {
            pBoss.addParticle(new CirclePart(thisColor));
        }
        
    }
    
    
    
    pBoss.update();
    
    //attractive.update();
    //attractive.setPosition(ofGetMouseX(), ofGetMouseY(), 0);
    
}

void ParticleScene::draw(){
    ofBackground(0);
    if(!ofGetLightingEnabled()) ofEnableLighting();
    if (!light1.getIsEnabled()) light1.enable();
    
    //ofDisableLighting();
    
    //light1.draw();
    mat.begin();
    pBoss.draw();
    mat.end();

}

void ParticleScene::addSpecial(){
    pBoss.addParticle(new CirclePart(specialColor));
    
}

void ParticleScene::flashRandom(){
    int idToFlash = ofRandom(pBoss.getParticlesPtr()->size());
    pBoss.getParticlesPtr()->at(idToFlash)->setAge(0) ;
    pBoss.getParticlesPtr()->at(idToFlash)->setColor(255) ;

    cout<< idToFlash<< endl;
    
}
//
//  AmoebaScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 3/30/15.
//
//

#include "AmoebaScene.h"

void AmoebaScene::setup(){
    if (ofIsGLProgrammableRenderer() == false) {
        ofDisableArbTex();
    }
    
    phong.setMethod(ofxShadersFX::Lighting::BLINNPHONG);
    amoeba = ofMesh::cylinder(50, 50);
    

    for (int i=0; i<amoeba.getVertices().size(); i++) {
        ofVec3f noiseVec = ofVec3f(ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10))
        ;
        amoeba.getVertices()[i] += noiseVec;
        del.addPoint(amoeba.getVertices()[i]);
    }
    del.triangulate();

    
    
    light.setup();
    light.setPointLight();
    light.setPosition(300, 300, 0);
    
    phong.setType(ofxShadersFX::VERTEX_SHADER);
    phong.useLight(&light);
    phong.useCamera(&cam);
}

void AmoebaScene::update(){
    
}

void AmoebaScene::draw(){
    cam.begin();


    
    ofBackground(0);

    phong.begin();
    
    ofPushMatrix();
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateY(ofGetFrameNum()*0.1);
    amoeba.draw();
    ofPopMatrix();
    
    phong.end();
    cam.end();
    
}
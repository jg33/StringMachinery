//
//  BoidScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 2/3/15.
//
//

#include "BoidScene.h"

bool killOlds(Boid b){
    return b.willDie;
    
}


void BoidScene::setup(){
    
    ofEnableSmoothing();
    eraseAlpha=150;
}

void BoidScene::update(){
    
    flock.setCohesion(0.7);
    flock.setAlign(1.9);
    flock.setSeparate(5);
    flock.setDrift(1, 2);
    
    flock.update();
    //flock.updateRibbons();

    
    if(ofGetFrameNum()%spawnEveryXFrames==0 && flock.boids.size()<250){
        flock.addRibbon();
        //flock.boids[flock.boids.size()-1];
    }
    
    ofRemove(flock.boids, &killOlds);
    
    /*
    flockMesh.clear();
    for(int i=0; i<flock.boids.size();i++){
        flockMesh.addVertex(flock.boids[i].loc);
        
    }
     */
    
    for(int i=0;i<flock.boids.size();i++){
        flock.boids[i].maxforce = 0.2;
            flock.boids[i].maxspeed = 10;
        
        flock.boids[i].seek(ofVec3f(ofGetMouseX(),ofGetMouseY(),0));
        //flock.boids[i]
    }
    
}

void BoidScene::draw(){
    ofEnableAlphaBlending();
    ofBackground(0, eraseAlpha);
    //ofSetColor(0, eraseAlpha);
    //ofEnableLighting();
    
    
    //ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255,255) ;
    
    
    glPointSize(5);

    glBegin(GL_POINTS);
    
    for(int i=0; i<flock.boids.size();i++){
        float brightness = ofMap(flock.boids[i].age,0,flock.boids[i].life,1,0.);
        //float brightness = 1.0;
        glColor3f(brightness, brightness, brightness);
        glVertex3f(flock.boids[i].loc.x,flock.boids[i].loc.y,flock.boids[i].loc.z);
        
    }
    
    glEnd();
    
    //flock.draw();
    
    /*
    for(int i=0;i<flock.boids.size();i++){
       flock.boids[i].maxspeed = 5;
       flock.boids[i].maxforce = 0.2;
       flock.boids[i].draw();
        
    }
     */
    syphon->publishScreen();
    
}

void BoidScene::exit(){
    
    flock = RibbonFlocking();
}
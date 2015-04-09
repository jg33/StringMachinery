//
//  SingleStringScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/26/14.
//
//

#include "SingleStringScene.h"


void LittleString::setup(){
    ofDisableLighting();
    seed = ofRandom(1000);

    for (int i=0; i< numPoints; i++) {
        float x = sin(i)*radius;
        float y = cos(i)*radius;
        basePoints.push_back(ofPoint(x,y));
    }
    
    twist = 10;
}

void LittleString::update(){
    
    points.clear();
    
        for(int i=0;i<numPoints;i++){
            ofPoint noise = ofPoint(ofNoise(seed+i+ofGetElapsedTimef())*5, ofNoise(seed+i+ofGetElapsedTimef()+1.3)*5 );
            
            ofPoint twister = ofPoint( cos(i*2)*twist , 0 , sin(i*2)*twist );
            points.push_back(basePoints[i] + noise + twister);
            
            
        }
    
    
    line.clear();
    for (int i=0; i< basePoints.size(); i++) {
        
        
        line.curveTo(points[i]);
        
    }
    line.close();
    
    
}

void LittleString::draw(){
    if(isFilling){
        ofSetColor(0,255);

        ofFill();
        ofSetPolyMode(OF_POLY_WINDING_NONZERO);
        ofBeginShape();
        
        for( int i = 0; i < line.getVertices().size(); i++) {
            ofVertex(line.getVertices().at(i).x, line.getVertices().at(i).y);
        }
        ofEndShape();
    }
    ofSetColor(255);
    line.draw();
}

//////// ----- /////////
void SingleStringScene::setup(){
    ofDisableLighting();
    little.setup();
    
}

void SingleStringScene::update(){
    little.update();
    
}

void SingleStringScene::draw(){
    ofBackground(0);
    
    ofSetColor(255);
    ofSetLineWidth(4);
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateX(ofGetElapsedTimef()*10);
    ofRotateY(ofGetElapsedTimef()*13);
    ofRotateZ(ofGetElapsedTimef()*14);

    
    little.draw();
    
}
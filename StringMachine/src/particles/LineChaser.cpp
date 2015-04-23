//
//  LineChaser.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/11/14.
//
//

#include "LineChaser.h"

bool offScreen(ofVec3f v){
    return v.x<-2000;
    
}

void LineChaser::update(){
    
    speed = ofNoise(ofGetElapsedTimef()+seed);
    speed*=speedMult;
    front.x = homebase.x+speed;
    
    displacement*= displaceDecay;
    float verticalDisplacement = displacement* sin(ofGetElapsedTimef()+seed+8292.3);
    front.y = homebase.y + verticalDisplacement;
    
    points.push_back(front);
    
    line.clear();
    for(int i=points.size()-1;i>=0;i--){
        points[i].x -= speed;
        line.curveTo(points[i]);
    }
    
    ofRemove(points, offScreen);
    
}

void LineChaser::draw(){
    ofPushStyle();
    ofSetColor(255);
    ofSetLineWidth(3);
    line.draw();
    
    ofNoFill();
    ofSetCircleResolution(25);
    if(points.size()>0){
        //ofDrawCircle(points[points.size()-1], 5);
    }
    
    ofPopStyle();
    }

void LineChaser::setDisplacement(float d){
    
    displacement =d;
    
}
//
//  ChaoticUnison.h
//  StringMachine
//
//  Created by Jesse Garrison on 4/22/15.
//
//

#ifndef __StringMachine__ChaoticUnison__
#define __StringMachine__ChaoticUnison__

#include <stdio.h>

#include "ofxAppUtils.h"
#include "ofxSyphon.h"


#define NUM_BANDS 8

class Band{
    
    
public:
    Band(){;};
    Band(float rad){
        seed = floor(ofRandom(3393));
        radius = rad;
        for(int i=0;i<128;i++){
            basePoints.push_back(ofVec2f(sin(i*0.05)*radius,cos(i*0.05)*radius));
        }
    
    
    };
    
    void update(){
        rotation += (targetRotation-rotation) * 0.1;
        wiggleAmt *= decay;
        
        points.clear();
        
        for (int i = 0; i< basePoints.size(); i++){
            ofVec2f noisePoint = ofVec2f(
                sin(i*0.05)*ofSignedNoise(seed+ofGetElapsedTimef()+(i*2.3*wiggleFreq)),
                cos(i*0.05)* ofSignedNoise(seed+ofGetElapsedTimef()+i*2.7*wiggleFreq)
            
            );
            noisePoint *= wiggleAmt;
            ofVec2f newPoint;
            
            newPoint = basePoints[i]+noisePoint;
            points.push_back(newPoint);
            
        }
        
        line.clear();
        for(int i=0; i< points.size(); i++){
            //line.curveTo(points[i].x, points[i].y);
            
            line.curveTo(points[i]);
            //ofDrawRectangle(points[i].x, points[i].y, 5, 5);
        }
        line.setClosed(true);
        
        
    }
    
    void draw(){
        
        ofPushMatrix();
        ofRotateZ(rotation);
        
        ofNoFill();
        ofSetColor(255);
        ofSetLineWidth(5);
        line.draw();
        
    }
    
    float wiggleAmt=25;
    float wiggleFreq = 2;
    float targetRotation;
    float rotation;

    
private:
    float radius;
    int seed;
    
    float decay = 0.9;
    
    vector<ofVec2f> points, basePoints;
    
    ofPolyline line;
    
};

class ChaoticUnison: public ofxScene{
    
public:
    ChaoticUnison():ofxScene("Chaotic Unison"){};
    ChaoticUnison(ofxSyphonServer* _syphon):ofxScene("Chaotic Unison"){syphon=_syphon;};
    
    void setup();
    void update();
    void draw();
    void exit(){};
    
    inline void pluck(int band, float amt){
        amt*=25;
        bands[band].wiggleAmt = amt;
        bands[band].targetRotation = bands[band].rotation+amt;
        ;};
    
    
private:
    
    ofVec2f loc;
    vector<Band> bands;
    
    
    ofxSyphonServer * syphon;
    
    
};



#endif /* defined(__StringMachine__ChaoticUnison__) */

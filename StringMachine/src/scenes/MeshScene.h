//
//  MeshScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 5/3/15.
//
//

#ifndef __StringMachine__MeshScene__
#define __StringMachine__MeshScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"

class MeshLine{
public:
    MeshLine();
    MeshLine(ofVec2f l, float w){
        loc =l;
        direction = ofVec2f(
            ofRandom(1,3),
            ofRandom(1,3)
        );
        
        pointOne = loc + (direction*2000);
        pointTwo = loc - (direction*2000);
        
        
        width = w;
        life = ofRandom(100,600 );
    };
    
    
    void update(){
        if(age>life){
            bWillDie = true;
            
        } else{
            age++;
        }
        
    };
    void draw(){
        ofSetColor(255,ofMap(age,0.0001,life,255,0));
        ofSetLineWidth(width);
        ofDrawLine(pointOne,pointTwo);
    };
    
    bool bWillDie = false;

private:
    ofVec2f loc, direction;
    
    ofVec2f pointOne, pointTwo;
    float width;
    
    float age, life;
    
    
};

class MeshScene: public ofxScene{
    
public:
    MeshScene():ofxScene("MeshScene"){};
    MeshScene(ofxSyphonServer * s):ofxScene("MeshScene"){
        syphon = s;
        setup();
    };
    
    void setup();
    void update();
    void draw();
    
    void addLine(float x, float y, float w);
    
private:
    vector<MeshLine> lines;
    ofxSyphonServer * syphon;
};
#endif /* defined(__StringMachine__MeshScene__) */

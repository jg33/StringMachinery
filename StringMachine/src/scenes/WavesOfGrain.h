//
//  WavesOfGrain.h
//  StringMachine
//
//  Created by Jesse Garrison on 4/20/15.
//
//

#ifndef __StringMachine__WavesOfGrain__
#define __StringMachine__WavesOfGrain__

#include <stdio.h>

#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "Particle.h"

class NotePart;
class WaveForm{
public:
    
    static bool isPointOff(ofVec3f v){
        bool bWillDie = false;
        
        if(v.x> 1000 || v.x< -1000) {
            
            bWillDie = true;
        }
        
        return bWillDie;
        
    }
    WaveForm(){
        xStep = 3;
        
    };
    
    void update(){
        values.push_back(currentAmp);
        
        while(values.size() > ofGetWidth()){
            values.erase(values.begin());
            
        }
        
        ofRemove(rightMesh.getVertices(), &WaveForm::isPointOff);
        ofRemove(leftMesh.getVertices(), &WaveForm::isPointOff);
        
        
        /* WORKING IF YOU LIKE CRAP
         leftMesh.clear();
         rightMesh.clear();
         int count = 0;
         for (int i =values.size();i>0;i-- ){
         for(int j =0 ; j< 9 ;j++){
         rightMesh.addVertex(ofVec3f(  xStep *count ,   cos(j)*values[i],sin(j)*50 ));
         //rightMesh.addVertex(ofVec3f(xStep*count, - cos(j)*values[i],sin(j)*50 ));
         }
         
         leftMesh.addVertex(ofVec3f(-xStep*count, values[i],0));
         leftMesh.addVertex(ofVec3f(-xStep*count, -values[i],0));
         count++;
         
         }
         
         
         */
        
        
        for (int i=0;i<rightMesh.getVertices().size();i++){
            ofVec3f newPoint;
            newPoint = rightMesh.getVertices()[i];
            newPoint.x += 5;
            rightMesh.setVertex(i, newPoint);
        }
        
        for (int i=0;i<leftMesh.getVertices().size();i++){
            ofVec3f newPoint;
            newPoint = leftMesh.getVertices()[i];
            newPoint.x -= 5;
            leftMesh.setVertex(i, newPoint);
        }
        
        
        if( ofGetFrameNum() % (int)xStep ==0){
            for(int i =0 ; i< 5 ;i++){
                rightMesh.addVertex(ofVec3f( sin(i*2.2)*10,   cos(i+ofGetFrameNum())*currentAmp, sin(i+ofGetFrameNum())*currentAmp )  );
                leftMesh.addVertex(ofVec3f( -sin(i*2.2)*10,   cos(i+ofGetFrameNum())*currentAmp, sin(i+ofGetFrameNum())*currentAmp )  );
            }
            
        }
        
        
        
    }
    
    void draw(){
        
        rightMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        leftMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        
        leftMesh.drawWireframe();
        rightMesh.drawWireframe();
    }
    
    float currentAmp;
    float xStep;
    
    void clear(){
        rightMesh.clear();
        leftMesh.clear();
    }
    
    
private:
    ofMesh leftMesh, rightMesh;
    
    
    //ofPolyline line;
    
    vector<float> values;
    
    
};




class WavesOfGrain : public ofxScene{
    
public:
    WavesOfGrain():ofxScene("NoteSend"){setup();};
    WavesOfGrain(ofxSyphonServer * _syphon1,ofxSyphonServer * _syphon2): ofxScene("Waves of Grain"){syphon1 = _syphon1;syphon2 = _syphon2; setup();};
    
    void setup();
    void update();
    void draw();
    void exit();

    void addNote(int note, int velocity);
    
    float amp1, amp2, amp3;
    float scale1, scale2, scale3;
    
private:
    ofxSyphonServer * syphon1, *syphon2;
    ofFbo drawer;
    
    ofLight light1;
    
    ofxParticleManager partMan;
    
    WaveForm wave;
    WaveForm wave2, wave3;
};


class NotePart: public Particle{
public:
    NotePart():Particle(){};
    NotePart(int _note, int _velocity);
    
    void customUpdate();
    void draw();
    
private:
    int note, velocity;
    float rotation;
    
    float targetSize;
    
    ofVec3f rotationAxis;
    
    ofMaterial material;
    
};





#endif /* defined(__StringMachine__WavesOfGrain__) */

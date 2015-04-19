//
//  WaveFormScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 4/18/15.
//
//


#ifndef __StringMachine__WaveFormScene__
#define __StringMachine__WaveFormScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "ofxDelaunay.h"



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
    ofxDelaunay deli;
    
    
    //ofPolyline line;
    
    vector<float> values;
    
    
};


class WaveFormScene: public ofxScene{
    
public:
    WaveFormScene():ofxScene("WaveForm"){};
    WaveFormScene(ofxSyphonServer* _syphon):ofxScene("WaveForm"){syphon=_syphon;};
    
    void setup();
    void update();
    void draw();
    void exit();
    
    float amp1, amp2, amp3;
    
    float scale1, scale2, scale3;
    
private:
    ofxSyphonServer * syphon;
    
    WaveForm wave;
    WaveForm wave2, wave3;
    
};

#endif /* defined(__StringMachine__WaveFormScene__) */

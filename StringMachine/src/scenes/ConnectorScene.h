//
//  ConnectorScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/13/14.
//
//

#ifndef __StringMachine__ConnectorScene__
#define __StringMachine__ConnectorScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSvg.h"
#include "SingleStringScene.h"
#include "ofxSyphon.h"

#define MAXSPREAD 25

class Connection{
public:
    Connection(){size = ofRandom(1,3) ;  life=ofRandom(250,750);};
    
    int targetIndex;
    ofVec3f start, current, end;
    float dist, maxDist, maxWidth;
    
    float size, seed;
    
    ofPolyline baseLine, drawnLine;
    ofFbo cache;
    bool isCached;
    
    void update(){
        
        if(!cache.isAllocated()) cache.allocate(ofGetWidth(), ofGetHeight());
        
        if(seed==0) seed= ofRandom(300);

        if(reach<=1 && !isCached ){
            reach+=0.01;
            current = start+ ( (end-start)*reach );
            
            if(baseLine.getVertices().size()==0 && start.length()>0){
                baseLine.addVertex(start);
            } else {
                ofVec3f noise = ofVec3f(ofSignedNoise(seed+ofGetElapsedTimef()*(4-size)),ofSignedNoise(seed+ofGetElapsedTimef()*(4-size)+33)), ofSignedNoise(seed+ofGetElapsedTimef()*(4-size)+78) ;
                noise*=10;
                baseLine.curveTo(current+noise);
                baseLine.simplify();
            }
            
        }
        drawnLine = baseLine;
        
        if(age>life){
            willDie = true;
            
        } else {
            age++;
        }
        
        /*
        drawnLine.clear();
        for(int i =0; i< baseLine.getVertices().size();i++){
            ofVec3f noise = ofVec3f(seed+ofSignedNoise(ofGetElapsedTimef()+(i*10)),ofSignedNoise(seed+ofGetElapsedTimef()+(i*10)+33)), ofSignedNoise(seed+ofGetElapsedTimef()+(i*10)+78) ;
            
            //drawnLine.curveTo(baseLine.getVertices().at(i)+noise);
        }
        //drawnLine.simplify();
        */

        

    
    }
    
    
    void spreadZ(float amt){
        for (int i=0;i<drawnLine.getVertices().size();i++){
            
            drawnLine.getVertices()[i].z = baseLine.getVertices()[i].z * ofMap(amt, 0, 1, 1, randSpread);;
        }
        
    }
    
    void draw(){
        
        ofPushStyle();
        //float width = ofMap(dist,0,maxDist,maxWidth,0);
        ofSetLineWidth(size);
        ofSetColor( ofMap(age,0,life,255,0) );
        /*
        if(isCached){
            cache.draw(0,0);
        } else if (reach >=1 && !isCached){
            cache.begin();
            baseLine.draw();
            cache.end();
            isCached = true;
        } else{
            baseLine.draw();
            
        }*/
        drawnLine.draw();
        ofPopStyle();
    };
    
    
    bool willDie;
    
private:
    float reach;
    
    float randSpread = ofRandom(1,5);
    
    //int toDie;

    
    float age, life;
    
    
};

class ConnectionPoint: public ofVec3f{
    
    public:
        ConnectionPoint():ofVec3f(){stringy.setup();stringy.setup(ofRandom(10,30));};
        ConnectionPoint(ofVec3f v ){
            x = v.x;
            y=  v.y;
            baseZ=  ofRandom(-10,10);
            z= baseZ;
            stringy.setup(ofRandom(10,30));
            
        };
        inline void setOthers(vector<ConnectionPoint> * _others){others=_others;findNeighbors();};

        bool isActive = false;
        vector<ConnectionPoint * > neighbors;
        inline void update(){stringy.update();}
        inline void draw(){stringy.draw();};
        inline void setTwist(float _twist){ stringy.twist= _twist;};
        inline void setFilling(bool _fill){ stringy.isFilling = _fill;};
    
        inline void spreadZ(float amt){z = baseZ*ofMap(amt, 0, 1, 1, MAXSPREAD);};
        float baseZ;
    
    private:
        vector<ConnectionPoint> * others;
    
        inline void findNeighbors(){
            for (int i=0;i< others->size();i++){
                if(distance(others->at(i))<500 && distance(others->at(i)) >1 && others->at(i).length()>5 ){
                    
                    neighbors.push_back( &others->at(i) );
                }
            }
        }
    
    LittleString stringy;
    
    

};

class ConnectorScene : public ofxScene{
    
public:
    ConnectorScene():ofxScene("Connections"){setSingleSetup(false);};
    ConnectorScene(ofxSyphonServer * _syphon):ofxScene("Connections"){syphon = _syphon; setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
    void inline setPoints(map<int,ofVec3f> * _points){points = _points;};
    void inline setPointPower(map<int,float>* _powers){
        pointPower= _powers;};
    
    void startGrowth();
    void growMore();
    
    bool bWillGrow = false;
    
    inline void pushIn(float amt){
        cam.setPosition(ofGetWidth()/2, ofGetHeight()/2, ofMap(amt, 0, 1, 300, 0)   ) ;
        for(int i =0;i<newPoints.size();i++){
            newPoints[i].spreadZ(amt);
            
        }
        for(int i =0;i<connections.size();i++){
            connections[i].spreadZ(amt);
            
        }
    
    };
    
private:
    int connectionDistance =200;
    int maxLineWidth = 10;
    
    map<int,ofVec3f> * points;
    map<int,float> * pointPower;
    vector<Connection> connections;
    
    ofxSVG image;
    vector<ConnectionPoint> newPoints;
    
    ofEasyCam cam;
    
    ofxSyphonServer * syphon;
};
#endif /* defined(__StringMachine__ConnectorScene__) */

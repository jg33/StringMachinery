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


class Connection{
public:
    Connection(){size = ofRandom(1,3) ; };
    
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
        
        
        /*
        drawnLine.clear();
        for(int i =0; i< baseLine.getVertices().size();i++){
            ofVec3f noise = ofVec3f(seed+ofSignedNoise(ofGetElapsedTimef()+(i*10)),ofSignedNoise(seed+ofGetElapsedTimef()+(i*10)+33)), ofSignedNoise(seed+ofGetElapsedTimef()+(i*10)+78) ;
            
            //drawnLine.curveTo(baseLine.getVertices().at(i)+noise);
        }
        //drawnLine.simplify();
        */

        

    
    }
    void draw(){
        
        ofPushStyle();
        //float width = ofMap(dist,0,maxDist,maxWidth,0);
        ofSetLineWidth(size);
        
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
        baseLine.draw();
        ofPopStyle();
    };
    
private:
    float reach;
    
};

class ConnectionPoint: public ofVec3f{
    
    public:
        ConnectionPoint():ofVec3f(){stringy.setup();stringy.setup(ofRandom(10,30));};
        ConnectionPoint(ofVec3f v ){
            x = v.x;
            y=  v.y;
            z=  v.z;
            stringy.setup(ofRandom(10,30));
            
        };
        inline void setOthers(vector<ConnectionPoint> * _others){others=_others;findNeighbors();};

        bool isActive = false;
        vector<ConnectionPoint * > neighbors;
        inline void update(){stringy.update();}
        inline void draw(){stringy.draw();};
    
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
    void setup();
    void update();
    void draw();
    
    void inline setPoints(map<int,ofVec3f> * _points){points = _points;};
    void inline setPointPower(map<int,float>* _powers){
        pointPower= _powers;};
    
    void startGrowth();
    void growMore();
    
private:
    int connectionDistance =200;
    int maxLineWidth = 10;
    
    map<int,ofVec3f> * points;
    map<int,float> * pointPower;
    vector<Connection> connections;
    
    ofxSVG image;
    vector<ConnectionPoint> newPoints;
    
    
};
#endif /* defined(__StringMachine__ConnectorScene__) */

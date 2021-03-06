//
//  BoidScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 2/3/15.
//
//

#ifndef __StringMachine__BoidScene__
#define __StringMachine__BoidScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxFlocking.h"
#include "ofxSyphon.h"
#include "ofxLeapMotion.h"

class Ribbon: public Boid{
    
public: 
    Ribbon(): Boid(){};
    /*
    explicit operator Boid() {
        Boid converted;
        converted.loc=loc;
        converted.vel=vel;
        converted.acc=acc;
        
        return converted;
    };
     */
    void setup(){
        
        vel = ofVec3f(ofRandomf(), ofRandomf(),ofRandomf());
        vel *= 5;
        
        //bIsSetup = true;
    
    }
    
    void updateRibbon(){
        
        //if (vel.length()<=3) setup();
        
        if(loc.distance(previousLocations[0])>1){
            previousLocations.push_front(loc);
        }
        
        if(previousLocations.size()>length){
            previousLocations.pop_back();
        }
        
        theLine.clear();
        //theLine.lineTo(previousLocations[0]);
        for(int i=1;i<previousLocations.size();i++){
            //if(previousLocations[i].distance(theLine.po))
           // theLine.curveTo(previousLocations[i]);
        }
        theLine.simplify(0.3);

        
        mesh.clear();
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        for(unsigned int i = 1; i < previousLocations.size(); i++){
            
            //find this point and the next point
            ofVec3f thisPoint = previousLocations[i-1];
            ofVec3f nextPoint = previousLocations[i];
            
            //get the direction from one to the next.
            //the ribbon should fan out from this direction
            ofVec3f direction = (nextPoint - thisPoint);
            
            //get the distance from one point to the next
            float distance = direction.length();
            
            //get the normalized direction. normalized vectors always have a length of one
            //and are really useful for representing directions as opposed to something with length
            ofVec3f unitDirection = direction.getNormalized();
            
            //find both directions to the left and to the right
            ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
            ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
            
            //use the map function to determine the distance.
            //the longer the distance, the narrower the line.
            //this makes it look a bit like brush strokes
            float thickness = width;
            
            //calculate the points to the left and to the right
            //by extending the current point in the direction of left/right by the length
            ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
            ofVec3f rightPoint = thisPoint+toTheRight*thickness;
            
            //add these points to the triangle strip
            mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
            mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
        }
        
    };
    
    void draw(){
        ofNoFill();
        ofSetColor(255);
        ofSetLineWidth(width);
        ofSetCurveResolution(10);
        
        //do the same thing from the first example...
        
        
        //end the shape
        //mesh.draw();
        ofDrawCircle(loc, 1);
        //theLine.draw();

    };
    
    deque<ofPoint> previousLocations;
private:
    ofPolyline theLine;
    int length= ofRandom(20,300);
    int width = ofRandom(6,10);
    
    ofMesh mesh;

    //bool bIsSetup = false;
    
};

class RibbonFlocking: public ofxFlocking{
public:
    RibbonFlocking():ofxFlocking(){};
    //vector<Ribbon> ribbons;
    
    void addRibbon(){
        boids.push_back(Ribbon());
        //boids.push_back(Boid());
    }
    void updateRibbons(){
        /*
        vector<Boid> converted;
        for(int i=0;i<boids.size();i++){
            converted.push_back(boids[i]);
        }
         */
        for(int i=0;i<boids.size();i++){
            boids[i].update(boids);

            //boids[i].update(converted);
            //boids[i].updateRibbon();
        }
    }
private:
    
};


class BoidScene: public ofxScene{
    
public:
    BoidScene():ofxScene("BoidScene"){setSingleSetup(true);};    BoidScene(ofxSyphonServer* _syphon):ofxScene("BoidScene"){syphon = _syphon ,setSingleSetup(true);};

    void setup();
    void update();
    void draw();
    
    void exit();
    
    int spawnEveryXFrames = 1;
    
    inline void setSeparate(float amt){flock.setSeparate(amt);};
    inline void setCohesion(float amt){flock.setCohesion(amt);};
    inline void setAlign(float amt){flock.setAlign(amt);};
    inline void setDrift(float freq, float amt){flock.setDrift(freq, amt);};
private:
    
    
    RibbonFlocking flock;
    
    float eraseAlpha;
    
    ofxSyphonServer * syphon;
    
    ofMesh flockMesh;
    ofLight light;
    ofMaterial mat;
    
    ofxLeapMotion leap;
};





#endif /* defined(__StringMachine__BoidScene__) */

//
//  VennScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 11/12/14.
//
//

#ifndef __StringMachine__VennScene__
#define __StringMachine__VennScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"

enum vennSide{
    LEFT,
    RIGHT,
    TOP
};

class VennCircle{
public:
    VennCircle(){};
    VennCircle(vennSide _side);

    
    void setup();
    void update();
    void draw();
    
    inline vector<ofVec3f> getPoints(){return currentPoints;};
    inline ofVec2f getLoc(){return loc;};
    inline void setLoc(ofVec2f v){loc=v;};
    inline void setDisplace(float d){displacement = d;};
    inline void setRadius(float r){ radius=r;};

    inline float getRadius(){return radius;};
    inline void setWiggle(float amt){wiggleFreq = amt;};
    
private:
    vennSide side;
    
    
    ofVec2f loc;
    float radius = ofRandom(150,300);
    float displacement = 0.25;
    
    int circleResolution = 15;
    
    vector<ofVec3f> basePoints, currentPoints;
    float wiggleAmp = ofRandom(20,30);
    float wiggleFreq = ofRandom(0.5,2);
    
    ofPolyline line;
    
    int seed = ofRandom(10000);
    
};


class VennScene : public ofxScene{
    
public:
    VennScene():ofxScene("Venn"){};
    VennScene(ofxSyphonServer* _syphon):ofxScene("Venn"){syphon=_syphon;};
    
    
    void setup();
    void draw();
    void update();
    
    void setLocs(vector<float> _inputs){};
    
    float leftDisplace=1;
    float rightDisplace=1;
    
    inline float setSize(int i, float amt){
        
        amt = ofMap(amt, 0.00001,1, 0, 250);
        circles[i].setRadius(amt);
    
    }
    inline void setDisplace(int i, float amt){circles[i].setDisplace(amt);};
    inline void setWiggle(int i, float amt){circles[i].setWiggle(amt);};
    inline void setRotationSpeed(float amt){};
    
private:
    ofxSyphonServer * syphon;
    
    vector<VennCircle>  circles;
    ofPath overlapShape;
    
    ofMesh testMesh;
    
    void calcOverlap(VennCircle a, VennCircle b);
    void calcOverlap(VennCircle a, VennCircle b, VennCircle c);

    
    float rotation;
    float rotationSpeed = 1;
    
    vector<ofPoint> getConvexHull(vector<ofPoint> points);
    ofPoint h1,h2,h3;
};


#endif /* defined(__StringMachine__VennScene__) */

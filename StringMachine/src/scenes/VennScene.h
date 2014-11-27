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
    RIGHT
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
    inline float getRadius(){return radius;};
    
    
private:
    vennSide side;
    
    
    ofVec2f loc;
    float radius = 150;
    float displacement = 100;
    
    int circleResolution = 15;
    
    vector<ofVec3f> basePoints, currentPoints;

    
    ofPolyline line;
    
};


class VennScene : public ofxScene{
    
public:
    VennScene():ofxScene("Venn"){};
    VennScene(ofxSyphonServer* _syphon):ofxScene("Venn"){syphon=_syphon;};
    
    
    void setup();
    void draw();
    void update();
    
    void setLocs(vector<float> _inputs){};
    
    
private:
    ofxSyphonServer * syphon;
    
    VennCircle left, right;
    ofPath overlapShape;
    
    ofMesh testMesh;
    
    void calcOverlap(VennCircle a, VennCircle b);
    
    float rotation;
    float rotationSpeed = 1;
    
    vector<ofPoint> getConvexHull(vector<ofPoint> points);
    ofPoint h1,h2,h3;
};


#endif /* defined(__StringMachine__VennScene__) */

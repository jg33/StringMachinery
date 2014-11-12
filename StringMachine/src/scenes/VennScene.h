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
    
    
private:
    vennSide side;
    
    
    ofVec2f loc;
    float radius = 150;
    float displacement = 100;
    

    
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
    
    void calcOverlap(VennCircle a, VennCircle b);
    
    float rotation;
    float rotationSpeed = 1;
    
};


#endif /* defined(__StringMachine__VennScene__) */

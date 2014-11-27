//
//  LineChaseScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 11/11/14.
//
//

#ifndef __StringMachine__LineChaseScene__
#define __StringMachine__LineChaseScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"

#include "LineChaser.h"

#define NUM_LINES 4

class LineChaseScene : public ofxScene{
    
public:
    LineChaseScene():ofxScene("LineChase"){};
    LineChaseScene(ofxSyphonServer* _syphon):ofxScene("LineChase"){syphon=_syphon;};

    
    void setup();
    void draw();
    void update();
    
    void setLineDisp(int i, float d);
    
private:
    ofxSyphonServer * syphon;
    
    vector <LineChaser> lines;
    
    
};


#endif /* defined(__StringMachine__LineChaseScene__) */

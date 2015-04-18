//
//  FlickerScreen.h
//  StringMachine
//
//  Created by Jesse Garrison on 4/18/15.
//
//

#ifndef __StringMachine__FlickerScreen__
#define __StringMachine__FlickerScreen__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"


class FlickerScreen: public ofxScene{
    
public:
    FlickerScreen():ofxScene("Flicker"){};
    FlickerScreen(ofxSyphonServer* _syphon):ofxScene("Flicker"){syphon=_syphon;};
    
    void setup();
    void update();
    void draw();
    
    float brightness;
    
private:
    ofxSyphonServer * syphon;

    
};


#endif /* defined(__StringMachine__FlickerScreen__) */

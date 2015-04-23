//
//  FragmentScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 11/5/14.
//
//

#ifndef __StringMachine__FragmentScene__
#define __StringMachine__FragmentScene__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAppUtils.h"
#include "ofxSvg.h"
#include "Fragment.h"
#include "ofxSyphon.h"


class FragmentScene : public ofxScene{
    
public:
    FragmentScene():ofxScene("Fragments"){setSingleSetup(false);};
    FragmentScene(ofxSyphonServer* _syphon):ofxScene("Fragments"){syphon = _syphon; setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
    void fireRandom();
    void fireRandom(float size);
    
private:
    vector<Fragment> fragments;
    ofxSVG image;
    ofxSyphonServer * syphon;
    
};

#endif /* defined(__StringMachine__FragmentScene__) */

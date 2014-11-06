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
#include "Fragment.h"

#define NUM_FRAGMENTS 50

class FragmentScene : public ofxScene{
    
public:
    FragmentScene():ofxScene("Fragments"){setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
    void fireRandom();
    void fireRandom(int size);
    
private:
    vector<Fragment> fragments;
    
};

#endif /* defined(__StringMachine__FragmentScene__) */

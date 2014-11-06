//
//  Fragment.h
//  StringMachine
//
//  Created by Jesse Garrison on 11/5/14.
//
//

#ifndef __StringMachine__Fragment__
#define __StringMachine__Fragment__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAppUtils.h"


class Fragment{
    
public:
    Fragment(){setup();};
    
    void setup();
    void update();
    void draw();
    
    void fire(int level);
    inline void setDecay(float _decay){decay = _decay;};
    
private:
    
    ofVec3f loc;
    
    float brightness;
    float decay;
    
    //ofxTimer timer;
    
};


#endif /* defined(__StringMachine__Fragment__) */

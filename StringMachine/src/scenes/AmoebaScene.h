//
//  AmoebaScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 3/30/15.
//
//

#ifndef __StringMachine__AmoebaScene__
#define __StringMachine__AmoebaScene__

#include <stdio.h>
#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "ofxShadersFX.h"
#include "ofxDelaunay.h"

class AmoebaScene : public ofxScene{
    
public:
    AmoebaScene():ofxScene("Amoeba"){setSingleSetup(false);};
    AmoebaScene(ofxSyphonServer* _syphon):ofxScene("Amoeba"){syphon = _syphon; setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
private:
    ofxSyphonServer * syphon;
    ofMesh amoeba;
    ofxDelaunay del;

    
    ofxShadersFX::Lighting::LightingShader phong;
    ofLight light;
    ofEasyCam cam;
};

#endif /* defined(__StringMachine__AmoebaScene__) */

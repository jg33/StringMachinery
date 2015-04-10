//
//  ParticleScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 10/7/14.
//
//

#ifndef __StringMachine__ParticleScene__
#define __StringMachine__ParticleScene__

#include <iostream>
#include "ofxAppUtils.h"
#include "CirclePart.h"
#include "Attractor.h"
#include "ofxColourTheory.h"

class ParticleScene : public ofxScene{
    
public:
    ParticleScene():ofxScene("Particles"){setSingleSetup(false);};
    void setup();
    void update();
    void draw();
    
    Attractor attractive;
    
    float spawnRate = 1;
    
    void flashRandom();
    void addSpecial();
private:
    
    ofxParticleManager pBoss;
    ofLight light1;
    ofMaterial mat;
    ofxColourTheory colorMaker;
    vector<ofColor> pallette;
    
    ofColor specialColor;
};


#endif /* defined(__StringMachine__ParticleScene__) */

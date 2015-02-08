//
//  noteSendScene.h
//  StringMachine
//
//  Created by Jesse Garrison on 11/26/14.
//
//

#ifndef __StringMachine__NoteSendScene__
#define __StringMachine__NoteSendScene__

#include <stdio.h>

#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "Particle.h"

class NotePart;

class NoteSendScene : public ofxScene{
    
public:
    NoteSendScene():ofxScene("NoteSend"){setup();};
    NoteSendScene(ofxSyphonServer * _syphon): ofxScene("NoteSend"){syphon = _syphon;setup();};
    
    
    void setup();
    void update();
    void draw();
    
    void addNote(int note, int velocity);
    
private:
    
    ofLight light1;
    
    ofxSyphonServer * syphon;
    ofxParticleManager partMan;
};


class NotePart: public Particle{
public:
    NotePart():Particle(){};
    NotePart(int _note, int _velocity);
    
    void customUpdate();
    void draw();
    
private:
    int note, velocity;
    float rotation;
    
    float targetSize;
    
    ofVec3f rotationAxis;
    
    ofMaterial material;
    
};


#endif /* defined(__StringMachine__noteSendScene__) */

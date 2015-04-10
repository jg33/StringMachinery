#pragma once

#include "ofMain.h"
#include "ofxAppUtils.h"
#include "ofxSyphon.h"
#include "ofxOsc.h"

#include "Scenes.h"

#define NUM_MICS 4

class CircleScene;
class ConnectorScene;
class RiceScene;
class FragmentScene;
class LineChaseScene;
class VennScene;
class NoteSendScene;
class SingleStringScene;
class WaveScene;
class ParticleScene;
class PulseScene;

class ofApp : public ofxApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void onGuiEvent(guiCallbackData & d);
    

private:
    ofxSyphonServer syphonServe;
    ofxOscReceiver oscIn;
    
    ofxSceneManager sceneManager;
    CircleScene * circles;
    ConnectorScene * connections;
    RiceScene * rice;
    FragmentScene * fragments;
    LineChaseScene * lineChase;
    VennScene * venn;
    NoteSendScene * noteSend;
    SingleStringScene * single;
    WaveScene * waves;
    PulseScene * pulse;
    ParticleScene * particles;
    
    vector<float> micInputs;
    map<int,ofVec3f> dancers;
    map<int,ofVec3f> POIs;
    map<int,float> POIpower;
    
};

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    syphon1.setName("String Machine 1");
    syphon2.setName("String Machine 2");
    syphon3.setName("String Machine 3");


    oscIn.setup(6666);
    ofSetVerticalSync(false);
    ofSetSmoothLighting(true);
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(false);
    ofSetFrameRate(50);
    
    //circles = (CircleScene*) sceneManager.add(new CircleScene());
    connections = (ConnectorScene*) sceneManager.add(new ConnectorScene(&syphon1));
    particles = (ParticleScene*) sceneManager.add(new ParticleScene());
    rice = (RiceScene*)sceneManager.add(new RiceScene(&syphon1));
    fragments = (FragmentScene*)sceneManager.add(new FragmentScene(&syphon1));
    lineChase = (LineChaseScene*)sceneManager.add(new LineChaseScene(&syphon1, &syphon2));
    venn = (VennScene*)sceneManager.add(new VennScene(&syphon1));
    //noteSend = (NoteSendScene*)sceneManager.add(new NoteSendScene(&syphon1));
    single = (SingleStringScene*)sceneManager.add(new SingleStringScene(&syphon1));
    //waves = (WaveScene*)sceneManager.add(new WaveScene(&syphon1));
    //sceneManager.add(new BoidScene(&syphon1));
    //sceneManager.add(new AmoebaScene(&syphon1));
    pulse = (PulseScene*) sceneManager.add(new PulseScene(&syphon1));
    //rings = (RingScene*) sceneManager.add(new RingScene(&syphon1));
    flicker = (FlickerScreen*) sceneManager.add(new FlickerScreen(&syphon1));
    //waveform = (WaveFormScene*) sceneManager.add(new WaveFormScene(&syphon1));
    bigDrums = (BigDrums*) sceneManager.add(new BigDrums(&syphon1, &syphon2, &syphon3));
    grain = (WavesOfGrain*) sceneManager.add(new WavesOfGrain(&syphon1, &syphon2));
    chaos = (ChaoticUnison*) sceneManager.add(new ChaoticUnison(&syphon1));
    
    sceneManager.setup(true);
    //ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE);
    setSceneManager(&sceneManager);
    sceneManager.gotoScene("WaveForm", true);

    
    ////CONTROL PANEL//////
    addTransformControls();
    setDrawControlPanel(false);
    setDrawFramerate(true);
    
    
    controlPanel.addPanel("Extras", 1);
    controlPanel.setWhichPanel("Extras");
    controlPanel.addSlider2D("POI0", "POI0", ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth(), 0, ofGetHeight(), false);
    controlPanel.addSlider2D("POI1", "POI1", ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth(), 0, ofGetHeight(), false);
    controlPanel.addSlider2D("POI2", "POI2", ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth(), 0, ofGetHeight(), false);
    controlPanel.addSlider2D("POI3", "POI3", ofGetWidth()/2, ofGetHeight()/2, 0, ofGetWidth(), 0, ofGetHeight(), false);
    
    controlPanel.addPanel("Rice", 1);
    controlPanel.setWhichPanel("Rice");
    controlPanel.addSlider2D("Wind", "wind", 0, 0, -0.001, 0.001, -0.001, 0.001, false);
    
    controlPanel.addPanel("Pulse", 1);
    controlPanel.setWhichPanel("Pulse");
    controlPanel.addSlider("Speed", "pulseSpeed", 1, 0, 5, false);
    controlPanel.addSlider("Max Brightness", "maxPulseBright", 150, 0, 255, true);
    
    controlPanel.setupEvents();
    controlPanel.enableEvents();
    ofAddListener(controlPanel.guiEvent, this, &ofApp::onGuiEvent);
    
    //////SCENE SPECIFICS/////////
    //connections->setPoints(&POIs);
    //connections->setPointPower(&POIpower);
    
    /*
    for(int i=0;i<50;i++){
        POIs[i] = ofVec3f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
        POIpower[i] = ofRandom(1);
    }
     */
    for(int i =0; i<NUM_MICS;i++){
        micInputs.push_back(10);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofxOscMessage msg;
    
    while (oscIn.hasWaitingMessages()){
        oscIn.getNextMessage(&msg);
        vector<string> address = ofSplitString(msg.getAddress(),"/");
        
        //cout<< address[1]<<" " <<msg.getArgAsFloat(0)<<endl;
        
        if(address[1] == "lineWiggle"){
            //micInputs[ofToInt(address[2])]= msg.getArgAsFloat(0);
            lineChase->setLineDisp(ofToInt(address[2]), msg.getArgAsFloat(0));
            
        } else if(address[1] == "lineIntensity"){
            float speed = ofMap(msg.getArgAsFloat(0), 0, 1, 50, 1000);
            float home = ofMap(msg.getArgAsFloat(0), 0, 1, 500, 1200);
            lineChase->setSpeed(speed);
            lineChase->setHome(home);

        } else if(address[1] == "lines" && address[2] == "start"){
            lineChase->startLines();

        } else if(address[1] == "lines" && address[2] == "clear"){
            
            lineChase->clearLines();
            
        }
        
        
        else if (address[1] == "fragmentBonk"){
            fragments->fireRandom( msg.getArgAsFloat(0));
            bigDrums->fireRandom( msg.getArgAsFloat(0));
            
        } else if( address[1] == "woodBonk"){
            lineChase->fire( msg.getArgAsFloat(0), msg.getArgAsFloat(1));

            
        }else if( address[1] == "connectionBonk"){
            connections->bWillGrow = true;
            
            
        }else if (address[1] == "venn" && address[3] == "displace"){
            venn->setDisplace(ofToInt(address[2]), msg.getArgAsFloat(0) ) ;

            
        }else if (address[1] == "venn" && address[3] == "wiggle"){
            venn->setWiggle(ofToInt(address[2]), msg.getArgAsFloat(0)) ;
            
            
        } else if (address[1] == "venn" && address[3] == "size"){
            venn->setSize(ofToInt(address[2]), msg.getArgAsFloat(0)) ;
            
            
        } else if (address[1] == "venn" && address[3] == "rotation"){
            venn->setRotationSpeed(msg.getArgAsFloat(0));
        
        } else if (address[1] == "drum" && address[3] == "amp"){
            bigDrums->setSize(ofToInt(address[2]), msg.getArgAsFloat(0) );
        } else if (address[1] == "drum" && address[3] == "bonk"){
            bigDrums->bonkRing(msg.getArgAsFloat(0) );
        } else if (address[1] == "swellAmp"){
            pulse->setMaxBrightness(msg.getArgAsFloat(0));
        } else if (address[1] == "particles" && address[2] == "bonk"){
            particles->addSpecial();
        } else if (address[1] == "flicker"){
            flicker->setBright(msg.getArgAsFloat(0));
            //cout<<"flick"<<endl;
        } else if (address[1] == "waveNote"){
            grain->addNote(msg.getArgAsInt32(0) , msg.getArgAsInt32(1));
            
        } else if (address[1] == "pulse" && address[2] == "brightness"){
            pulse->setMaxBrightness(msg.getArgAsFloat(0));
            
        } else if (address[1] == "pulse" && address[2] == "speed"){
            pulse->setSpeed(msg.getArgAsFloat(0));
            
        }
        else if (address[1] == "waveAmp"){
            switch (ofToInt(address[2])) {
                    
                case 0:
                    grain->amp1 = msg.getArgAsFloat(0);
                    break;
                    
                case 1:
                    grain->amp2 = msg.getArgAsFloat(0);
                    break;
                   
                case 2:
                    grain->amp3 = msg.getArgAsFloat(0);
                    break;
                    
                default:
                    break;
            }
            flicker->brightness = ofToFloat(address[0]);
        } else if(address[1] == "chaos" ){
            chaos->pluck(ofToInt(address[2]), msg.getArgAsFloat(0));
            
        }else if(address[1] == "scene"){
            switch (msg.getArgAsInt32(0)) {
                case 0:
                    sceneManager.gotoScene("Flicker");

                    break;
                case 1:
                    sceneManager.gotoScene("Pulse");

                    break;
                    
                case 2:
                    sceneManager.gotoScene("Connections");
                    break;
                    
                case 3:
                    sceneManager.gotoScene("Metal and Wood");

                    break;
                    
                case 4:
                    sceneManager.gotoScene("Venn");
                    break;
                    
                case 5:
                    sceneManager.gotoScene("Big Drums");

                    break;
                    
                case 6:
                    sceneManager.gotoScene("Waves of Grain");

                    break;
                    
                case 7:
                    sceneManager.gotoScene("Rice");

                    break;
                    
                case 8:
                    sceneManager.gotoScene("Chaotic Unison");
                default:
                    break;
            }
            
            
            
        } else if (address[1] =="nextScene"){
            sceneManager.nextScene();
            
        }else if (address[1] =="prevScene"){
            sceneManager.prevScene();
            
        }
        
        else if (address[1] == "wind"){
            rice->setWind(ofVec3f(msg.getArgAsFloat(0), msg.getArgAsFloat(1)));
            
        }
        
    }
    
    
    
    //connections->setPoints(&POIs);
    ofSetWindowTitle(sceneManager.getCurrentSceneName()+" @ "+ ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    popTransforms();
    ofPopStyle();
    
    
    //drawFramerate(10, 10);
    
    //syphon2.publishScreen();
    
    if(bDebug){
        ofFill();
        ofSetColor(255);
        ofSetLineWidth(2);
        ofDisableLighting();
        drawControlPanel();
    }

}

void ofApp::onGuiEvent(guiCallbackData & d){
    if (ofIsStringInString(d.getXmlName(), "POI")){
        vector <string> poiNum = ofSplitString(d.getXmlName(), "I");
        POIs[ofFromString<int>(poiNum[1])] = ofVec3f(d.getFloat(0),d.getFloat(1));
        cout<< "set POI!"<<endl;
    } else if(d.getXmlName() =="wind"){
        rice->setWind (ofVec3f(d.getFloat(0),d.getFloat(1)));
    } else if(d.getXmlName() == "pulseSpeed"){
        pulse->setSpeed(d.getFloat(0));
    } else if(d.getXmlName() == "maxPulseBright"){
        pulse->setMaxBrightness(d.getFloat(0));
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
            case 'd':
            bDebug = !bDebug;
            break;
            case '[':
            sceneManager.prevScene();
            break;
            case ']':
            sceneManager.nextScene();
            break;
            case 'm':
            grain->addNote((int)ofRandom(127), (int)ofRandom(127));
            break;
            case 'g':
            connections->startGrowth();
            break;
            case 'r':
            bigDrums->bonkRing(ofRandom(30));
            break;

    }
    if(key == ' '){
        fragments->fireRandom();
        bigDrums->fireRandom();
        lineChase->fireRandom();


    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    setNewScreenSize(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

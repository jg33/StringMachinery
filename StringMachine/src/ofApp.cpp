#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    syphonServe.setName("String Machine");
    oscIn.setup(6666);
    ofSetVerticalSync(true);
    ofSetSmoothLighting(true);
    
    circles = (CircleScene*) sceneManager.add(new CircleScene());
    connections = (ConnectorScene*) sceneManager.add(new ConnectorScene());
    sceneManager.add(new ParticleScene());
    rice = (RiceScene*)sceneManager.add(new RiceScene());
    fragments = (FragmentScene*)sceneManager.add(new FragmentScene(&syphonServe));
    lineChase = (LineChaseScene*)sceneManager.add(new LineChaseScene(&syphonServe));
    venn = (VennScene*)sceneManager.add(new VennScene(&syphonServe));
    noteSend = (NoteSendScene*)sceneManager.add(new NoteSendScene(&syphonServe));
    single = (SingleStringScene*)sceneManager.add(new SingleStringScene(&syphonServe));
    waves = (WaveScene*)sceneManager.add(new WaveScene(&syphonServe));
    
    
    sceneManager.setup(true);
    ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE);
    setSceneManager(&sceneManager);
    sceneManager.gotoScene("Waves", true);


    
    ////CONTROL PANEL//////
    addTransformControls();
    setDrawControlPanel(true);
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
    
    controlPanel.setupEvents();
    controlPanel.enableEvents();
    ofAddListener(controlPanel.guiEvent, this, &ofApp::onGuiEvent);
    
    //////SCENE SPECIFICS/////////
    connections->setPoints(&POIs);
    connections->setPointPower(&POIpower);
    
    for(int i=0;i<50;i++){
        POIs[i] = ofVec3f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
        POIpower[i] = ofRandom(1);
    }

    for(int i =0; i<NUM_MICS;i++){
        micInputs.push_back(0);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofxOscMessage msg;
    
    while (oscIn.hasWaitingMessages()){
        oscIn.getNextMessage(&msg);
        vector<string> address = ofSplitString(msg.getAddress(),"/");

        if(address[1] == "mic"){
            micInputs[ofToInt(address[2])]= msg.getArgAsFloat(0);
            lineChase->setLineDisp(ofToInt(address[2]), msg.getArgAsFloat(0));
            
        } else if ( address[1] == "dancer"){
            dancers[ofToInt(address[2])] = ofVec3f(msg.getArgAsFloat(0),msg.getArgAsFloat(1),msg.getArgAsFloat(2));
        } else if (address[1] == "POI" && address[3] == "pos"){
            POIs[ofFromString<int>(address[2])] = ofVec3f(msg.getArgAsFloat(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
            
        } else if(address[1] == "POI" && address[3] == "power"){
            POIpower[ofFromString<int>(address[2])] = msg.getArgAsFloat(0);
        }
        
    }
    
    
    
    circles->setSizes(micInputs);
    //connections->setPoints(&POIs);
    ofSetWindowTitle(sceneManager.getCurrentSceneName()+" @ "+ ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    popTransforms();
    
    
    //drawControlPanel();
    //drawFramerate(10, 10);
}

void ofApp::onGuiEvent(guiCallbackData & d){
    if (ofIsStringInString(d.getXmlName(), "POI")){
        vector <string> poiNum = ofSplitString(d.getXmlName(), "I");
        POIs[ofFromString<int>(poiNum[1])] = ofVec3f(d.getFloat(0),d.getFloat(1));
        cout<< "set POI!"<<endl;
    } else if(d.getXmlName() =="wind"){
        rice->setWind (ofVec3f(d.getFloat(0),d.getFloat(1)));
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
            noteSend->addNote((int)ofRandom(127), (int)ofRandom(127));
            break;

    }
    if(key == ' '){
        fragments->fireRandom();
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

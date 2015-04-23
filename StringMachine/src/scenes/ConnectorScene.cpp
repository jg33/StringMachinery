//
//  ConnectorScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 10/13/14.
//
//

#include "ConnectorScene.h"

void ConnectorScene::setup(){
    ofDisableLighting();
    
    image.load("apr12_map_v3.svg");
    connections.clear();
    newPoints.clear();
    
    for(int i=1 ;i < image.getNumPath() ; i++){
        vector<ofPolyline> pathPolys;
        pathPolys = image.getPathAt(i).getOutline();
        if(pathPolys.size()>0){ ofPolyline thisPoly = pathPolys[0];
            ConnectionPoint newPoint = ConnectionPoint( thisPoly.getCentroid2D());
            //cout<< newPoint<< endl;
            newPoints.push_back(newPoint);
            newPoints[newPoints.size()-1].setFilling(true);
        }
        
    }
    
    for (int i=0;i< newPoints.size();i++){
        newPoints[i].setOthers(&newPoints);
        
    }
    
    //cam.disableMouseInput();
    
    
    
    /*
    connections.clear();
    if (newPoints.size()>0) {
        
        for (int i=0;i<newPoints.size();i++){
            for(int j=0;j<newPoints.size();j++){
                if(newPoints.at(i).distance(newPoints.at(j))<connectionDistance){
                    connections.push_back(Connection());
                    connections.at(connections.size()-1).start=newPoints.at(i);
                    connections.at(connections.size()-1).end=newPoints.at(j);
                    connections.at(connections.size()-1).dist= newPoints.at(i).distance(newPoints.at(j));
                    
                }
            }
            
        }
    }
    */
    
}

void ConnectorScene::update(){
    
    //pushIn(sin(ofGetFrameNum()*0.01)   );
    
    if (bWillGrow){
        startGrowth();
        bWillGrow = false;
    }
    
    for (int i=0; i<newPoints.size(); i++){

        newPoints[i].update();
        
        
    }
    
    for (int i=0; i<connections.size(); i++) {
        connections[i].update();
    }
    
    
    
    
    
    
}


void ConnectorScene::draw(){
    
    //cam.begin();
    ofBackground(0);
    ofSetColor(255);
    ofDisableDepthTest();
    
    for (int i=0; i<connections.size(); i++) {
        connections[i].draw();
    }
    
    for (int i=0; i<newPoints.size();i++){
        ofPushMatrix();
        ofTranslate(newPoints[i]);
        ofSeedRandom(i);
        //newPoints[i].rotateString(25);
        ofRotateY(ofRandom(0.2,1.5)*ofGetFrameNum());
        ofSeedRandom(i+5);
        ofRotateX(ofRandom(0.2,1.5)*ofGetFrameNum());
        newPoints[i].setTwist( sin((i*300)+ ofGetFrameNum() *0.01)*10 );
        newPoints[i].draw();
        ofSeedRandom();

        ofPopMatrix();
        
    }
    
    ofEnableDepthTest();
    
    syphon->publishScreen();
    //cam.end();
    
}

void ConnectorScene::startGrowth(){
    
    int rando =ofRandom(newPoints.size());
    ofVec3f startPoint = newPoints[rando];
    newPoints[rando].isActive= true;
    
    connections.push_back(Connection());
    connections.at(connections.size()-1).start = ofVec3f(newPoints[rando].x, newPoints[rando].y, newPoints[rando].baseZ);
    ConnectionPoint target = * newPoints[rando].neighbors[ofRandom(newPoints[rando].neighbors.size())];
    ofVec3f targetVec = ofVec3f(target.x, target.y, target.baseZ);
    
    connections.at(connections.size()-1).end = targetVec ;
    
        
}


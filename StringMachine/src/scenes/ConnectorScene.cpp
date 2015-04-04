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
    
    image.load("blah.svg");
    connections.clear();
    
    for(int i=1 ;i < image.getNumPath() ; i++){
        vector<ofPolyline> pathPolys;
        pathPolys = image.getPathAt(i).getOutline();
        if(pathPolys.size()>0){ ofPolyline thisPoly = pathPolys[0];
            ConnectionPoint newPoint = ConnectionPoint( thisPoly.getCentroid2D());
            //cout<< newPoint<< endl;
            newPoints.push_back(newPoint);
        }
        
    }
    
    for (int i=0;i< newPoints.size();i++){
        newPoints[i].setOthers(&newPoints);
        
    }
    
    
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
    
    for (int i=0; i<newPoints.size(); i++){

        newPoints[i].update();
        
        
    }
    
    for (int i=0; i<connections.size(); i++) {
        connections[i].update();
    }
    
    
    
    
}


void ConnectorScene::draw(){
    ofBackground(0);
    ofSetColor(255);
    
    
    for (int i=0; i<connections.size(); i++) {
        connections[i].draw();
    }
    for (int i=0; i<newPoints.size();i++){
        ofPushMatrix();
        ofTranslate(newPoints[i]);
        
        newPoints[i].rotateString(25);
        newPoints[i].draw();

        ofPopMatrix();
        
    }
    
    
}

void ConnectorScene::startGrowth(){
    
    int rando =ofRandom(newPoints.size());
    ofVec3f startPoint = newPoints[rando];
    newPoints[rando].isActive= true;
    
    connections.push_back(Connection());
    connections.at(connections.size()-1).start = newPoints[rando];
    ofVec3f target = * newPoints[rando].neighbors[ofRandom(newPoints[rando].neighbors.size())];
    connections.at(connections.size()-1).end = target ;
    
        
}


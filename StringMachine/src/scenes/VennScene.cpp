//
//  VennScene.cpp
//  StringMachine
//
//  Created by Jesse Garrison on 11/12/14.
//
//

#include "VennScene.h"

void VennScene::setup(){
    ofDisableLighting();
    ofDisableAlphaBlending();
    left = VennCircle(LEFT);
    right = VennCircle(RIGHT);
    
}

void VennScene::update(){
    left.update();
    right.update();
    
    
    left.setDisplace(sin(ofGetElapsedTimef())*100);
    right.setDisplace(sin(ofGetElapsedTimef())*100);

    
    rotation+= rotationSpeed;
    
    calcOverlap(left, right);
    
    
}

void VennScene::draw(){
    ofBackground(0);
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofRotate (rotation);
    
    overlapShape.draw();

    left.draw();
    right.draw();
    
    //testMesh.draw();
    
    syphon->publishScreen();
}

void VennScene::calcOverlap(VennCircle a, VennCircle b){
    
    vector<ofVec3f> aPoints = a.getPoints();
    vector<ofVec3f> bPoints = b.getPoints();
    
    vector<ofVec3f> overlappingPoints;
    
    
    overlappingPoints.clear();
    testMesh.clear();
    for(int i = 0; i< aPoints.size(); i++){
        
        ofVec3f adjustedPoint = aPoints[i];
        adjustedPoint += a.getLoc();

        if (adjustedPoint.distance(b.getLoc()) < b.getRadius()  ){
            overlappingPoints.push_back(adjustedPoint);
            
            
        }
        
    }
    for(int i = 0; i< bPoints.size(); i++){
        
        ofVec3f adjustedPoint = bPoints[i];
        adjustedPoint += b.getLoc();
        
        if (adjustedPoint.distance(a.getLoc()) < a.getRadius() ){
            overlappingPoints.push_back(adjustedPoint);
            
            
        }
        
    }
    
    vector<ofPoint> hull;
    hull = getConvexHull(overlappingPoints);
    
    overlapShape.clear();
    overlapShape.setColor(ofColor(255,0,0));
    for (int i=0;i<hull.size();i++){
        //int pickedIndex = ofMap( ofNoise(i*0.75),0,1,0,overlappingPoints.size());
        overlapShape.curveTo(hull[i]);
    }
    overlapShape.curveTo(hull[0]);
    
    
}


/// Convex Hull Calculation ///
bool lexicalComparison(const ofPoint& v1, const ofPoint& v2) {
    if (v1.x > v2.x) return true;
    else if (v1.x < v2.x) return false;
    else if (v1.y > v2.y) return true;
    else return false;
}

bool isRightTurn(ofPoint a, ofPoint b, ofPoint c) {
    // use the cross product to determin if we have a right turn
    return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) > 0;
}

vector<ofPoint> VennScene::getConvexHull(vector<ofPoint> points) {
    sort(points.begin(), points.end(), lexicalComparison);
    
    vector<ofPoint> hull;
    
    hull.push_back(points.at(0));
    hull.push_back(points.at(1));
    
    int currentPoint = 2;
    int direction = 1;
    
    for (int i=0; i<1000; i++) { //max 1000 tries
        
        hull.push_back(points.at(currentPoint));
        
        // look at the turn direction in the last three points
        h1 = hull.at(hull.size()-3);
        h2 = hull.at(hull.size()-2);
        h3 = hull.at(hull.size()-1);
        
        // while there are more than two points in the hull
        // and the last three points do not make a right turn
        while (!isRightTurn(h1, h2, h3) && hull.size() > 2) {
            
            // remove the middle of the last three points
            hull.erase(hull.end() - 2);
            
            if (hull.size() >= 3) {
                h1 = hull.at(hull.size()-3);
            }
            h2 = hull.at(hull.size()-2);
            h3 = hull.at(hull.size()-1);
        }
        
        // going through left-to-right calculates the top hull
        // when we get to the end, we reverse direction
        // and go back again right-to-left to calculate the bottom hull
        if (currentPoint == points.size() -1 || currentPoint == 0) {
            direction = direction * -1;
        }
        
        currentPoint+= direction;
        
        if (hull.front()==hull.back()) break;
    }
    
    return hull;
}




///-----///

VennCircle::VennCircle(vennSide _side){
    side = _side;
    
    for(int i =0;i<circleResolution;i++){
        float x = sin(i)*radius;
        float y = cos(i)*radius;
        basePoints.push_back(ofVec3f(x,y));
        
    }
    currentPoints = basePoints;
    
}


void VennCircle::update(){
    //loc = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
    loc = ofVec2f();
    
    switch (side) {
        case LEFT:
            loc.x -= abs(displacement);
            break;
            
        case RIGHT:
            loc.x+= abs(displacement);
            break;
            
        default:
            break;
    }
    
    
    for(int i =0;i<circleResolution;i++){
        
        float x = sin(i)*radius;
        float y = cos(i)*radius;
        basePoints [i] =ofVec3f(x,y);
            

        ofVec3f noiseVec = ofVec3f( ofSignedNoise(i+ofGetElapsedTimef()), ofSignedNoise(i+ofGetElapsedTimef()*1.2098), ofSignedNoise(i+ofGetElapsedTimef()*1.45033) );
        noiseVec *= 30;
        currentPoints[i]= basePoints[i] + noiseVec;
        
    }
    
    line.clear();
    for(int i =0;i<circleResolution;i++){
        line.curveTo(currentPoints[i]);
    }
    line.close();
}

void VennCircle::draw(){
    
    ofSetColor(255);
    ofNoFill();
    ofSetLineWidth(3);
    
    ofPushMatrix();
    ofTranslate(loc);
    line.draw();
    ofPopMatrix();
    
    
}
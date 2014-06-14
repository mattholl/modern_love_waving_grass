//
//  whiteLine.cpp
//  modernLoveCover
//
//  Created by mh on 08/06/2014.
//
//

#include "whiteLine.h"
#include "ofMain.h"

whiteLine::whiteLine() {
    // Default values
    height = 100.0;
    
    // Float radians
    rotX = 0;
    rotY = 0;
    
    width = 1;
    
    startPos = ofVec3f();
    endPos = ofVec3f();
}

void whiteLine::setStart(ofVec3f start) {
    startPos.set(start);
    endPos.set(start);
    endPos.z = endPos.z + height;
}

void whiteLine::setRotation(float radX, float radY) {
    rotX = radX;
    rotY = radY;
}

void whiteLine::updateRotation(float radX, float radY) {
    rotX = rotX + radX;
    rotY = rotY + radY;
}

void whiteLine::setHeight(float newHeight) {
    height = newHeight;
    endPos.z = endPos.z + newHeight;
}

void whiteLine::update() {
//    endPos.rotateRad(rotX, rotY, 0);
//    ofVec3f xRotAngle = ofVec3f(startPos.x, 0, 0);
    
//    endPos.rotate(rotX, xRotAngle);
    
    ofVec3f lineVec = endPos - startPos;
    
    // Get the aangle between linevec and z axis
    ofVec3f zAxis = ofVec3f(0, 0, 1);
    
    float angleDiff = zAxis.angle(lineVec);
//    ofLog() << angleDiff;
    
    
    // figure out angle of lineVec to return rotation angle to 0
    // figure out what it should be start
    
    lineVec.rotate(rotX, ofVec3f(0, 1, 0));
    endPos = startPos + lineVec;
    
    // Slowly return rotX to 0
    ofLerpRadians(rotX, 0, 0.1);
}

void whiteLine::draw() {
    // We're translating to the startPos within the draw function
//    ofLine(ofVec3f(0, 0, 0), endPos);
}
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
    height = 10.0;
    
    // Float radians
    rotX = 0;
    rotY = 0;
    
    width = 5;
}

void whiteLine::setStart(ofVec3f start) {
    startPos = start;
}

void whiteLine::setRotation(float radX, float radY) {
    rotX = radX;
    rotY = radY;
}

void whiteLine::setHeight(float newHeight) {
    height = newHeight;
}

void whiteLine::draw() {
    // calculate vec3 of the end point
    ofVec3f end = ofVec3f(0, 0, height);
    end.rotateRad(rotX, rotY, 0);
    
    // We're translating to the startPos within the draw function
    ofLine(ofVec3f(0, 0, 0), end);
}
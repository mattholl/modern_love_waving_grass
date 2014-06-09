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

void whiteLine::draw() {
    // calculate vec3 of the end point
    
    ofVec3f end;
    end.set(0, 0, 100);
    
    // We're translating to the startPos within the draw function
    ofLine(ofVec3f(0, 0, 0), end);
}
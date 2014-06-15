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
    
    // 1. Update the rotation angle
    //      To get the position of the endpoint
    //      Calculate what the rotation in x and y should be next
    // 2. TODO, add points to linePath -> mesh
    
    // Get the vector of the line
    ofVec3f lineVec = endPos - startPos;
    
    // Get the angle between linevec and z axis
    ofVec3f zAxis = ofVec3f(0, 0, 1);
    
    // Need to know what the x and y components of these are
    float angleDiff = zAxis.angleRad(lineVec);
    
    // Apply the rotation around the yAxis
    lineVec.rotate(rotX, ofVec3f(0, 1, 0));
//    lineVec.rotate(rotY, ofVec3f(1, 0, 0));
    
    // Update the end position with the new angle
    endPos = startPos + lineVec;
    

    //
    ofLog() << "rotX";
    ofLog() << rotX;
    
    ofLog() << "rotY";
    ofLog() << rotY;

    
    // Slowly return rotX to 0
    rotX = ofLerpRadians(rotX, 0, 0.1);
    
    // If rotX has returned to zero get the angle that would be required to return the line to parallel with z-axis
    if (rotX <= 1.0e-3) {
        rotX = -angleDiff;
    }
    
    // Quaternions
    ofQuaternion xRotQuat(rotY, ofVec3f(1,0,0));
    ofQuaternion yRotQuat(rotX, ofVec3f(0,1,0));

    ofVec3f xRotVec3 = xRotQuat.getEuler();
    ofVec3f yRotVec3 = yRotQuat.getEuler();
    
    ofLog() << "xRotVec3";
    ofLog() << xRotVec3;

    ofLog() << "yRotVec3";
    ofLog() << yRotVec3;
    
}

void whiteLine::draw() {
    // We're translating to the startPos within the draw function
//    ofLine(ofVec3f(0, 0, 0), endPos);
}
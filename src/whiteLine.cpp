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
    
    width = 1;
    
    startPos = ofVec3f();
    endPos = ofVec3f();
}

void whiteLine::setStart(ofVec3f start) {
    startPos.set(start);
    endPos.set(start);
    endPos.z = endPos.z + height;
}

void whiteLine::setHeight(float newHeight) {
    height = newHeight;
    endPos.z = endPos.z + newHeight;
}

void whiteLine::setRotation(float radX, float radY, float rate) {
    // Set the target quaternion rotation
    ofQuaternion xRotQuat, yRotQuat;
    xRotQuat.makeRotate(ofRadToDeg(radX), 0, 1, 0);
    yRotQuat.makeRotate(ofRadToDeg(radY), 1, 0, 0);
    
    // Get the target from the x and y rotation quats
    targetQuat = xRotQuat * yRotQuat;
    
    // Set the start quaternion from the current quaternion rotation
    startQuat = currQuat;
    
    // Set the rate at which the rotation should move from the start to target rotations
    lerpStep = 1 / rate;
    lerpPos = 0;
}

// void whiteLine::returnUp

void whiteLine::update() {
    
    // Lerp towards targetQuat
    currQuat.slerp(lerpPos, startQuat, targetQuat);
    
    // Update the position of the slerp for the next time through
    lerpPos = lerpPos + lerpStep;
    
    // Create a vector pointing along the z axis to the height of the line.
    ofVec3f lineVec;
    lineVec.z = height;
    
    // Apply the rotation
    lineVec = lineVec * currQuat;
    
    // Apply the line base vector to move back out to the correct place from the origin
    endPos = startPos + lineVec;
    
    // If the target rotation has been reached then reset the rotation to point the line straight back up
    if (lerpPos >= 1) {
            // lerpT = 1 - target to upright quat
        // Set the target to up vector
        
        lerpStep = 0;
    }
    
    // Should there be a check for whether the slerp needs to happen??????
    
}

void whiteLine::draw() {
    // For debugging
    ofLine(startPos, endPos);
}
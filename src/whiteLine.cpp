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
    
    startPos = ofVec3f();
    endPos = ofVec3f();
}

// The position of the base of the line.
void whiteLine::setStart(ofVec3f start) {
    startPos.set(start);
    endPos.set(start);
    endPos.z = endPos.z + height;
}

void whiteLine::setHeight(float newHeight) {
    height = newHeight;
    endPos.z = endPos.z + newHeight;
}

// Set the target rotation from rotation in x and y.
// Set the rate at which this rotation should happen.
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

// Set rotation with no interpolation
void whiteLine::setRotation(float radX, float radY) {
    // Set the target quaternion rotation
    ofQuaternion xRotQuat, yRotQuat;
    xRotQuat.makeRotate(ofRadToDeg(radX), 0, 1, 0);
    yRotQuat.makeRotate(ofRadToDeg(radY), 1, 0, 0);
    
    // Get the target from the x and y rotation quats
    targetQuat = xRotQuat * yRotQuat;
    
    // Set the start quaternion from the current quaternion rotation
    startQuat = currQuat;
    
    // Set the lerp control parameters so that the update function puts the line directly to the target
    lerpStep = 0;
    lerpPos = 1;
}

// Deal with rotating the line towards the target vector.
// If the target has been achieved (lerpPos is 1) reset the line to upright orientation.
void whiteLine::update() {
    
    // Lerp towards targetQuat
    // TODO? Should there be a check whether slerp is required
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
        // Reset dt for the lerp
        lerpStep = 0;

        // Send the line back to an upright angle
        setRotation(0, 0, 10);
    }
    
    // Interpolate the line start and end points to make the curve Catmull-Rom
    ofVec3f curveStart;
    curveStart.set(startPos);
    curveStart.z -= 100;
    
    ofVec3f curveEnd;
    curveEnd.set(endPos);
    
    // Vector for the curveEnd point to control the bend?
    
    curveEnd.z -= 150;
    curveLine.clear();
    curveLine.curveTo(curveStart); // -z direction so stright line up to start point
    curveLine.curveTo(startPos);
    curveLine.curveTo(endPos);
    curveLine.curveTo(curveEnd);   // +z direction
    
    // Get the tesselation out and store in a local mesh?
//    //     lineMesh.setMode(OF_PRIMITIVE_LINES);
    // just use mesh.append(polyLineMesh) with main update
//    curveLineMesh = curveLine.getTessellation();
    
}


void whiteLine::draw() {
    // For debugging
    ofLine(startPos, endPos);
}
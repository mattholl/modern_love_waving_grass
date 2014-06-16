//
//  whiteLine.h
//  modernLoveCover
//
//  Created by mh on 08/06/2014.
//
//

#ifndef __modernLoveCover__whiteLine__
#define __modernLoveCover__whiteLine__

#include <iostream>
#include "ofMain.h"

#endif /* defined(__modernLoveCover__whiteLine__) */

class whiteLine {
public:
    whiteLine();
    
    ofVec3f startPos;
    ofVec3f endPos;
    
    float height;
    
    // Rotation around x and y, when updated will set a start and target quaternion to be completed in a set lerp time
    // If the target quaternion is arrived at then the line will be returned to an upright direction
    //float rotX;
    //float rotY; // May not need these on the object
    
    ofQuaternion currQuat, startQuat, targetQuat;
    float lerpPos, lerpStep;
    
    // So that we can tell when lerping x to zero has stopped changing
    //float angleChangeX;
    
    int width;
    
    void setStart(ofVec3f start);
    void setRotation(float radX, float radY, float rate);
    void setHeight(float newHeight);
    void update();
    void draw();
};
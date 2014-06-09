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
    
    float rotX;
    float rotY;
    
    int width;
    
    void setStart(ofVec3f start);
    void setRotation(float radX, float radY);
    void updateRotation(float radX, float radY);
    void setHeight(float newHeight);
    void update();
    void draw();
};
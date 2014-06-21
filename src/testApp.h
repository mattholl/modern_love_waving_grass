#pragma once

#include "ofMain.h"
#include "whiteLine.h"

const int LINE_RESOLUTION = 140;
//const int LINE_RESOLUTION = 5;

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofEasyCam cam;
    ofNode camMover;
    ofVec3f camMoverTarget;
    ofVec3f camMoverStart;
    bool autoMoveCamera;
    int camMode;

    vector<whiteLine> whiteLines;
    ofMesh lineMesh;
    bool orbiting;
    bool axis;
};

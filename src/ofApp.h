#pragma once

#include "ofMain.h"
#include "whiteLine.h"
#include "ofxXmlSettings.h"
//#include "ofxTouchPad.h"

//const int LINE_RESOLUTION = 140;
//const int LINE_RESOLUTION = 100;
//const int LINE_RESOLUTION = 5;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

//    bool onPointerUp(ofx::PointerEventArgs& evt);
//    bool onPointerDown(ofx::PointerEventArgs& evt);
//    bool onPointerMove(ofx::PointerEventArgs& evt);
//    bool onPointerCancel(ofx::PointerEventArgs& evt);
    
    
    // Load the settings from bin/data/settings.xml
    ofxXmlSettings XML;

    int lineDensity;
    int planeSize;
    int lineResolution;

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
    
    bool bShowInfo = true;
};

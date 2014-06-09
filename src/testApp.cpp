#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //
    
    cam.setDistance(1000);
//    cam.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
    
    // Create a line
    whiteLine line;
    line.setStart(ofVec3f(200, 200, 0));
    
    whiteLines.push_back(line);
}

//--------------------------------------------------------------
void testApp::update(){
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableDepthTest();
    ofBackground(0);
    
    ofPushMatrix();
    
        cam.begin();
            ofDrawAxis(1000);
    
            for (int i = 0; i < whiteLines.size(); i++) {
                ofPushMatrix();
                    ofTranslate(whiteLines[i].startPos);
                    ofSetColor(ofColor::white);
                    ofSetLineWidth(whiteLines[i].width);
                    whiteLines[i].draw();
                ofPopMatrix();
            }

            // draw the lines vector foreach
            // translate to startCoords
            // draw line 0,0 to z + height
        cam.end();

    ofPopMatrix();
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
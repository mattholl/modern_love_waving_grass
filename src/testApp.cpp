#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Calculate distance between lines
    
    int xStride = ofGetWidth() / LINE_RESOLUTION;
    int yStride = ofGetHeight() / LINE_RESOLUTION;
    
    // Create the lines vector with the corect starting positions
    for (int i = 0; i <= ofGetWidth(); i += xStride) {
        for (int j = 0; j <= ofGetHeight(); j += yStride) {
            whiteLine line;
            line.setStart(ofVec3f(i, j, 0));
            // Set height if required
            whiteLines.push_back(line);
        }
    }
    
    cam.setDistance(1000);
}

//--------------------------------------------------------------
void testApp::update(){
    float time = ofGetElapsedTimef();
    float x = ofSignedNoise(time);
    float y = ofSignedNoise(time - 1000);
    for (int i = 0; i < whiteLines.size(); i++) {
        whiteLines[i].setRotation(x, y);
        whiteLines[i].update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableDepthTest();
    ofBackground(0);
    
    ofPushMatrix();
    
        cam.begin();
            ofDrawAxis(1000);
            // Draw each line
            for (int i = 0; i < whiteLines.size(); i++) {
                ofPushMatrix();
                    // Move to the start location for the line
                    ofTranslate(whiteLines[i].startPos);
                    ofSetColor(ofColor::white);
                    ofSetLineWidth(whiteLines[i].width);
                    whiteLines[i].draw();
                ofPopMatrix();
            }
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
#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //
    
    cam.setDistance(1000);
    
    // Create a line
    whiteLine line;
    line.setStart(ofVec3f(100, 0, 0));
    line.setHeight(100);
    whiteLines.push_back(line);
    
    whiteLine line2;
    line2.setStart(ofVec3f(200, 0, 0));
    line2.setHeight(100);
    whiteLines.push_back(line2);
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
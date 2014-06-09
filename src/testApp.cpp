#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    cam.setDistance(1000);
    
    // Calculate distance between lines
    int worldWidth = ofGetWidth() * 4;
    int worldHeight = ofGetHeight() * 4;
    
    int halfWorldWidth = worldWidth / 2;
    int halfWorldHeight = worldHeight / 2;
    
    int xStride = worldWidth / LINE_RESOLUTION;
    int yStride = worldHeight / LINE_RESOLUTION;
    
    // Create the lines vector with the corect starting positions
    for (int i = -halfWorldWidth; i <= halfWorldWidth; i += xStride) {
        for (int j = -halfWorldHeight; j <= halfWorldHeight; j += yStride) {
            
            whiteLine line;
            line.setStart(ofVec3f(i + ofRandom(-4, 4), j + ofRandom(-4, 4), 0));
            line.setRotation(ofRandom(-0.03, 0.03), ofRandom(-0.03, 0.03));

            // Set height if required
            float height = 150 + ofRandom(-10, 10);
            line.setHeight(height);
            
            whiteLines.push_back(line);
            
        }
    }
}

//--------------------------------------------------------------
void testApp::update(){
    float time = ofGetElapsedTimef();

    for (int i = 0; i < whiteLines.size(); i++) {
        float x = 0.01 * ofSignedNoise(time + 0.1 * i);
        float y = 0.01 * ofSignedNoise(time + 0.1 * i);
        whiteLines[i].updateRotation(x, y);
        whiteLines[i].update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableDepthTest();
    ofBackground(0);
    ofPushMatrix();
    
        cam.begin();
//            ofDrawAxis(1000);
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
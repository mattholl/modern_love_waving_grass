#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(60);
    lineMesh.setMode(OF_PRIMITIVE_LINES);
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
//            line.setRotation(ofRandom(-0.03, 0.03), ofRandom(-0.03, 0.03));
            line.setRotation(1, 0);
            line.update();
            
            // Set height if required
            float height = 150 + ofRandom(-10, 10);
            line.setHeight(height);
            
            whiteLines.push_back(line);
            
        }
    }
    
    orbiting = true;
    axis = true;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
//    float time = ofGetElapsedTimef();
//    
//    for (int i = 0; i < whiteLines.size(); i++) {
//        float x = 0.01 * ofSignedNoise(time + 0.1 * i);
//        float y = 0.01 * ofSignedNoise(time + 0.1 * i);
//        whiteLines[i].setRotation(ofRandom(-0.3, 0.3), ofRandom(-0.3, 0.03));
//        whiteLines[i].updateRotation(x, y);
//    }
    
    
    // Set the mesh vertices
    lineMesh.clear();
    
    for (int i = 0; i < whiteLines.size(); i++) {
        whiteLines[i].update();
        
        lineMesh.addVertex(whiteLines[i].startPos);
        lineMesh.addColor(ofColor::black);
        
        lineMesh.addVertex(whiteLines[i].endPos);
        lineMesh.addColor(ofColor::white);
    }
    
    // Add mesh indices
    int numVerts = lineMesh.getNumVertices();
    
    for (int i = 0; i < numVerts; i += 2) {
        lineMesh.addIndex(i);
        lineMesh.addIndex(i + 1);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableDepthTest();
    ofBackground(0);

    // Orbiting bool is set with "m" key
    // Draw axis bool is set with "a" key
    
    cam.begin();
    
        if(orbiting) {
            cam.enableMouseInput();
        } else {
            cam.disableMouseInput();
        }
    
        if (axis) {
            ofDrawAxis(100000);
        }
    
        lineMesh.draw();
    
    cam.end();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == 'm') {
        orbiting = !orbiting;
    }
    
    if(key == 'a') {
        axis = !axis;
    }
    
    if(key == 's') {
        ofImage image;
        
        image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        
        // Save the image to the dir from XML settings, path should end in /
        image.saveImage("screengrab_" + ofToString(ofGetUnixTime()) + ".png");
        cout << "Manual image saved : screengrab_" + ofToString(ofGetUnixTime()) + ".png" << endl;
    }
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
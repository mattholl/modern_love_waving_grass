#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    lineMesh.setMode(OF_PRIMITIVE_LINES);

    // Use the camMove node to move the camera programmatically
    cam.lookAt(camMover);
    cam.setAutoDistance(true);
    cam.setDistance(1000);

    // Set this as soon as we switch a camera mode on
    autoMoveCamera = true;

    // Load the settings file
    if( XML.loadFile("settings.xml") ){
        cout << "settings.xml loaded" << endl;
    } else {
        cout << "unable to load settings.xml check data/ folder" << endl;
    }

    // Parse settings
    lineDensity = XML.getValue("app-settings:mesh-data:line-density", 5);
    planeSize = XML.getValue("app-settings:mesh-data:plane-size", 4);
    lineResolution = XML.getValue("app-settings:mesh-data:line-resolution", 20);

    // Calculate distance between lines
    int worldWidth = ofGetWidth() * planeSize;
    int worldHeight = ofGetHeight() * planeSize;

    int halfWorldWidth = worldWidth / 2;
    int halfWorldHeight = worldHeight / 2;

    int xStride = worldWidth / lineDensity;
    int yStride = worldHeight / lineDensity;

    // Create the lines vector with the corect starting positions
    for (int i = -halfWorldWidth; i <= halfWorldWidth; i += xStride) {
        for (int j = -halfWorldHeight; j <= halfWorldHeight; j += yStride) {

            // Pass the resolution that curves should be made to into the constructor
            whiteLine line(lineResolution);

            // Create a slight variation in the starting position of the line
            line.setStart(ofVec3f(i + ofRandom(-4, 4), j + ofRandom(-4, 4), 0));

            // Set the line height
            float height = 150 + ofRandom(-10, 10);
            line.setHeight(height);

            whiteLines.push_back(line);
        }
    }

    ofLog() << "num lines : " << whiteLines.size();

    // To draw the axis and allow mouse input
    orbiting = true;
    axis = true;
    

}

//--------------------------------------------------------------
void ofApp::update(){


    //--------------------------------------------------------------
    // UPDATE THE CAMERA
    if(autoMoveCamera) {

        if(camMode == 1) {
            // Rotate camera around camMover
            cam.roll(0.1);
        }

        if(camMode == 2) {
            // Dolly the camera towards the surface and rotate to look down the xaxis
//            camMoverTarget

            float x = ofLerp(camMoverStart.x, camMoverTarget.x, 0.001);
            float y = ofLerp(camMoverStart.y, camMoverTarget.y, 0.001);
            float z = ofLerp(camMoverStart.z, camMoverTarget.z, 0.001);

            camMover.move(x, y, z);
            cam.lookAt(camMover);

            // Rotate the camera incrementally towards 45deg
        }

        // Orbit ofNode camMover
        if(camMode == 3) {
//            float angleLatitude = (sin(ofGetElapsedTimef())) * 90;
//            float angleLongitude = (sin(ofGetElapsedTimef())) * 180;
//            ofLog() << angle;
            //cam.orbit(float longitude, float latitude, float radius, camMover);
//            cam.orbit(angleLongitude, angleLatitude, 1000, camMover);
        }
    }


    //--------------------------------------------------------------
    // SETTING LINE ROTATIONS
    float time = ofGetElapsedTimef();

//    // Set a pulse of random rotations every 10 seconds
//    int timeInt = int(time);

//    if(timeInt % 2 == 0) {
//        for (int i = 0; i < whiteLines.size(); i++) {
//            float x = ofSignedNoise(time + 0.1 * i);
//            float y = ofSignedNoise(time + 0.1 * i);
//            whiteLines[i].setRotation(x, y, 10);
////            whiteLines[i].setRotation(ofRandom(-0.3, 0.3), ofRandom(-0.3, 0.3), 10);
////            whiteLines[i].setRotation(ofRandom(-0.75, 0.75), ofRandom(-0.75, 0.75), 10);
//        }
//    }

    // Set the rotation for a selection of lines
    unsigned int numLines = 5000;

    for(unsigned int i = 0; i < numLines; i++) {
        int randomIndex = rand() % whiteLines.size();

        float x = ofSignedNoise(time * i) * 0.2;
        float y = ofSignedNoise(time * i) * 0.2;
        whiteLines[randomIndex].setRotation(x, y, 10);

    }

    //--------------------------------------------------------------
    // MESH SETUP

    // Reset the mesh vertices - it's very likely that the vertices will be updated
    lineMesh.clear();

    // Loop over the lines
    for (unsigned int i = 0; i < whiteLines.size(); i++) {
        whiteLines[i].update();

        // Number of vertices that are there already
        int prevNumVerts = lineMesh.getNumVertices();

        // Get the vertices which form the curve
        vector<ofVec3f> curveLineVertices = whiteLines[i].curveLine.getVertices();
        unsigned int numNewVerts = curveLineVertices.size();

        // Line start colour
        ofColor startColor = whiteLines[i].startColor;
        ofColor endColor = whiteLines[i].endColor;

        // Append this line vertices to the mesh
        lineMesh.addVertices(curveLineVertices);

        // Loop over the vertices in the line and add the index to form each line
        // Lerp the colour for the vertex and add to the mesh

        float colorLerpStep = 1.0f / numNewVerts;

        for (unsigned int j = 0; j < numNewVerts; j++) {

            // Index 0 will be a reference to the last vertex of the previous line so don't add it
            if(j > 0) {
                lineMesh.addIndex(prevNumVerts + j - 1);
                lineMesh.addIndex(prevNumVerts + j);
            }

            // Add the vertex colour
            // Lerp between the start and end colours
            ofColor vertexColor = startColor.getLerped(endColor, colorLerpStep * (j + 1));

            lineMesh.addColor(vertexColor);
        }

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
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
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key == 'b') {
        ofLog() << "break";
    }

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

    // Programmatic camera movement
    if(key == '1') {
//        autoMoveCamera = !autoMoveCamera;

        if(autoMoveCamera) {
            camMode = 1;

            camMoverStart = camMover.getPosition();

            // Set the camMoverTarget vector to a sit on the plane at the far edge
            camMoverTarget.set(-200, -200, 0);
        }
    }

    if(key == '2') {

        if(autoMoveCamera) {
            camMode = 2;
            camMoverStart = camMover.getPosition();

            // Set the camMoverTarget vector to a sit on the plane at the far edge
            camMoverTarget.set(1000, 0, 0);
        }
    }

    // Orbit camMover node
    if(key == '3') {
        if(autoMoveCamera) {
            camMode = 3;

        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

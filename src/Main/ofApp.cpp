#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    if (animationDebugFlag) {
        ofSetFrameRate(60);
    } else {
        ofSetVerticalSync(false);
    }
    ofSetFrameRate(60);
    ofSetCircleResolution(256);
}

//--------------------------------------------------------------
void ofApp::update(){
    scenario.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    scenario.draw();
    
    if (debugFPSFlag) {
        ofPushStyle();
        ofSetColor(0, 0, 0, 255);
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 40, 40);
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        vs.saveTS();
    }
    if (key == 'n') {
        scenario.next();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

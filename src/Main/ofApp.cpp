#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    if (animationDebugFlag) {
        ofSetFrameRate(60);
    } else {
        ofSetVerticalSync(false);
    }
    ofSetCircleResolution(256);
}

//--------------------------------------------------------------
void ofApp::update(){
    runner.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    runner.draw();
    
    if (debugFPSFlag) {
        ofPushStyle();
        ofSetColor(0, 0, 0, 255);
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 40, 40);
        ofPopStyle();
    }
    
    //vs.save();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        runner.save();
    }
    if (key == 'n') {
        runner.next();
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

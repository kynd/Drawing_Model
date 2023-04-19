#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    if (animationDebugFlag) {
        ofSetFrameRate(60);
    } else {
        ofSetVerticalSync(false);
    }
    //ofSetFrameRate(2);
    ofSetCircleResolution(256);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    runner.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    runner.draw();
    
    /*
    for (int k = 0; k < 8; k ++) {
        vector<ofVec3f> center;
        vector<ofVec3f> left, right;
        
        ofVec2f p = ofVec3f(ofRandom(BUFF_WIDTH), ofRandom(BUFF_HEIGHT));
        ofVec3f dir = VectorUtil::randomUnitVec3();
        
        vector<vector<ofVec3f> > points = I_Leaf::trunkPoints(p, dir, BUFF_HEIGHT, BUFF_WIDTH * 0.25);
        vector<ofPolyline> polylines = I_Leaf::pointsToLeaf02(points[0], points[1], points[2]);
        
        for (int i = 0; i < polylines.size(); i ++) {
            ofPolyline line = polylines[i];
            line.draw();
            
        }
    }
    */
    
    /*
    if (debugFPSFlag) {
        ofPushStyle();
        ofSetColor(0, 0, 0, 255);
        ofDrawBitmapString(ofToString(ofGetFrameRate()), 40, 40);
        ofPopStyle();
    }
     */
    if(ofGetFrameNum() % 5 == 0) {
        vs.save();
    }
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

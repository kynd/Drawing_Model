#include "AnimationActor.hpp"

void AnimationActor::update() {
    
}


void AnimationActor::setPosition(ofVec2f _center, ofVec2f _scale) {

    dispCenter = _center;
    dispScale = _scale;
}

void AnimationActor::updateConductor(shared_ptr<ofFbo> _canvas, Conductor& conductor) {
    
}

void AnimationActor::draw() {
    ofPushMatrix();
    /*
    ofTranslate(float(ofGetWidth()) / BUFF_WIDTH * dispCenter.x, float(ofGetHeight()) / BUFF_HEIGHT * dispCenter.y);
    ofScale(float(ofGetWidth()) / BUFF_WIDTH * dispScale.x, float(ofGetHeight()) / BUFF_HEIGHT * dispScale.y);
     */
    ofScale(float(ofGetWidth()) / BUFF_WIDTH, float(ofGetHeight()) / BUFF_HEIGHT);
    drawMain();
    ofPopMatrix();
}

void AnimationActor::drawMain() {
}

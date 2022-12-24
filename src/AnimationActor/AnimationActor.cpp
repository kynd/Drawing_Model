#include "AnimationActor.hpp"

void AnimationActor::update() {
    
}

void AnimationActor::updateConductor(shared_ptr<ofFbo> _canvas, Conductor& conductor) {
    
}

void AnimationActor::draw() {
    ofPushMatrix();
    ofScale(float(ofGetWidth()) / BUFF_WIDTH, float(ofGetHeight()) / BUFF_HEIGHT);
    drawMain();
    ofPopMatrix();
}

void AnimationActor::drawMain() {
}

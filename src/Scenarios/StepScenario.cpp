
#include "StepScenario.hpp"


StepScenario::StepScenario() {
    
    canvas = shared_ptr<ofFbo>(new ofFbo());
    canvas->allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);;
    
    animator.init(canvas);
    next();
};

void StepScenario::next() {
    animator.update(conductor);
};

void StepScenario::draw() {
    canvas->draw(0, 0, ofGetWidth(), ofGetHeight());
    /*
    for (int i = 0; i < fillDefs.size(); i ++) {
        ofPushMatrix();
        ofScale(float(ofGetWidth()) / BUFF_WIDTH, float(ofGetHeight()) / BUFF_HEIGHT);
        fillDefs[i].line.draw();
        ofPopMatrix();
    }
    */
    if (debugFlag || animationDebugFlag) {
        conductor.debugDraw(true);
    }
    if (debugFlag) {
        conductor.debugDraw(true);
    }
    
    if (conductor.getIsDone()) {
        vs.save(*canvas);
        next();
    }
}

#include "AnimationScenario.hpp"


AnimationScenario::AnimationScenario() {
    colorSampler.load("img/26.jpg");
    
    canvas = shared_ptr<ofFbo>(new ofFbo());
    canvas->allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    backgroungColor = colorSampler.getRandomColor();
    clearBackground();
    
    animater.init(canvas);
    animater.update(conductor);
};
            
void AnimationScenario::clearBackground() {
    canvas->begin();
    ofClear(backgroungColor);
    canvas->end();
};
            

void AnimationScenario::draw() {
    canvas->draw(0, 0, ofGetWidth(), ofGetHeight());
    if (debugFlag || animationDebugFlag) {
        conductor.debugDraw(true);
    }
    
    if (animationDebugFlag) {
        clearBackground();
        animater.update(conductor);
    } else if (conductor.getIsDone()) {
        if (saveFlag) { vs.save(*canvas);
            nImage ++;
            if (nImage > 1000) {
                std::exit(0);
            }
        }
        clearBackground();
        animater.update(conductor);
    }
}

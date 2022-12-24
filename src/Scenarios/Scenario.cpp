#include "Scenario.hpp"


Scenario::Scenario() {
};

void Scenario::next() {
}

void Scenario::update() {
    conductor.update();
};

void Scenario::draw() {
    canvas->draw(0, 0, ofGetWidth(), ofGetHeight());
    
    if (debugFlag || animationDebugFlag) {
        conductor.debugDraw(true);
    }
    if (debugFlag) {
        conductor.debugDraw(true);
    }
}

void Scenario::save() {
    vs.save(*canvas);
};

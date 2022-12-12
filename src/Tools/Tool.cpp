#include "Tool.hpp"

Tool::Tool(shared_ptr<ofFbo> _canvas, int _priority) {
    canvas = _canvas;
    priority = _priority;
}

ofRectangle Tool::getBoundingBox() {
    return boundingBox;
}


int Tool::getPriority() {
    return priority;
}

Tool::States Tool::getState() {
    return state;
}


void Tool::setup() {
    if (!animationDebugFlag) {
        setupMain();
    }
}
void Tool::setupMain() {
}

void Tool::activate() {
    state = ACTIVE;
    if (!animationDebugFlag) {
        activateMain();
    }
}

void Tool::activateMain() {
}

void Tool::finalize() {
    state = COMPLETE;
    if (!animationDebugFlag) {
        finalizeMain();
    }
}

void Tool::finalizeMain() {
}

void Tool::update() {
    if (!animationDebugFlag) {
        updateMain();
    }
}

void Tool::updateMain() {
    
}

void Tool::debugDraw() {
    
}

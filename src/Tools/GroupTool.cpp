#include "GroupTool.hpp"

bool GroupTool::isInitialized = false;

GroupTool::GroupTool(shared_ptr<ofFbo> _canvas, int _priority) : Tool(_canvas, _priority) {
    if (!isInitialized && !animationDebugFlag) { initialize(); }
    setup();
}


void GroupTool::initialize() {
    isInitialized = true;
}

void GroupTool::setupMain() {
}

void GroupTool::activateMain() {
}


void GroupTool::updateMain() {
    conductor.update();
    
    if (conductor.getIsDone()) {
        finalize();
    }
}

void GroupTool::debugDraw() {
    ofPushStyle();
    ofNoFill();
    for (int i = 0; i < tools.size(); i ++) {
        tools[i]->debugDraw();
    }
    ofPopStyle();
}

void GroupTool::addTool(shared_ptr<Tool> tool) {
    if (boundingBox.width == 0 && boundingBox.height == 0) {
        boundingBox = tool->getBoundingBox();
    } else {
        boundingBox = boundingBox.getUnion(tool->getBoundingBox());
    }
    tools.push_back(tool);
    conductor.addTool(tool);
}

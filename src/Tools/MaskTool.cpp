#include "MaskTool.hpp"

bool MaskTool::isInitialized = false;
ofShader MaskTool::maskShader;
ofFbo MaskTool::canvasCopy;

MaskTool::MaskTool(shared_ptr<ofFbo> _canvas, float _priority) : Tool(_canvas, _priority) {
    if (!isInitialized && !animationDebugFlag) { initialize(); }
    
    localCanvas = shared_ptr<ofFbo>(new ofFbo());
    mask = shared_ptr<ofFbo>(new ofFbo());
    
    setup();
}


void MaskTool::initialize() {
    isInitialized = true;
    maskShader.load("shader/basic.vs", "shader/mask/mask.fs");
    canvasCopy.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
}

void MaskTool::setupMain() {
}

void MaskTool::activateMain() {
    allocateMask();
    localCanvas->allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    localCanvas->begin();
    canvas->draw(0, 0);
    localCanvas->end();
    
    for (int i = 0; i < masks.size(); i ++) {
        conductor.runToolImmediately(masks[i]);
    }
}

void MaskTool::allocateMask() {
    if (mask->getWidth() > 0) { return; };
    mask->allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    mask->begin();
    ofClear(255);
    mask->end();
}


void MaskTool::updateMain() {
    conductor.update();
    
    canvasCopy.begin();
    canvas->draw(0,0);
    canvasCopy.end();
    
    canvas->begin();
    maskShader.begin();
    maskShader.setUniformTexture("canvas", canvasCopy, 1);
    maskShader.setUniformTexture("mask", *mask, 2);
    localCanvas->draw(0, 0);
    maskShader.end();
    canvas->end();
    
    if (conductor.getIsDone()) {
        finalize();
    }
}

void MaskTool::debugDraw() {
    ofPushStyle();
    ofNoFill();
    for (int i = 0; i < tools.size(); i ++) {
        tools[i]->debugDraw();
    }
    ofPopStyle();
}


shared_ptr<ofFbo> MaskTool::getLocalCanvas() {
    return localCanvas;
}

shared_ptr<ofFbo> MaskTool::getMask() {
    return mask;
}

void MaskTool::addTool(shared_ptr<Tool> tool) {
    tools.push_back(tool);
    conductor.addTool(tool);
}

void MaskTool::addMask(shared_ptr<Tool> tool) {
    if (boundingBox.width == 0 && boundingBox.height == 0) {
        boundingBox = tool->getBoundingBox();
    } else {
        boundingBox = boundingBox.getUnion(tool->getBoundingBox());
    }
    masks.push_back(tool);
}

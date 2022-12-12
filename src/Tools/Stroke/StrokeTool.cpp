#include "StrokeTool.hpp"

bool StrokeTool::isInitialized = false;

StrokeTool::StrokeTool(shared_ptr<ofFbo> _canvas, int _priority, shared_ptr<StrokeStyle> _style, ofPolyline _shape, float _width, ofPolyline _taper) : Tool(_canvas, _priority) {
    
    if (!isInitialized && !animationDebugFlag) { initialize(); }
    
    style = _style;
    width = _width;
    shape = _shape;
    taper = _taper;
    
    resolution =  shape.getLengthAtIndex(shape.getIndexAtPercent(0.99)) * 0.5;
    
    margin = max(margin, int(ceil(width + 4)));
    
    ofRectangle bb = shape.getBoundingBox();
    boundingBox = ofRectangle(bb.x - margin, bb.y - margin, bb.width + margin * 2, bb.height + margin * 2);
}

void StrokeTool::initialize() {
    isInitialized = true;
}

void StrokeTool::setupMain() {
}

void StrokeTool::activateMain() {
    base.allocate(boundingBox.width, boundingBox.height, fboDepth, samplingDepth);
    original.allocate(boundingBox.width, boundingBox.height, fboDepth, samplingDepth);
    
    original.begin();
    ofPushMatrix();
    canvas->draw(-boundingBox.x, -boundingBox.y);
    ofPopMatrix();
    original.end();
    
    base.begin();
    ofClear(0, 0, 0);
    style->begin();
    ofTranslate(-boundingBox.x, -boundingBox.y);
    mesh.draw();
    style->end();
    base.end();
}

void StrokeTool::updateMain() {
    canvas->begin();
    style->beginPrint();
    style->getPrintShader().setUniformTexture("original", original, 1);
    base.draw(boundingBox.x, boundingBox.y);
    style->endPrint();
    canvas->end();
    finalize();
}

void StrokeTool::debugDraw() {
    ofPushStyle();
    ofNoFill();
    ofSetColor(style->getDebugColor());
    ofDrawRectangle(boundingBox);
    shape.draw();
    ofPopStyle();
}

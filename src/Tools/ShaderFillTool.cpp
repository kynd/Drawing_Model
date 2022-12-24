#include "ShaderFillTool.hpp"

bool ShaderFillTool::isInitialized = false;

ShaderFillTool::ShaderFillTool(shared_ptr<ofFbo> _canvas, float _priority, shared_ptr<ShaderFill> _fill, ofPolyline _shape) : Tool(_canvas, _priority) {
    
    type = POLYLINE;
    if (!isInitialized && !animationDebugFlag) { initialize(); }
    shape = _shape;
    fill = _fill;
    maxCnt = fill->nIterations;
    pathShape = PolyLineUtil::polylineToPath(shape);
    pathShape.setFillColor(ofColor(255));
    pathShape.setStrokeColor(ofColor(255));
    
    ofRectangle bb = shape.getBoundingBox();
    boundingBox = ofRectangle(bb.x - margin, bb.y - margin, bb.width + margin * 2, bb.height + margin * 2);
    
    
    boundingBox.x = round(boundingBox.x);
    boundingBox.y = round(boundingBox.y);
    boundingBox.width = round(boundingBox.width);
    boundingBox.height = round(boundingBox.height);
    
    setup();
}

ShaderFillTool::ShaderFillTool(shared_ptr<ofFbo> _canvas, float _priority, shared_ptr<ShaderFill> _fill, ofFbo fbo, ofVec2f pos) : Tool(_canvas, _priority) {
    type = FBO;
    if (!isInitialized && !animationDebugFlag) { initialize(); }
    
    fill = _fill;
    maxCnt = fill->nIterations;
    boundingBox = ofRectangle(pos.x - margin, pos.y - margin, fbo.getWidth() + margin * 2, fbo.getHeight() + margin * 2);
    
    base.allocate(boundingBox.width, boundingBox.height, fboDepth, samplingDepth);
    base.begin();
    fbo.draw(margin, margin);
    base.end();
    
    setup();
}


void ShaderFillTool::initialize() {
    isInitialized = true;
}

void ShaderFillTool::setupMain() {
    if (type != POLYLINE) {return;}
    
    base.allocate(boundingBox.width, boundingBox.height, fboDepth, 4);
    base.begin();
    ofPushMatrix();
    ofTranslate(-boundingBox.x, -boundingBox.y);
    pathShape.draw();
    ofPopMatrix();
    base.end();
    
}

void ShaderFillTool::activateMain() {
    
    canvasCopy.allocate(boundingBox.width, boundingBox.height, fboDepth, samplingDepth);
    
    canvasCopy.begin();
    ofPushMatrix();
    canvas->draw(-boundingBox.x, -boundingBox.y);
    ofPopMatrix();
    canvasCopy.end();
    
    if (maxCnt > 1) {
        pingpong[0].allocate(boundingBox.width, boundingBox.height, fboDepth, samplingDepth);
        pingpong[1].allocate(boundingBox.width, boundingBox.height, fboDepth, samplingDepth);
        pingpong[0].begin();
        ofPushMatrix();
        canvas->draw(-boundingBox.x, -boundingBox.y);
        ofPopMatrix();
        pingpong[0].end();
    }
    
    fill->preprocess(base);
}

void ShaderFillTool::updateMain() {
    if (maxCnt > 1) {
        updateMainPingPong();
    } else {
        updateMainSingle();
    }
}

void ShaderFillTool::updateMainSingle() {
    canvas->begin();
    ofPushMatrix();
    ofTranslate(boundingBox.getTopLeft());
    fill->begin();
    fill->getShader().setUniform4f("bounds", boundingBox.x, boundingBox.y, boundingBox.width, boundingBox.height);
    fill->getShader().setUniformTexture("canvasCopy", canvasCopy, 1);
    base.draw(0, 0);
    fill->end();
    ofPopMatrix();
    ofPopStyle();
    canvas->end();

    finalize();
}

void ShaderFillTool::updateMainPingPong() {
    int i0 = pIdx;
    int i1 = (pIdx + 1) % 2;
    
    // PingPong
    pingpong[i1].begin();
    fill->begin();
    fill->getShader().setUniform4f("bounds", boundingBox.x, boundingBox.y, boundingBox.width, boundingBox.height);
    
    fill->getShader().setUniform2f("res", BUFF_WIDTH, BUFF_HEIGHT);
    fill->getShader().setUniformTexture("base", base, 1);
    fill->getShader().setUniformTexture("canvasCopy", canvasCopy, 2);
    pingpong[i0].draw(0, 0);
    
    fill->end();
    pingpong[i1].end();
    pIdx = i1;
    
    // Draw pn canvas
    canvas->begin();
    ofPushMatrix();
    ofTranslate(boundingBox.getTopLeft());
    pingpong[pIdx].draw(0, 0);
    ofPopMatrix();
    ofPopStyle();
    canvas->end();
    
    // progress
    cnt ++;
    if (cnt >= maxCnt) {
        finalize();
    }
}

void ShaderFillTool::debugDraw() {
    ofPushStyle();
    ofNoFill();
    ofDrawRectangle(boundingBox);
    if (type == POLYLINE) {
        shape.draw();
    } else {
        base.draw(boundingBox.x, boundingBox.y);
    }
    ofPopStyle();
}

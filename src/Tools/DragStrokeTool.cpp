#include "DragStrokeTool.hpp"

bool DragStrokeTool::isInitialized = false;
ofShader DragStrokeTool::drawShader;
ofShader DragStrokeTool::updateShader;
ofShader DragStrokeTool::noiseShader;
ofFbo DragStrokeTool::dummy;
ofFbo DragStrokeTool::noise;

DragStrokeTool::DragStrokeTool(shared_ptr<ofFbo> _canvas, float _priority,
                               ofPolyline _lineA,
                               ofPolyline _lineB,
                               ofFloatColor _cbl,
                               ofFloatColor _cbr,
                               ofFloatColor _cel,
                               ofFloatColor _cer,
                               ofFloatColor _bg)
: Tool(_canvas, _priority) {
    
    if (!isInitialized && !animationDebugFlag) { initialize(); }
    lineA = _lineA;
    lineB = _lineB;
    cbl = _cbl;
    cbr = _cbr;
    cel = _cel;
    cer = _cer;
    bg = _bg;
    ofRectangle bb = lineA.getBoundingBox();
    bb = bb.getUnion(lineB.getBoundingBox());
    boundingBox = ofRectangle(bb.x - margin, bb.y - margin, bb.width + margin * 2, bb.height + margin * 2);
    
    float lenL = lineA.getLengthAtIndex(lineA.getVertices().size() - 1);
    float lenR = lineB.getLengthAtIndex(lineB.getVertices().size() - 1);
    length = max(lenL, lenR);
    setup();
}

void DragStrokeTool::initialize() {
    isInitialized = true;
    drawShader.load("shader/basic.vs", "shader/dragStroke/stroke.fs");
    updateShader.load("shader/basic.vs", "shader/dragStroke/update.fs");
    noiseShader.load("shader/basic.vs", "shader/dragStroke/noise.fs");
    
    noise.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    dummy.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    noise.begin();
    ofClear(255, 255, 255, 255);
    noiseShader.begin();
    noiseShader.setUniform1f("time", ofGetSeconds());
    noiseShader.setUniform2f("res", ofVec2f(BUFF_WIDTH, BUFF_HEIGHT));
    dummy.draw(0, 0, BUFF_WIDTH, BUFF_HEIGHT);
    noiseShader.end();
    noise.end();
}

void DragStrokeTool::setupMain() {
}

void DragStrokeTool::activateMain() {
    strokeFbo[0].allocate(1024, 1, fboDepth, samplingDepth);
    strokeFbo[1].allocate(1024, 1, fboDepth, samplingDepth);
}

void DragStrokeTool::updateMain() {
    for (int i = 0; i < 1; i ++) {
        updateMainLoop();
        if (pos >= 1.0) { finalize(); break; }
        pos = min(1.0, pos + 0.5 / length);
    }
}

void DragStrokeTool::updateMainLoop() {
    ofPoint p0, p1;
    p0 = lineA.getPointAtPercent(pos + 5.0 / length);
    p1 = lineB.getPointAtPercent(pos + 5.0 / length);
    
    int a = pIdx;
    int b = (pIdx + 1) % 2;
    
    //cout << bg;
    strokeFbo[b].begin();
    updateShader.begin();
    updateShader.setUniformTexture("canvas", *canvas, 1);
    updateShader.setUniformTexture("noiseBuffer", noise, 2);
    updateShader.setUniform1i("isFirstFrame", isFirstFrame);
    updateShader.setUniform3f("p0", p0);
    updateShader.setUniform3f("p1", p1);
    updateShader.setUniform4f("cbl", cbl);
    updateShader.setUniform4f("cbr", cbr);
    updateShader.setUniform4f("cel", cel);
    updateShader.setUniform4f("cer", cer);
    updateShader.setUniform4f("bg", bg);
    updateShader.setUniform1f("pos", pos);
    strokeFbo[a].draw(0, 0);
    updateShader.end();
    strokeFbo[b].end();
    
    pIdx = b;
    isFirstFrame = false;
    
    p0 = lineA.getPointAtPercent(pos);
    p1 = lineB.getPointAtPercent(pos);
    
    canvas->begin();
    drawShader.begin();
    drawShader.setUniform3f("p0", p0);
    drawShader.setUniform3f("p1", p1);
    drawShader.setUniformTexture("map", strokeFbo[pIdx], 1);
    ofDrawLine(p0, p1);
    drawShader.end();
    canvas->end();
    
    if (pos >= 1.0) { finalize(); }
    pos = min(1.0, pos + 0.5 / length);
}


void DragStrokeTool::debugDraw() {
    ofPushStyle();
    ofNoFill();
    ofDrawRectangle(boundingBox);
    ofSetColor(cbl);
    lineA.draw();
    ofSetColor(cbr);
    lineB.draw();
    ofPopStyle();
}

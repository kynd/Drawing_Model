#include "_RoughEdgeStrokeTool.hpp"

bool RoughEdgeStrokeTool::isInitialized = false;
ofShader RoughEdgeStrokeTool::strokeShader;
ofShader RoughEdgeStrokeTool::roughEdgeShader;
ofShader RoughEdgeStrokeTool::noiseShader;
ofFbo RoughEdgeStrokeTool::noise;
ofFbo RoughEdgeStrokeTool::dummy;

RoughEdgeStrokeTool::RoughEdgeStrokeTool(shared_ptr<ofFbo> _canvas, int _priority, ofPolyline _shape, float _width, ofColor _color) : Tool(_canvas, _priority) {
    
    if (!isInitialized && !animationDebugFlag) { initialize(); }
    color = _color;
    shape = _shape;
    margin = max(margin, int(_width));
    mesh = PolyLineUtil::toStrokeMesh(shape, _width, shape.getVertices().size() * 4);
    ofRectangle bb = shape.getBoundingBox();
    boundingBox = ofRectangle(bb.x - margin, bb.y - margin, bb.width + margin * 2, bb.height + margin * 2);
    setup();
}

void RoughEdgeStrokeTool::initialize() {
    isInitialized = true;
    
    
    strokeShader.load("shader/basic.vs", "shader/roughEdgeStroke/stroke.fs");
    roughEdgeShader.load("shader/basic.vs", "shader/roughEdgeStroke/roughEdge.fs");
    noiseShader.load("shader/basic.vs", "shader/roughEdgeStroke/noise.fs");
    
    noise.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    dummy.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    
    noise.begin();
    ofClear(0, 0, 0, 255);
    noiseShader.begin();
    noiseShader.setUniform2f("res", BUFF_WIDTH, BUFF_HEIGHT);
    dummy.draw(0, 0);
    noiseShader.end();
    noise.end();
    
}

void RoughEdgeStrokeTool::setupMain() {
}

void RoughEdgeStrokeTool::activateMain() {
    
    base.allocate(boundingBox.width, boundingBox.height, fboDepth, samplingDepth);
    original.allocate(boundingBox.width, boundingBox.height, fboDepth, samplingDepth);
    
    original.begin();
    ofPushMatrix();
    canvas->draw(-boundingBox.x, -boundingBox.y);
    ofPopMatrix();
    original.end();
    
    base.begin();
    ofClear(0, 0, 0);
    strokeShader.begin();
    strokeShader.setUniform4f("color", color);
    ofTranslate(-boundingBox.x, -boundingBox.y);
    mesh.draw();
    strokeShader.end();
    base.end();
}

void RoughEdgeStrokeTool::updateMain() {
    canvas->begin();
    roughEdgeShader.begin();
    roughEdgeShader.setUniformTexture("original", original, 1);
    roughEdgeShader.setUniformTexture("noise", noise, 2);
    roughEdgeShader.setUniform4f("color", color);
    base.draw(boundingBox.x, boundingBox.y);
    roughEdgeShader.end();
    canvas->end();
    finalize();
}

void RoughEdgeStrokeTool::debugDraw() {
    ofPushStyle();
    ofNoFill();
    ofSetColor(color);
    ofDrawRectangle(boundingBox);
    shape.draw();
    ofPopStyle();
}

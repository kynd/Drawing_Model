#include "TestTool.hpp"

TestTool::TestTool(shared_ptr<ofFbo> _canvas, float _priority, ofVec3f  _p0, ofVec3f _p1, ofColor _color) : Tool(_canvas, _priority) {
    
    p0 = _p0;
    p1 = _p1;
    color = _color;
    maxCnt = ofRandom(100, 200);
    
    float minX = min(p0.x, p1.x) - size;
    float maxX = max(p0.x, p1.x) + size;
    float minY = min(p0.y, p1.y) - size;
    float maxY = max(p0.y, p1.y) + size;
    boundingBox = ofRectangle(minX, minY, maxX - minX, maxY - minY);
}

void TestTool::updateMain() {
    float ang = ofRandom(PI);
    float d = ofRandom(size);
    ofVec2f offset = ofVec2f(cos(ang), sin(ang)) * d;
    ofVec2f dir = (p1 - p0).getNormalized();
    float length = (p1 - p0).length();
    float dOffset = ofRandom(length);
    ofVec2f sp = p0 + offset + dir * dOffset;
    ofVec2f ep = p0 + offset + dir * (dOffset + 10);
    
    canvas->begin();
    ofPushStyle();
    ofSetColor(color);
    ofDrawLine(sp, ep);
    ofPopStyle();
    canvas->end();
    
    cnt ++;
    if (cnt >= maxCnt) {
        state = Tool::COMPLETE;
    }
}

void TestTool::debugDraw() {
    ofPushStyle();
    ofNoFill();
    ofSetColor(color);
    ofDrawRectangle(boundingBox);
    
    ofDrawCircle(p0, 4);
    ofDrawCircle(p1, 4);
    ofPopStyle();
}

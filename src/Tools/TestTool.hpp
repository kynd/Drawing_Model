#pragma once

#include "const.h"
#include "ofMain.h"
#include "Tool.hpp"


class TestTool : public Tool {
public:
    TestTool(shared_ptr<ofFbo> _canvas, int _priority, ofVec3f _p0, ofVec3f _p1, ofColor _color);
    virtual void updateMain();
    virtual void debugDraw();
    
protected:
    ofVec3f p0, p1;
    int cnt = 0;
    int maxCnt = 0;
    float size = 20;
    ofColor color;
};

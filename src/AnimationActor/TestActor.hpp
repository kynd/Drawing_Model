#pragma once

#include "AnimationActor.hpp"

class TestActor : public AnimationActor {
public:
    TestActor(int div = 0);
    virtual void update();
    virtual void updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor);
    virtual void drawMain();
    
    ofPolyline createShape();
protected:
    int loopLength = 60;
    vector<ofRectangle> rects;
    ofRectangle rect;
    ofPolyline lines[2];
    ofPolyline line;
    ofFloatColor colors[4];
    ColorSampler colorSampler;
    ofVec2f dirs[2];
    float breadths[2];
    float centers[2];
};

#pragma once

#include "const.h"
#include "ofMain.h"
#include "Runnable.hpp"
#include "Conductor.hpp"
#include "common_includes.h"

class AnimationActor : public Runnable {
public:
    virtual void setPosition(ofVec2f _center, ofVec2f _scale);
    virtual void update();
    virtual void updateConductor(shared_ptr<ofFbo> _canvas, Conductor& conductor);
    virtual void draw();
    virtual void drawMain();
protected:
    int frameCount = 0;
    ofVec2f dispCenter = ofVec2f(0, 0);
    ofVec2f dispScale = ofVec2f(1, 1);
};

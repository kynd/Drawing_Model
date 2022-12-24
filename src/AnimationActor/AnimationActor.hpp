#pragma once

#include "const.h"
#include "ofMain.h"
#include "Runnable.hpp"
#include "Conductor.hpp"
#include "common_includes.h"

class AnimationActor : public Runnable {
public:
    virtual void update();
    virtual void updateConductor(shared_ptr<ofFbo> _canvas, Conductor& conductor);
    virtual void draw();
    virtual void drawMain();
protected:
    int frameCount = 0;
};

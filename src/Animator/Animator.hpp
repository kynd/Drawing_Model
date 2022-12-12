#pragma once

#include "const.h"
#include "ofMain.h"
#include "Conductor.hpp"

#include "common_includes.h"

class Animator {
public:
    virtual void init(shared_ptr<ofFbo> _canvas);
    virtual void update(Conductor& conductor);
protected:
    int frameCount = 0;
    shared_ptr<ofFbo> canvas;
};

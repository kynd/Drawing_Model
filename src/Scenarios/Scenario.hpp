#pragma once

#include "const.h"
#include "ofMain.h"

#include "Conductor.hpp"
#include "common_includes.h"

class Scenario {
public:
    Scenario();
    virtual void update();
    virtual void next();
    virtual void draw();
    
    shared_ptr<ofFbo> canvas;
    Conductor conductor;
    ofFloatColor backgroundColor;
    ColorSampler colorSampler;
};

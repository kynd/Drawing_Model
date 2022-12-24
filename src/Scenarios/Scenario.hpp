#pragma once

#include "const.h"
#include "ofMain.h"
#include "Runnable.hpp"
#include "Conductor.hpp"
#include "common_includes.h"

#include "VideoSaver.hpp"

class Scenario : public Runnable {
public:
    Scenario();
    virtual void update();
    virtual void next();
    virtual void draw();
    virtual void save();
    
    shared_ptr<ofFbo> canvas;
    Conductor conductor;
    ofFloatColor backgroundColor;
    ColorSampler colorSampler;
    VideoSaver vs;
};

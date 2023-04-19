#pragma once

#include "Scenario.hpp"
#include "const.h"
#include "ofMain.h"
#include "Conductor.hpp"
#include "ColorSampler.hpp"
#include "WavePhysicsAnimator.hpp"
#include "SquareLoopAnimator.hpp"
#include "BlobDanceAnimator.hpp"
#include "BrushWaveAnimator.hpp"
#include "TestAnimator.hpp"



class AnimationScenario : public Scenario {
public:
    AnimationScenario();
    virtual void draw();
    void clearBackground();
    shared_ptr<ofFbo> canvas;
    
    TestAnimator animater;
    ofFloatColor backgroungColor;
    int nImage = 0;
    ToolUtil toolUtil;
};


#pragma once

#include "SketchScenario.hpp"
#include "VideoSaver.hpp"

#include "MaskProcessAnimator.hpp"
#include "PlanetAnimator.hpp"



class StepScenario : public SketchScenario {
public:
    StepScenario();
    
    virtual void next();
    virtual void draw();
    
    PlanetAnimator animator;
    VideoSaver vs;
};


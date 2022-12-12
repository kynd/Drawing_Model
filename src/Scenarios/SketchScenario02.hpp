#pragma once

#include "SketchScenario.hpp"

class SketchScenario02 : public SketchScenario {
public:
    SketchScenario02();
    
    virtual void next();
    virtual void shaderFillTest();
    virtual void lineTest();
    virtual void lineTestSpecific();
    virtual void maskTest();
    virtual void groupTest();
};


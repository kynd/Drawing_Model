#pragma once

#include "SketchScenario.hpp"
#include "ShapeMorphActor.hpp"
#include "BoxActor.hpp"

class SketchScenario02 : public SketchScenario {
public:
    SketchScenario02();
    
    virtual void next();
    virtual void draw();
    
    virtual void trunksTest();
    virtual void vainTest();
    virtual void leafTest4();
    virtual void leafTest3();
    virtual void leafTest2();
    virtual void leafTest();
    virtual void curtainTest();
    virtual void orderTest();
    virtual void starTest();
    virtual void treeTest();
    virtual void pathMorphTest();
    virtual void shaderFillTest();
    
    virtual void randomBgTest();
    virtual void dottedLineTest();
    virtual void lineTest();
    virtual void lineTestSpecific();
    virtual void maskTest();
    virtual void groupTest();
    
    
    ShapeMorphActor shapeMorphActor;
    BoxActor boxActor;
};


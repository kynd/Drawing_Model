#pragma once

#include "SketchScenario.hpp"
#include "ShapeMorphActor.hpp"
#include "BoxActor.hpp"

class SketchScenario02 : public SketchScenario {
public:
    SketchScenario02();
    
    virtual void next();
    virtual void draw();
    vector<ofPolyline> randomPaths(ofRectangle rect);
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


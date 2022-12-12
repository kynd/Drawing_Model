
#pragma once

#include "Animator.hpp"
#include "MaskTool.hpp"


struct PlanetDef {
    PlanetDef(shared_ptr<ShaderFill> _fillA, shared_ptr<ShaderFill> _fillB, ofRectangle _rect, float _ang, float _rot) {
        fillA = _fillA;
        fillB = _fillB;
        rect = _rect;
        ang = _ang;
        rot = _rot;
    }
    shared_ptr<ShaderFill> fillA;
    shared_ptr<ShaderFill> fillB;
    ofRectangle rect;
    float ang;
    float rot;
};


class PlanetAnimator : public Animator {
public:
    void init(shared_ptr<ofFbo> _canvas);
    void update(Conductor& conductor);
    shared_ptr<ShaderFill> randomFill();
    
    vector<vector<PlanetDef> > defs;
    vector<vector<PlanetDef> > defs2;
    int n = 3;
    ColorSampler colorSampler;
    int step;
    ofFloatColor backgroundColor;
};

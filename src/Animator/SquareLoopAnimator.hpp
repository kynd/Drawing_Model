#pragma once

#include "Animator.hpp"


class SquareLoopAnimator : public Animator {
public:
    void init(shared_ptr<ofFbo> _canvas);
    void update(Conductor& conductor);
    shared_ptr<ShaderFill> randomShaderFill();
    float powerInOut(float t, float a = 2);
private:
    int frameCount = 0;
    shared_ptr<ofFbo> canvas;
    
    vector<shared_ptr<ShaderFill> > fills;
    ColorSampler colorSampler;
    
    
    
    ofFloatColor colorA;
    ofFloatColor colorB;
};

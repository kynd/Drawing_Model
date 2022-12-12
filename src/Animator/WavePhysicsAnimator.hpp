#pragma once

#include "Animator.hpp"


class WavePhysicsAnimator : public Animator {
public:
    void init(shared_ptr<ofFbo> _canvas);
    void initWave();
    void update(Conductor& conductor);
    void updateSimulation(int iN, int iC, int iP);
    void createTools(int iN, Conductor& conductor);
private:
    int frameCount = 0;
    shared_ptr<ofFbo> canvas;
    ColorSampler colorSampler;
    ofFloatColor colorA, colorB, colorC, colorD, colorE;
    ofVec2f dirA, dirB;
    
    vector<vector<float> > up;
};

#pragma once

#include "AnimationActor.hpp"


class WaveFill {
public:
    WaveFill();
    shared_ptr<Tool> linesToTool(shared_ptr<ofFbo> canvas, ofPolyline lA, ofPolyline lB);
    
    float priority;
    
    shared_ptr<ShaderFill> fill;
    static bool initialized;
    static ColorSampler colorSampler;
};

class WaveTideActor : public AnimationActor {
public:
    WaveTideActor();
    virtual void update();
    virtual void updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor);
    virtual void drawMain();
    
protected:
    float w = BUFF_WIDTH * 3.0;
    float h = BUFF_HEIGHT * 1.2;
    int nLines = 4;
    int stepLength = 60;
    vector<float> basePoints;
    vector<ofPolyline> lines;
    vector<WaveFill> wavefills;
};

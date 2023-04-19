#pragma once

#include "AnimationActor.hpp"
#include "VideoSaver.hpp"

class Ball {
public:
    Ball(ofVec2f p, ofVec2f v, float r);
    void update();
    void updateShape();
    void updateBounds();
    void checkBorders();
    void react(Ball* b);
    float getBoundOffset(ofVec2f p);
    void calcBounds(Ball* b);
    ofVec2f getSidePoint(int i);
    
    float radius;
    float maxVec = 15;
    ofVec2f pos, vel, paintDir, grav;
    ofFloatColor colorA, colorB;
    int res;
    vector<float> boundOffset, boundOffsetBuff;
    ofPolyline line;
    ToolUtil toolUtil;
};

class CandyClashActor : public AnimationActor {
public:
    CandyClashActor();
    virtual void update();
    virtual void updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor);
    virtual void drawMain();
protected:
    vector<Ball> balls;
    ToolUtil toolUtil;
};

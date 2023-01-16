#pragma once

#include "AnimationActor.hpp"


class OrbitObj {
public:
    OrbitObj(ofVec3f _pos, ofVec3f _vel, float _mass);
    void update();
    ofVec3f pos, vel;
    float mass;
    deque<ofVec3f> trail;
};

class OrbitActor : public AnimationActor {
public:
    OrbitActor();
    virtual void update();
    virtual void updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor);
    virtual void drawMain();
    
protected:
    float w = BUFF_WIDTH * 3.0;
    float h = BUFF_HEIGHT * 1.2;
    int nLines = 4;
    int stepLength = 60;
    vector<float> basePoints;
    vector<vector<ofPolyline> > lines;
    vector<OrbitObj> objs;
};

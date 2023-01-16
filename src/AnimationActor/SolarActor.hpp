#pragma once

#include "AnimationActor.hpp"
#include "VideoSaver.hpp"

class SolarEntityDef {
    
public:
    SolarEntityDef();
    void setParent(shared_ptr<SolarEntityDef> _parent);
    void update();
    
    float w;
    ofFloatColor strokeColor;
    vector<ofPolyline> lines;
    vector<ofPolyline> trailLines;
    bool hasParent = false;
    shared_ptr<SolarEntityDef> parent;
    ofVec3f pos, baseDir, axis;
    float size, speed, angle, rot, rotSpeed;
    
    deque<ofVec3f> trail;
    
    vector<shared_ptr<ShaderFill> > fills;
    ToolUtil toolUtil;
};

class SolarActor : public AnimationActor {
public:
    SolarActor();
    virtual void setPosition(ofVec2f _center, ofVec2f _scale);
    void updateBoundaryBase();
    virtual void update();
    //bool compareEntities(SolarEntityDef a, SolarEntityDef b);
    virtual void updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor);
    virtual void drawMain();
protected:
    ofPolyline boundaryLineBase;
    ofPolyline boundaryLine;
    shared_ptr<ShaderFill> boudaryFill;
    vector<shared_ptr<SolarEntityDef> > entities;
    
    ToolUtil toolUtil;
};



#pragma once

#include "AnimationActor.hpp"
#include "VideoSaver.hpp"

class DrapeTileDef {
public:
    DrapeTileDef();
    void update(ofVec3f _p0, ofVec3f _p1, ofVec3f _p2, ofVec3f _p3, ofFloatColor _color);
    void AddVerts(ofPolyline & line, ofVec3f pa, ofVec3f pb);
    ofVec3f p0, p1, p2, p3;
    ofVec2f d;
    ofPolyline polyline;
    ofFloatColor baseColor, color;
    ToolUtil toolUtil;
};

class DrapeActor : public AnimationActor {
public:
    DrapeActor();
    virtual void setPosition(ofVec2f _center, ofVec2f _scale);
    virtual void update();
    //bool compareEntities(DrapeEntityDef a, DrapeEntityDef b);
    virtual void updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor);
    virtual void drawMain();
protected:
    
    int xDiv = 72, yDiv = 24;
    ofVec3f a0, a1, a2, a3;
    
    vector<vector<ofVec2f> > points;
    vector<DrapeTileDef> tiles;
    ToolUtil toolUtil;
};

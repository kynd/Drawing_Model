#pragma once

#include "AnimationActor.hpp"
#include "VideoSaver.hpp"

class BoxDef {
public:
    BoxDef();
    void updatePoints();
    void update();
    void updateTarget(bool reset = false);
    
    vector<ofVec3f> points;
    vector<vector<int> > edges;
    vector<vector<int> > faces;
    vector<shared_ptr<ShaderFill> > fills;
    ofFloatColor strokeColor;
    
    int frameCount = 0;
    int moveLen = 30;
    float rot, pRot, tRot, iRot;
    ofVec3f center, size, pCenter, pSize, tCenter, tSize, iCenter, iSize;
    ofVec3f axis;
    vector<ofPolyline> edgeLines;
    vector<ofPolyline> faceLines;
    float baseSpan, span, lineWidth;
    ToolUtil toolUtil;
};


class BoxActor : public AnimationActor {
public:
    BoxActor();
    virtual void update();
    virtual void updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor);
    virtual void drawMain();
protected:
    vector<BoxDef> boxes;
    VideoSaver v;
};

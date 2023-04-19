#pragma once

#include "AnimationActor.hpp"
#include "VideoSaver.hpp"
#include "Squishy.hpp"
#include "I_Tree.hpp"

class TreeActor : public AnimationActor {
public:
    TreeActor();
    virtual void update();
    virtual void updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor);
    virtual void drawMain();
protected:
    vector<shared_ptr<ShaderFill> > fills;
    vector<shared_ptr<StrokeStyle> > styles;
    vector<ofPolyline> lines;
    ToolUtil toolUtil;
    ofFloatColor color;
};

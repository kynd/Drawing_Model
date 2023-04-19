#pragma once

#include "AnimationActor.hpp"
#include "VideoSaver.hpp"
#include "Squishy.hpp"

class SquishyActor : public AnimationActor {
public:
    SquishyActor();
    virtual void update();
    virtual void updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor);
    virtual void drawMain();
protected:
    vector<Squishy> squishies;
    ToolUtil toolUtil;
};

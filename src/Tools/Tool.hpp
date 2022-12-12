#pragma once

#include "const.h"
#include "ofMain.h"
#include "ShaderFill.hpp"
#include "PolyLineUtil.hpp"

class Tool {
public:
    enum States {STANDBY, ACTIVE, COMPLETE};
    
    Tool(shared_ptr<ofFbo> _canvas, int _priority = 0);
    
    virtual ofRectangle getBoundingBox();
    virtual int getPriority();
    virtual States getState();
    virtual void setup();
    virtual void setupMain();
    virtual void activate();
    virtual void activateMain();
    virtual void update();
    virtual void updateMain();
    virtual void finalize();
    virtual void finalizeMain();
    virtual void debugDraw();
    
protected:
    States state = STANDBY;
    shared_ptr<ofFbo> canvas;
    ofRectangle boundingBox;
    int priority;
};

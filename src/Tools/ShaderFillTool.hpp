#pragma once

#include "Tool.hpp"
#include "ShaderFill.hpp"

class ShaderFillTool : public Tool {
public:
    ShaderFillTool(shared_ptr<ofFbo> _canvas, float _priority, shared_ptr<ShaderFill> _fill, ofPolyline _shape);
    
    ShaderFillTool(shared_ptr<ofFbo> _canvas, float _priority, shared_ptr<ShaderFill> _fill, ofFbo fbo, ofVec2f pos);
    virtual void setupMain();
    virtual void activateMain();
    virtual void updateMain();
    virtual void firstUpdate();
    virtual void updateMainSingle();
    virtual void updateMainPingPong();
    virtual void debugDraw();
    
protected:
    enum Type {POLYLINE, FBO};
    static void initialize();
    
    Type type = POLYLINE;
    shared_ptr<ShaderFill> fill;
    ofPolyline shape;
    ofPath pathShape;
    int cnt = 0;
    int maxCnt = 0;
    int margin = 64;
    ofFbo base, canvasCopy;
    ofFbo pingpong[2];
    int pIdx = 0;
    
    bool wasUpdated = false;
    static bool isInitialized;
};

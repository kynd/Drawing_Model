#pragma once

#include "Tool.hpp"
#include "PolylineUtil.hpp"
#include "StrokeStyle.hpp"

class StrokeTool : public Tool {
public:
    
    StrokeTool(shared_ptr<ofFbo> _canvas, int _priority, shared_ptr<StrokeStyle> _style, ofPolyline _shape, float _width, ofPolyline _taper);
    virtual void setupMain();
    virtual void activateMain();
    virtual void updateMain();
    virtual void firstUpdate();
    virtual void debugDraw();
    
protected:
    static void initialize();
    
    shared_ptr<StrokeStyle> style;
    ofPolyline shape, taper;
    ofMesh mesh;
    float width;
    int resolution;
    int margin = 32;
    ofFbo base, original;
    
    bool wasUpdated = false;
    static bool isInitialized;
};

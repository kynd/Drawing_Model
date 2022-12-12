#pragma once

#include "const.h"
#include "ofMain.h"
#include "Tool.hpp"
#include "PolylineUtil.hpp"

class RoughEdgeStrokeTool : public Tool {
public:
    
    RoughEdgeStrokeTool(shared_ptr<ofFbo> _canvas, int _priority, ofPolyline _shape, float _width, ofColor _color);
    
    virtual void setupMain();
    virtual void activateMain();
    virtual void updateMain();
    virtual void debugDraw();
    
protected:
    static void initialize();
    
    ofPolyline shape;
    ofMesh mesh;
    int margin = 32;
    ofColor color;
    ofFbo base, original;
    static bool isInitialized;
    static ofShader noiseShader, strokeShader, roughEdgeShader;
    static ofFbo noise, dummy;
};

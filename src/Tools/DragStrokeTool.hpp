#pragma once

#include "const.h"
#include "ofMain.h"
#include "Tool.hpp"
#include "PolylineUtil.hpp"

class DragStrokeTool : public Tool {
public:
    
    DragStrokeTool(shared_ptr<ofFbo> _canvas, float _priority,
                   ofPolyline _lineA,
                   ofPolyline _lineB,
                   ofFloatColor _cbl,
                   ofFloatColor _cbr,
                   ofFloatColor _cel,
                   ofFloatColor _cer,
                   ofFloatColor _bg);
    
    virtual void setupMain();
    virtual void activateMain();
    virtual void updateMain();
    virtual void updateMainLoop();
    virtual void debugDraw();
    
protected:
    static void initialize();
    static bool isInitialized;
    bool isFirstFrame = true;
    ofPolyline lineA, lineB;
    ofFloatColor cbl, cbr, cel, cer, bg;
    ofFbo strokeFbo[2];
    int pIdx = 0;
    int margin = 32;
    float pos = 0.0;
    float length;
    static ofShader drawShader, updateShader, noiseShader;
    static ofFbo noise, dummy;
};


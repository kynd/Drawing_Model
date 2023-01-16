#pragma once

#include "const.h"
#include "ofMain.h"
#include "common_includes.h"
#include "ColorSampler.hpp"

class ToolUtil {
public:
    ToolUtil();
    shared_ptr<ShaderFill> getRandomShaderFill();
    shared_ptr<Tool> getRandomPathTool(shared_ptr<ofFbo> _canvas, ofPolyline line, int priority);
    shared_ptr<Tool> getRandomFboTool(shared_ptr<ofFbo> _canvas, ofFbo fbo, ofVec2f pos, int priority);
    shared_ptr<Tool> getRandomStrokeTool(shared_ptr<ofFbo> _canvas, ofPolyline polyline, int priority = 0, float minW = 1, float maxW = 8);
    
    
    ofFloatColor getRandomColor();
    
protected:
    static ColorSampler colorSampler;
    static bool initialized;
};

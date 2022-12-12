#pragma once

#include "Animator.hpp"
#include "MaskTool.hpp"


struct FillDef {
    FillDef(shared_ptr<ShaderFill> _fill, ofPolyline _line) {
        fill = _fill;
        line = _line;
    }
    shared_ptr<ShaderFill> fill;
    ofPolyline line;
};

struct StrokeDef {
    enum Type {BASIC, FLAT, ROUND};
    StrokeDef(shared_ptr<StrokeStyle> _style, ofPolyline _line, Type _type = BASIC) {
        style = _style;
        line = _line;
        type = _type;
    }
    shared_ptr<StrokeStyle> style;
    ofPolyline line;
    Type type;
};



class MaskProcessAnimator : public Animator {
public:
    void init(shared_ptr<ofFbo> _canvas);
    void update(Conductor& conductor);
    
    ofRectangle randRect();
    void createTools(Conductor& conductor);
    virtual void addBlob();
    virtual void addStroke();
    virtual void addMaskBlob();
    virtual void randomizeFills();
    shared_ptr<ShaderFill> randomFill();
    shared_ptr<StrokeStyle> randomStrokeStyle();
    shared_ptr<ShaderFill> randomMaskFill();
    
    shared_ptr<Tool> randomPathTool(shared_ptr<ofFbo> _canvas, ofPolyline polyline, int priority = 0);
    shared_ptr<Tool> randomFboTool(shared_ptr<ofFbo> _canvas, ofFbo fbo, ofVec2f pos, int priority = 0);
    shared_ptr<Tool> randomStrokeTool(shared_ptr<ofFbo> _canvas, ofPolyline polyline, int priority = 0, float minW = 1, float maxW = 8);
    
    int step = 0;
    vector<FillDef> fillDefs;
    vector<FillDef> maskDefs;
    vector<StrokeDef> strokeDefs;
    ColorSampler colorSampler;
    ofFloatColor backgroundColor;
};

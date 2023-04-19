#include "ToolUtil.hpp"

ColorSampler ToolUtil::colorSampler;
bool ToolUtil::initialized;

ToolUtil::ToolUtil() {
    if (!initialized) {
        colorSampler.load(COMMON_COLOR_SOURCE);
        initialized = true;
    }
}

ofFloatColor ToolUtil::getRandomColor() {
    return colorSampler.getRandomColor();
}


shared_ptr<ShaderFill> ToolUtil::getRandomShaderFill() {
    shared_ptr<ShaderFill> fill;
    ofFloatColor colorA = colorSampler.getRandomColor();
    ofFloatColor colorB = colorSampler.getRandomColor();
    ofVec2f dir = VectorUtil::randomVec2();
    float breadth = ofRandom(1.0);
    float center = ofRandom(1.0);
    
    float rnd = ofRandom(16.0);
    if (rnd < 1.0) {
        fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
    } else if (rnd < 2.0) {
        fill = shared_ptr<ShaderFill>(new PaintPatchShaderFill(colorA, colorB, dir));
    } else if (rnd < 3.0) {
        auto _fill = new NoiseGradientShaderFill(colorA, colorB, dir, 0.5, 0.5);
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        fill = shared_ptr<ShaderFill>(_fill);
    } else if (rnd < 4.0) {
        fill = shared_ptr<ShaderFill>(new PaintTextureShaderFill(colorA, colorB, dir));
    } else if (rnd < 5.0) {
        fill = shared_ptr<ShaderFill>(new GradientStripeShaderFill(colorA, colorB, dir * 40));
    } else if (rnd < 6.0) {
        fill = shared_ptr<ShaderFill>(new DotsShaderFill(colorA, colorB, dir * 4.0));
    } else if (rnd < 10.0) {
        fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(colorA, colorB, dir));
    } else if (rnd < 11.0) {
        fill = shared_ptr<ShaderFill>(new MetalicGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
    } else {
        fill = shared_ptr<ShaderFill>(new SlideBleedShaderFill(colorA, colorB, dir.getNormalized() * ofRandom(0.25, 1.0)));
    }
    
    return fill;
}

shared_ptr<ShaderFill> ToolUtil::getRandomShaderFill2() {
    shared_ptr<ShaderFill> fill;
    ofFloatColor colorA = colorSampler.getRandomColor();
    ofFloatColor colorB = colorSampler.getRandomColor();
    ofVec2f dir = VectorUtil::randomVec2();
    float breadth = ofRandom(1.0);
    float center = ofRandom(1.0);
    float rnd = ofRandom(8.0);
    if (rnd < 1.0) {
        fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
    } else if (rnd < 2.0) {
        fill = shared_ptr<ShaderFill>(new PaintPatchShaderFill(colorA, colorB, dir));
    } else if (rnd < 3.0) {
        auto _fill = new NoiseGradientShaderFill(colorA, colorB, dir, 0.5, 0.5);
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        fill = shared_ptr<ShaderFill>(_fill);
    } else if (rnd < 4.0) {
        fill = shared_ptr<ShaderFill>(new PaintTextureShaderFill(colorA, colorB, dir));
    } else if (rnd < 7.0) {
        fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(colorA, colorB, dir));
    } else {
        fill = shared_ptr<ShaderFill>(new SlideBleedShaderFill(colorA, colorB, dir.getNormalized() * ofRandom(0.25, 1.0)));
    }
    
    return fill;
}

shared_ptr<Tool> ToolUtil::getRandomPathTool(shared_ptr<ofFbo> _canvas, ofPolyline line, int priority) {
    auto fill = getRandomShaderFill();
    auto tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, line));
    return tool;
}

shared_ptr<Tool> ToolUtil::getRandomPathTool2(shared_ptr<ofFbo> _canvas, ofPolyline line, int priority) {
    auto fill = getRandomShaderFill2();
    auto tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, line));
    return tool;
}


shared_ptr<Tool> ToolUtil::getRandomFboTool(shared_ptr<ofFbo> _canvas, ofFbo fbo, ofVec2f pos, int priority) {
    
    auto fill = getRandomShaderFill();
    auto tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, fbo, pos));
    return tool;
}


shared_ptr<StrokeStyle> ToolUtil::getRandomStrokeStyle() {
    
    ofFloatColor color = getRandomColor();
    shared_ptr<StrokeStyle> style;
    float rnd = ofRandom(3.0);
    if (rnd < 1.0) {
        style = shared_ptr<StrokeStyle>(new BasicStrokeStyle(color));
    } else if (rnd < 2.0) {
        style = shared_ptr<StrokeStyle>(new RoughEdgeStrokeStyle(color));
    } else {
        float freq = ofRandom(2, 4);
        style = shared_ptr<StrokeStyle>(new StripeStrokeStyle(color, colorSampler.getRandomColor(), freq));
    }
    
    return style;
}


shared_ptr<Tool> ToolUtil::getRandomStrokeTool(shared_ptr<ofFbo> _canvas, ofPolyline polyline, int priority, float minW, float maxW) {
    auto style = getRandomStrokeStyle();
    
    float width = ofRandom(1, 12);
    ofPolyline taper = PolyLineUtil::createTaperNtoN(1, 1);
    
    shared_ptr<Tool> tool = getRandomStrokeToolWithStyle(_canvas, polyline, style, priority, minW, maxW);
    return tool;
}

shared_ptr<Tool> ToolUtil::getRandomStrokeToolWithStyle(shared_ptr<ofFbo> _canvas, ofPolyline polyline, shared_ptr<StrokeStyle> style, int priority, float minW, float maxW) {
    
    float width = ofRandom(1, 12);
    ofPolyline taper = PolyLineUtil::createTaperNtoN(1, 1);
    
    shared_ptr<Tool> tool;
    float rnd = ofRandom(3.0);
    if (rnd < 1.0) {
        tool = shared_ptr<Tool>(new BasicStrokeTool(_canvas, priority, style, polyline, width, taper));
    } else if (rnd < 2.0) {
        tool = shared_ptr<Tool>(new FlatPenStrokeTool(_canvas, priority, style, polyline, width, ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)), taper));
    } else {
        tool = shared_ptr<Tool>(new RoundStrokeTool(_canvas, priority, style, polyline, width, taper));
    }
    return tool;
}

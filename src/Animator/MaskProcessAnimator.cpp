#include "MaskProcessAnimator.hpp"

void MaskProcessAnimator::init(shared_ptr<ofFbo> _canvas) {
    canvas = _canvas;
    colorSampler.load("img/26.jpg");
}


void MaskProcessAnimator::update(Conductor& conductor) {
    conductor.clear();
    
    if (step == 0) {
        fillDefs.clear();
        maskDefs.clear();
        strokeDefs.clear();
        backgroundColor = colorSampler.getRandomColor();
    }
    if (step < 4) {
        addBlob();
    } else if (step < 8) {
        randomizeFills();
        addStroke();
    } else if (step < 9) {
        addMaskBlob();
    }
    
    createTools(conductor);
    step = (step + 1) % 11;
    
    canvas->begin();
    ofClear(backgroundColor);
    canvas->end();
}

void MaskProcessAnimator::addBlob() {
    vector<ofPolyline> lines = Illustrator::createBlobPath(randRect());
    auto fill = randomFill();
    fillDefs.push_back(FillDef(fill, lines[0]));
}


void MaskProcessAnimator::addStroke() {
    vector<ofPolyline> lines = Illustrator::createSquigglePath(randRect());
    auto style = randomStrokeStyle();
    strokeDefs.push_back(StrokeDef(style, lines[0]));
}

void MaskProcessAnimator::addMaskBlob() {
    vector<ofPolyline> lines = Illustrator::createBlobPath(ofRectangle(0, 0, BUFF_WIDTH, BUFF_HEIGHT));
    auto fill = randomMaskFill();
    maskDefs.push_back(FillDef(fill, lines[0]));
}


void MaskProcessAnimator::randomizeFills() {
    for (int i = 0; i < fillDefs.size(); i ++) {
        auto fill = randomFill();
        fillDefs[i].fill = fill;
    }
}


void MaskProcessAnimator::createTools(Conductor& conductor) {
    if (step < 4) {
        for (int i = 0; i < fillDefs.size(); i ++) {
            conductor.addTool(randomStrokeTool(canvas, fillDefs[i].line));
        }
    } else if (step < 9){
        for (int i = 0; i < fillDefs.size(); i ++) {
            auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, i + 5, fillDefs[i].fill, fillDefs[i].line));
            conductor.addTool(tool);
        }
        
        for (int i = 0; i < maskDefs.size(); i ++) {
            auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, 0, maskDefs[i].fill, maskDefs[i].line));
            conductor.addTool(tool);
        }
    } else {
        MaskTool* mt = new MaskTool(canvas, ofRandom(10));
        auto maskTool = shared_ptr<Tool>(mt);
        auto maskDrawer = shared_ptr<Tool>(new ShaderFillTool(mt->getMask(), 0, maskDefs[0].fill, maskDefs[0].line));
        mt->addMask(maskDrawer);
        conductor.addTool(maskTool);
        for (int i = 0; i < fillDefs.size(); i ++) {
            if (maskTool->getBoundingBox().intersects(fillDefs[i].line.getBoundingBox())) {
                auto tool = shared_ptr<Tool>(new ShaderFillTool(mt->getLocalCanvas(), i + 5, fillDefs[i].fill, fillDefs[i].line));
                mt->addTool(tool);
            } else {
                auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, i + 5, fillDefs[i].fill, fillDefs[i].line));
                conductor.addTool(tool);
            }
        }
        
    }
    
    for (int i = 0; i < strokeDefs.size(); i ++) {
        ofPolyline taper = PolyLineUtil::createTaperNtoN(ofRandom(1.0), ofRandom(1.0));
        auto tool = shared_ptr<Tool>(new BasicStrokeTool(canvas, ofRandom(10), strokeDefs[i].style, strokeDefs[i].line, ofRandom(10, 40), taper));
        
        conductor.addTool(tool);
    }
}


ofRectangle MaskProcessAnimator::randRect() {
    float minSize = BUFF_WIDTH / 4;
    float x = ofRandom(BUFF_WIDTH - minSize);
    float y = ofRandom(BUFF_HEIGHT - minSize);
    float w = ofRandom(minSize, BUFF_WIDTH - x);
    float h = ofRandom(minSize, BUFF_WIDTH - y);
    return ofRectangle(x, y, w, h);
}

shared_ptr<ShaderFill> MaskProcessAnimator::randomFill() {
    ofFloatColor colorA = colorSampler.getRandomColor();
    ofFloatColor colorB = colorSampler.getRandomColor();
    ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)) * 4.0;
    shared_ptr<ShaderFill> fill;
    float rnd = ofRandom(6.0);
    if (rnd < 1.0) {
        fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
    } else if (rnd < 2.0) {
        fill = shared_ptr<ShaderFill>(new PaintPatchShaderFill(colorA, colorB, dir));
    } else if (rnd < 3.0) {
        NoiseGradientShaderFill* _fill = new NoiseGradientShaderFill(colorA, colorB, dir, 0.5, 0.5);
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        fill = shared_ptr<ShaderFill>(_fill);
    } else if (rnd < 4.0) {
        fill = shared_ptr<ShaderFill>(new PaintTextureShaderFill(colorA, colorB, dir));
    } else if (rnd < 5.0) {
        fill = shared_ptr<ShaderFill>(new GradientStripeShaderFill(colorA, colorB, dir));
    } else {
        fill = shared_ptr<ShaderFill>(new DotsShaderFill(colorA, colorB, dir));
    }
    return fill;
}

shared_ptr<StrokeStyle> MaskProcessAnimator::randomStrokeStyle() {
    ofFloatColor color = colorSampler.getRandomColor();
    shared_ptr<StrokeStyle> style;
    
    float rnd = ofRandom(3.0);
    if (rnd < 1.0) {
        style = shared_ptr<StrokeStyle>(new BasicStrokeStyle(color));
    } else if (rnd < 2.0) {
        style = shared_ptr<StrokeStyle>(new RoughEdgeStrokeStyle(color));
    } else {
        float freq = ofRandom(2, 16);
        style = shared_ptr<StrokeStyle>(new StripeStrokeStyle(color, colorSampler.getRandomColor(), freq));
    }
    return style;
}


shared_ptr<ShaderFill> MaskProcessAnimator::randomMaskFill() {
    ofFloatColor colorA = ofFloatColor(1.0, 1.0, 1.0, 1.0);
    ofFloatColor colorB = ofFloatColor(0.0, 0.0, 0.0, 1.0);
    ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)) * 4.0;
    shared_ptr<ShaderFill> fill;
    float rnd = ofRandom(6.0);
    if (rnd < 1.0) {
        fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
    } else if (rnd < 2.0) {
        fill = shared_ptr<ShaderFill>(new PaintPatchShaderFill(colorA, colorB, dir));
    } else if (rnd < 3.0) {
        NoiseGradientShaderFill* _fill = new NoiseGradientShaderFill(colorA, colorB, dir, 0.5, 0.5);
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        fill = shared_ptr<ShaderFill>(_fill);
    } else if (rnd < 4.0) {
        fill = shared_ptr<ShaderFill>(new PaintTextureShaderFill(colorA, colorB, dir));
    } else if (rnd < 5.0) {
        fill = shared_ptr<ShaderFill>(new GradientStripeShaderFill(colorA, colorB, dir));
    } else {
        fill = shared_ptr<ShaderFill>(new DotsShaderFill(colorA, colorB, dir));
    }
    return fill;
}



shared_ptr<Tool> MaskProcessAnimator::randomPathTool(shared_ptr<ofFbo> _canvas, ofPolyline polyline, int priority) {
    shared_ptr<Tool> tool;
    ofFloatColor colorA = colorSampler.getRandomColor();
    ofFloatColor colorB = colorSampler.getRandomColor();
    ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
    
    float rnd = ofRandom(7.0);
    if (rnd < 1.0) {
        auto fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, polyline));
    } else if (rnd < 2.0) {
        auto fill = shared_ptr<ShaderFill>(new PaintPatchShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, polyline));
    } else if (rnd < 3.0) {
        auto _fill = new NoiseGradientShaderFill(colorA, colorB, dir, 0.5, 0.5);
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        shared_ptr<ShaderFill> fill = shared_ptr<ShaderFill>(_fill);
        
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, polyline));
    } else if (rnd < 4.0) {
        auto fill = shared_ptr<ShaderFill>(new PaintTextureShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(canvas, priority, fill, polyline));
    } else if (rnd < 5.0) {
        auto fill = shared_ptr<ShaderFill>(new GradientStripeShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(canvas, priority, fill, polyline));
    } else if (rnd < 6.0) {
        auto fill = shared_ptr<ShaderFill>(new DotsShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(canvas, ofRandom(10), fill, polyline));
    } else {
        auto fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, polyline));
    }
    return tool;
}

shared_ptr<Tool> MaskProcessAnimator::randomFboTool(shared_ptr<ofFbo> _canvas, ofFbo fbo, ofVec2f pos, int priority) {
    shared_ptr<Tool> tool;
    ofFloatColor colorA = colorSampler.getRandomColor();
    ofFloatColor colorB = colorSampler.getRandomColor();
    ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
    
    float rnd = ofRandom(7.0);
    if (rnd < 1.0) {
        auto fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, fbo, pos));
    } else if (rnd < 2.0) {
        auto fill = shared_ptr<ShaderFill>(new PaintPatchShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, fbo, pos));
    } else if (rnd < 3.0) {
        auto _fill = new NoiseGradientShaderFill(colorA, colorB, dir, 0.5, 0.5);
        _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
        shared_ptr<ShaderFill> fill = shared_ptr<ShaderFill>(_fill);
        
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, fbo, pos));
    } else if (rnd < 4.0) {
        auto fill = shared_ptr<ShaderFill>(new PaintTextureShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(canvas, priority, fill, fbo, pos));
    } else if (rnd < 5.0) {
        auto fill = shared_ptr<ShaderFill>(new GradientStripeShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(canvas, priority, fill, fbo, pos));
    } else if (rnd < 6.0) {
        auto fill = shared_ptr<ShaderFill>(new DotsShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(canvas, ofRandom(10), fill, fbo, pos));
    } else {
        auto fill = shared_ptr<ShaderFill>(new WaterBleedShaderFill(colorA, colorB, dir));
        tool = shared_ptr<Tool>(new ShaderFillTool(_canvas, priority, fill, fbo, pos));
    }
    return tool;
}





shared_ptr<Tool> MaskProcessAnimator::randomStrokeTool(shared_ptr<ofFbo> _canvas, ofPolyline polyline, int priority, float minW, float maxW) {
    ofFloatColor color = colorSampler.getRandomColor();
    shared_ptr<Tool> tool;
    shared_ptr<StrokeStyle> style;
    float width;
    
    ofPolyline taper = PolyLineUtil::createTaperNtoN(1, 1);
    float rnd = ofRandom(3.0);
    if (rnd < 1.0) {
        width = ofRandom(1, 12);
        style = shared_ptr<StrokeStyle>(new BasicStrokeStyle(color));
    } else if (rnd < 2.0) {
        width = ofRandom(1, 12);
        style = shared_ptr<StrokeStyle>(new RoughEdgeStrokeStyle(color));
    } else {
        width = ofRandom(4, 12);
        float freq = width / ofRandom(2, 4);
        style = shared_ptr<StrokeStyle>(new StripeStrokeStyle(color, colorSampler.getRandomColor(), freq));
    }
    
    rnd = ofRandom(3.0);
    if (rnd < 1.0) {
        tool = shared_ptr<Tool>(new BasicStrokeTool(_canvas, priority, style, polyline, width, taper));
    } else if (rnd < 2.0) {
        tool = shared_ptr<Tool>(new FlatPenStrokeTool(_canvas, priority, style, polyline, width, ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1)), taper));
    } else {
        tool = shared_ptr<Tool>(new RoundStrokeTool(_canvas, priority, style, polyline, width, taper));
    }
    return tool;
}

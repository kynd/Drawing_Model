#include "SquareLoopAnimator.hpp"

void SquareLoopAnimator::init(shared_ptr<ofFbo> _canvas) {
    canvas = _canvas;
    colorSampler.load("img/26.jpg");
 
    for (int i = 0; i < 32; i ++) {
        fills.push_back(randomShaderFill());
    }
    
}

shared_ptr<ShaderFill> SquareLoopAnimator::randomShaderFill() {
    shared_ptr<ShaderFill> fill;
    ofVec2f dir = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
    
    colorA = colorSampler.getRandomColor();
    colorB = colorSampler.getRandomColor();
    float rnd = ofRandom(1.0);
    auto _fill = new NoiseGradientShaderFill(colorA, colorB, dir, 0.5, 0.5);
    _fill->setRadial(ofVec2f(ofRandom(1.0), ofRandom(1.0)), ofRandom(1.0));
    fill = shared_ptr<ShaderFill>(_fill);
    
    return fill;
}

void SquareLoopAnimator::update(Conductor& conductor) {
    conductor.clear();
    
    float cx = BUFF_WIDTH / 2;
    float cy = BUFF_HEIGHT / 2;
    float span = float(BUFF_WIDTH) / (fills.size() - 1) / 2;
    float maxSize = span * fills.size();
    for (int i = 0; i < fills.size(); i ++) {
        float size = fmod(i * span + frameCount * span / 60 , maxSize);
        size = pow(size / maxSize, 2) * maxSize;
        float x = cx - size;
        float y = cy - size;
        float w = size * 2;
        float h = size * 2;
        
        ofPolyline polyline = PolyLineUtil::rectangle(x, y, w, h);
        shared_ptr<Tool> tool = shared_ptr<Tool>(new ShaderFillTool(canvas, size, fills[i], polyline));
        conductor.addTool(tool);
    }
    
    frameCount += animationDebugFlag? 1 : 1;
    if (frameCount > 6000) {
        exit(0);
    }
}


float SquareLoopAnimator::powerInOut(float t, float a) {
    t = max(0.f, min(t, 1.f));
    if (t < 0.5) {
      return pow(t * 2, a) * 0.5;
    } else {
      return 1.0 - pow((1 - t) * 2, a) * 0.5;
    }
}

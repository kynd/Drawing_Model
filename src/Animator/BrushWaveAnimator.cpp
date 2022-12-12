#include "BrushWaveAnimator.hpp"

void BrushWaveAnimator::init(shared_ptr<ofFbo> _canvas) {
    canvas = _canvas;
    colorSampler.load("img/26.jpg");
 
    for (int i = 0; i < n; i ++) {
        BrushColorDef colorDef;
        colorDef.cbl = colorSampler.getRandomColor();
        colorDef.cbr = colorSampler.getRandomColor();
        colorDef.cel = colorSampler.getRandomColor();
        colorDef.cer = colorSampler.getRandomColor();
        colorDefs.push_back(colorDef);
    }
    
    background = colorSampler.getRandomColor();
}

void BrushWaveAnimator::update(Conductor& conductor) {
    conductor.clear();
    
    canvas->begin();
    ofClear(background);
    canvas->end();
    
    float span = float(BUFF_WIDTH) / (n);
    float mult = sin(PI * float(frameCount) / 150);
    for (int i = 0; i < n; i ++) {
        float lMult = sin(PI * float(i) / (n - 1) + float(frameCount) / 25);
        int hn = BUFF_HEIGHT / 10;
        ofPolyline lineA, lineB;
        for (int j = 0; j <= hn; j ++) {
            float t = float(j) / hn + float(i) / n + float(frameCount) / 50;
            float y = 1 + (BUFF_HEIGHT - 20) * float(j) / hn;
            float dx = sin(t * TWO_PI * (2 + lMult)) * mult * lMult;
            float lx = span * (i + 1) + dx * span - span;
            float rx = span * (i + 1) + dx * span;
            lineA.curveTo(ofVec3f(lx, y, 0));
            lineB.curveTo(ofVec3f(rx, y, 0));
            if (j == 0 || j == hn) {
                lineA.curveTo(ofVec3f(span * (i + 1) + dx * span * 0.5, y, 0));
                lineB.curveTo(ofVec3f(span * (i + 1) - dx * span * 0.5, y, 0));
            }
        }
            
        shared_ptr<Tool> tool = shared_ptr<Tool>(new DragStrokeTool(canvas, 0, lineA, lineB, colorDefs[i].cbl, colorDefs[i].cbr, colorDefs[i].cel, colorDefs[i].cer, background));
        conductor.addTool(tool);
    }
    
    frameCount += animationDebugFlag? 1 : 1;
    if (frameCount > 600) {
        exit(0);
    }
}

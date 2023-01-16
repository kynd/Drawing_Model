#include "WaveTideActor.hpp"

bool WaveFill::initialized = false;
ColorSampler WaveFill::colorSampler;

WaveFill::WaveFill() {
    if (!initialized) {
        colorSampler.load(COMMON_COLOR_SOURCE);
        initialized = true;
    }
    ofFloatColor colorA = colorSampler.getRandomColor();
    ofFloatColor colorB = colorSampler.getRandomColor();
    ofVec2f dir = VectorUtil::randomVec2();
    float breadth = ofRandom(1.0);
    float center = ofRandom(1.0);
    priority = ofRandom(10);
    
    float rnd = ofRandom(22.0);
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
    } else {
        fill = shared_ptr<ShaderFill>(new MetalicGradientShaderFill(colorA, colorB, dir, ofRandom(1.0), ofRandom(1.0)));
    }
}



shared_ptr<Tool> WaveFill::linesToTool(shared_ptr<ofFbo> canvas, ofPolyline lA, ofPolyline lB) {
    ofPolyline line;
    int res = 240;
    for (int i = 0; i < res; i ++) {
        float t = float(i) / (res - 1);
        ofVec3f p = lA.getPointAtPercent(t);
        line.addVertex(p);
    }
    
    for (int i = res - 1; i >= 0 ; i --) {
        float t = float(i) / (res - 1);
        ofVec3f p = lB.getPointAtPercent(t);
        line.addVertex(p);
    }
    line.close();
    
    auto tool = shared_ptr<Tool>(new ShaderFillTool(canvas, priority, fill, line));
    return tool;
}




WaveTideActor::WaveTideActor() {
    for(int i = 0; i < nLines; i ++) {
        basePoints.push_back(w / nLines * i);
    }
    
    for(int i = 0; i < nLines - 1; i ++) {
        wavefills.push_back(WaveFill());
    }
}

void WaveTideActor::update() {
    float offX = (BUFF_WIDTH - w) * 0.5;
    float offY = (BUFF_HEIGHT - h) * 0.5;
    
    for (int i = 0; i < nLines; i ++) {
        basePoints[i] += w / nLines / stepLength;
    }
    if (basePoints[nLines - 1] > w) {
        float temp = basePoints[nLines - 1];
        basePoints.pop_back();
        basePoints.insert(basePoints.begin(), 0);
        wavefills.pop_back();
        wavefills.insert(wavefills.begin(), WaveFill());
    }
    
    lines.clear();
    for (int i = 0; i < nLines; i ++) {
        ofVec3f pa(offX + basePoints[i], offY);
        ofVec3f pb(offX + basePoints[i], BUFF_HEIGHT - offY);
        ofPolyline line;
        line.addVertex(pa);
        int res = 24;
        for (int j = 0; j < res; j ++) {
            float t = float(j) / (res - 1);
            ofVec3f p = pa.getInterpolated(pb, t);
            float baseXStep = w / nLines;
            
            float sn = sin((float(frameCount) / stepLength + p.x / baseXStep) * PI * 0.5);
            p.x += sn * w / nLines * 0.25;
            
            float ns0 = t * 2.0;
            float ns1 = float(p.x) * 0.001 + float(frameCount) * 0.005;
            float n = ofSignedNoise(ns0, ns1);
            p.x += n * baseXStep * 0.2;
            
            line.curveTo(p);
        }
        
             
        line.addVertex(pb);
        lines.push_back(line);
    }
    
    
    frameCount ++;
}

void WaveTideActor::updateConductor(shared_ptr<ofFbo> canvas, Conductor& conductor) {
    for(int i = 0; i < nLines - 1; i ++) {
        auto tool = wavefills[i].linesToTool(canvas, lines[i], lines[i + 1]);
        conductor.addTool(tool);
    }
}

void WaveTideActor::drawMain() {
    ofNoFill();
    //ofTranslate(BUFF_WIDTH * 0.5, BUFF_HEIGHT * 0.5);
    //ofDrawRectangle(-BUFF_WIDTH * 0.5 + 16, -BUFF_HEIGHT * 0.5 + 16, BUFF_WIDTH - 32, BUFF_HEIGHT - 32);
    
    for (int i = 0; i < nLines; i ++) {
        lines[i].draw();
    }
    
}


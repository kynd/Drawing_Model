#include "WavePhysicsAnimator.hpp"

void WavePhysicsAnimator::init(shared_ptr<ofFbo> _canvas) {
    canvas = _canvas;
    colorSampler.load("img/26.jpg");
    initWave();
}


void WavePhysicsAnimator::initWave() {
    
    up.clear();
    for (int i = 0; i < 3; i ++) {
        vector<float> pts;
        int n = BUFF_WIDTH / 32;
        for (int j = 0; j < n; j ++) {
            pts.push_back(0.0);
        }
        up.push_back(pts);
    }
    
    colorA = colorSampler.getRandomColor();
    colorB = colorSampler.getRandomColor();
    colorC = colorSampler.getRandomColor();
    colorD = colorSampler.getRandomColor();
    colorE = colorSampler.getRandomColor();
    dirA = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
    dirB = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
}

void WavePhysicsAnimator::update(Conductor& conductor) {

    int nLoop = animationDebugFlag? 1 : 8;
    int iN, iC, iP;
    for (int i = 0; i < nLoop; i ++) {
        int f = frameCount;
        iN = (f + 1) % 3; // Next (t + 1)
        iC = f % 3; // Current (t)
        iP = (f + 2) % 3; // Previous (t - 1)

        updateSimulation(iN, iC, iP);
        
        frameCount ++;
    }
    
    createTools(iN, conductor);
    
    if (frameCount > 6000) {
        exit(0);
    }
}


void WavePhysicsAnimator::updateSimulation(int iN, int iC, int iP) {
    
    up[iC][0] += ofSignedNoise(frameCount * 0.01) * BUFF_HEIGHT / 750;
    for (int i = 0; i < up[0].size(); i ++) {
        float dhdx = 0;
        if (i != 0 && i != up[0].size() - 1) {
            dhdx = up[iC][i - 1] + up[iC][i + 1] - 2 * up[iC][i];
        }
        float c2 = 0.1;
        float dampen = 0.996;
        up[iN][i] = 2 * up[iC][i] + c2 * dhdx - up[iP][i];
        up[iN][i] *= dampen;
    }
}

void WavePhysicsAnimator::createTools(int iN, Conductor& conductor) {
    float cy = BUFF_HEIGHT * 0.5;
    conductor.clear();
    
    float span = float(BUFF_WIDTH) / (up[0].size() - 2);
    {
        ofPolyline polyline;
        polyline.addVertex(ofVec3f(0, up[iN][0] + cy, 0));
        for (int i = 0; i < up[0].size(); i ++) {
            polyline.curveTo(ofVec3f(span * i, up[iN][i] + cy + ofRandom(-4, 4), 10));
        }
        //shared_ptr<Tool> tool = shared_ptr<Tool>(new StrokeTool(canvas, 0, polyline, 2, colorE));
        //conductor.addTool(tool);
    }
    
    {
        ofPolyline polyline;
        polyline.addVertex(ofVec3f(0, 0, 0));
        polyline.lineTo(ofVec3f(0, up[iN][0] + cy, 0));
        for (int i = 0; i < up[0].size(); i ++) {
            polyline.curveTo(ofVec3f(span * i, up[iN][i] + cy, 0));
        }
        polyline.lineTo(ofVec3f(BUFF_WIDTH, 0, 0));
        polyline.lineTo(ofVec3f(0, 0, 0));
        polyline.close();
        shared_ptr<ShaderFill> fill = shared_ptr<ShaderFill>(new NoiseGradientShaderFill(colorA, colorB, dirA));
        dirA.rotate(0.1);
        shared_ptr<Tool> tool = shared_ptr<Tool>(new ShaderFillTool(canvas, 10, fill, polyline));
        conductor.addTool(tool);
    }
    
    {
        ofPolyline polyline;
        polyline.addVertex(ofVec3f(0, BUFF_HEIGHT, 0));
        polyline.lineTo(ofVec3f(0, up[iN][0] + cy, 0));
        for (int i = 0; i < up[0].size(); i ++) {
            polyline.curveTo(ofVec3f(span * i, up[iN][i] + cy, 0));
        }
        polyline.lineTo(ofVec3f(BUFF_WIDTH, BUFF_HEIGHT, 0));
        polyline.lineTo(ofVec3f(0, BUFF_HEIGHT, 0));
        shared_ptr<ShaderFill> fill = shared_ptr<ShaderFill>(new PaintPatchShaderFill(colorC, colorD, dirB));
        dirB.rotate(0.2);
        shared_ptr<Tool> tool = shared_ptr<Tool>(new ShaderFillTool(canvas, 10, fill, polyline));
        conductor.addTool(tool);
    }
}

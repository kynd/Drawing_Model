#include "BlobDanceAnimator.hpp"

void BlobDanceAnimator::init(shared_ptr<ofFbo> _canvas) {
    canvas = _canvas;
    colorSampler.load("img/26.jpg");
    initShapes();
}


void BlobDanceAnimator::initShapes() {
    
    lines.clear();
    int vn = 8;
    for (int i = 0; i < vn; i ++) {
        float cy = BUFF_HEIGHT * 1.5 / vn * i;
        vector<float> pts;
        int hn = BUFF_WIDTH / 64;
        for (int j = 0; j < hn; j ++) {
            pts.push_back(ofSignedNoise(j * 0.1 + i) * BUFF_HEIGHT / vn);
        }
        lines.push_back(pts);
    }
    
    colors[0] = colorSampler.getRandomColor();
    colors[1] = colorSampler.getRandomColor();
    colors[2] = colorSampler.getRandomColor();
    colors[3] = colorSampler.getRandomColor();
    colors[4] = colorSampler.getRandomColor();
    dirA = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
    dirB = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
}

void BlobDanceAnimator::update(Conductor& conductor) {
    conductor.clear();
    for (int i = 0; i < lines.size(); i ++) {
        ofPolyline polyline;
        float loopHeight = BUFF_HEIGHT * 1.5;
        float t = powerInOut(fmod(float(frameCount) / 180, 1.f));
        float offsetY = fmod(t * loopHeight + loopHeight / lines.size() * i, loopHeight) - BUFF_HEIGHT * 0.25;
        //cout << offsetY << "/" << loopHeight << ", ";
        float span = float(BUFF_WIDTH) / (lines[i].size() - 2);
        polyline.addVertex(ofVec3f(0, lines[i][0] + offsetY, 0.0));
        for (int j = 0; j < lines[i].size(); j ++) {
            polyline.curveTo(ofVec3f(span * j, lines[i][j] + offsetY,  0.0));
        }
        //shared_ptr<Tool> tool = shared_ptr<Tool>(new StrokeTool(canvas, 0, polyline, 2, colors[i % 5]));
       // conductor.addTool(tool);
    }
    //cout << &endl;//
    
    frameCount += animationDebugFlag? 1 : 2;
    if (frameCount > 6000) {
        exit(0);
    }
}


float BlobDanceAnimator::powerInOut(float t, float a) {
    t = max(0.f, min(t, 1.f));
    if (t < 0.5) {
      return pow(t * 2, a) * 0.5;
    } else {
      return 1.0 - pow((1 - t) * 2, a) * 0.5;
    }
}

#pragma once

#include "Animator.hpp"


class BlobDanceAnimator : public Animator {
public:
    void init(shared_ptr<ofFbo> _canvas);
    void initShapes();
    void update(Conductor& conductor);
    float powerInOut(float t, float a = 2);
private:
    int frameCount = 0;
    shared_ptr<ofFbo> canvas;
    ColorSampler colorSampler;
    ofFloatColor colors[5];
    ofVec2f dirA, dirB;
    
    vector<vector<float> > lines;
    
};

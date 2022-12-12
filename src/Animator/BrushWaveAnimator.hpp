#pragma once

#include "Animator.hpp"

struct BrushColorDef {
    ofFloatColor cbl;
    ofFloatColor cbr;
    ofFloatColor cel;
    ofFloatColor cer;
};

class BrushWaveAnimator : public Animator {
public:
    void init(shared_ptr<ofFbo> _canvas);
    void update(Conductor& conductor);
private:
    int n = 24;
    int frameCount = 0;
    shared_ptr<ofFbo> canvas;
    vector<BrushColorDef> colorDefs;
    ofFloatColor background;
    ColorSampler colorSampler;
};

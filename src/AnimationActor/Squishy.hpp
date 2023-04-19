#pragma once

#include "ofMain.h"
#include "common_includes.h"

class Squishy {
    
    public:
    Squishy(vector<float> o);
    static Squishy rounded(float s);
    static Squishy rect(float w, float h);
    void react(Squishy& s);
    
    void calcBounds(Squishy& s, float amt = 1.0);
    ofVec2f getSidePoint(int i);
    float getBoundOffset(ofVec2f p);
    void updateOffset();
    
    ofRectangle getBounds();
    void update();
    void draw();
    
    ofVec2f paintDir;
    ofFloatColor colorA, colorB;

    ofRectangle bounds;
    static int res;
    vector<float> offsetBase, offset, offsetBuff;
    vector<bool> squishMark;
    ofVec2f pos, vel;
    vector<ofVec2f> points;
    ofPolyline line;
    float weight = 1.0;
    shared_ptr<ShaderFill> fill;
    ToolUtil toolUtil;
};

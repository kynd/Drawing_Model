#pragma once

#include "ofMain.h"
class ColorSampler {
public:
    void load(string path);
    ofColor getRandomColor();
    ofImage img;
};

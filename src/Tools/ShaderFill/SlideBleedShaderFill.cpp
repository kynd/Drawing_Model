#include "SlideBleedShaderFill.hpp"


ofShader SlideBleedShaderFill::shader;
bool SlideBleedShaderFill::isInitialized = false;

SlideBleedShaderFill::SlideBleedShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir, int _nIterations) {
    if (!isInitialized) {
        initialize();
    }
    
    colorA = _colorA;
    colorB = _colorB;
    dir = _dir;
    nIterations = _nIterations == 0 ? 12 : _nIterations;
}

void SlideBleedShaderFill::initialize() {
    isInitialized = true;
    shader.load("shader/basic.vs", "shader/slideBleed/slideBleed.fs");
}

void SlideBleedShaderFill::begin() {
    shader.begin();
    shader.setUniform4f("colorA", colorA);
    shader.setUniform4f("colorB", colorB);
    shader.setUniform2f("dir", dir);
}

void SlideBleedShaderFill::end() {
    shader.end();
};

ofShader& SlideBleedShaderFill::getShader() {
    return shader;
}

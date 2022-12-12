#include "NoiseGradientShaderFill.hpp"


ofShader NoiseGradientShaderFill::shader;
bool NoiseGradientShaderFill::isInitialized = false;

NoiseGradientShaderFill::NoiseGradientShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir, float _center, float _breadth) {
    if (!isInitialized) {
        shader.load("shader/basic.vs", "shader/noiseGradientFill/noiseGradientFill.fs");
        isInitialized = true;
    }
    
    colorA = _colorA;
    colorB = _colorB;
    dir = _dir;
    center = ofVec2f(_center, 0.5);
    breadth = _breadth;
}

void NoiseGradientShaderFill::setRadial(ofVec2f _center, float _breadth) {
    isRadial = true;
    center = _center;
    breadth = _breadth;
};

void NoiseGradientShaderFill::begin() {
    shader.begin();
    shader.setUniform4f("colorA", colorA);
    shader.setUniform4f("colorB", colorB);
    shader.setUniform2f("dir", dir);
    shader.setUniform2f("center", center);
    shader.setUniform1f("breadth", breadth);
    shader.setUniform1i("isRadial", isRadial);
}

void NoiseGradientShaderFill::end() {
    shader.end();
};

ofShader& NoiseGradientShaderFill::getShader() {
    return shader;
}

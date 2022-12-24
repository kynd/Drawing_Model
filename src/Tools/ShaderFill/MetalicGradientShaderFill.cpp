#include "MetalicGradientShaderFill.hpp"


ofShader MetalicGradientShaderFill::shader;
bool MetalicGradientShaderFill::isInitialized = false;

MetalicGradientShaderFill::MetalicGradientShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir, float _center, float _breadth) {
    if (!isInitialized) {
        shader.load("shader/basic.vs", "shader/metalicGradientFill/metalicGradientFill.fs");
        isInitialized = true;
    }
    
    colorA = _colorA;
    colorB = _colorB;
    dir = _dir;
    center = ofVec2f(_center, 0.5);
    breadth = _breadth;
}

void MetalicGradientShaderFill::setRadial(ofVec2f _center, float _breadth) {
    isRadial = true;
    center = _center;
    breadth = _breadth;
};

void MetalicGradientShaderFill::begin() {
    shader.begin();
    shader.setUniform4f("colorA", colorA);
    shader.setUniform4f("colorB", colorB);
    shader.setUniform2f("dir", dir);
    shader.setUniform2f("center", center);
    shader.setUniform1f("breadth", breadth);
    shader.setUniform1i("isRadial", isRadial);
}

void MetalicGradientShaderFill::end() {
    shader.end();
};

ofShader& MetalicGradientShaderFill::getShader() {
    return shader;
}

#include "DotsShaderFill.hpp"


ofShader DotsShaderFill::shader;
bool DotsShaderFill::isInitialized = false;

DotsShaderFill::DotsShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir) {
    if (!isInitialized) {
        initialize();
        isInitialized = true;
    }
    
    colorA = _colorA;
    colorB = _colorB;
    dir = _dir;
}

void DotsShaderFill::initialize() {
    shader.load("shader/basic.vs", "shader/dots/dots.fs");

}

void DotsShaderFill::begin() {
    shader.begin();
    shader.setUniform4f("colorA", colorA);
    shader.setUniform4f("colorB", colorB);
    shader.setUniform2f("dir", dir);
}

void DotsShaderFill::end() {
    shader.end();
};

ofShader& DotsShaderFill::getShader() {
    return shader;
}

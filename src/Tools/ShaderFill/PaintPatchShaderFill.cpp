#include "PaintPatchShaderFill.hpp"


ofShader PaintPatchShaderFill::shader;
ofShader PaintPatchShaderFill::noiseShader;
ofFbo PaintPatchShaderFill::noise;
ofFbo PaintPatchShaderFill::dummy;
bool PaintPatchShaderFill::isInitialized = false;

PaintPatchShaderFill::PaintPatchShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir) {
    if (!isInitialized) {
        initialize();
        isInitialized = true;
    }
    
    colorA = _colorA;
    colorB = _colorB;
    dir = _dir;
}

void PaintPatchShaderFill::initialize() {
    shader.load("shader/basic.vs", "shader/paintPatch/paintPatch.fs");
    noiseShader.load("shader/basic.vs", "shader/paintPatch/noise.fs");
    noise.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    dummy.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    noise.begin();
    ofClear(0, 0, 0);
    noiseShader.begin();
    noiseShader.setUniform2f("res", BUFF_WIDTH, BUFF_HEIGHT);
    dummy.draw(0, 0);
    noiseShader.end();
    noise.end();
}

void PaintPatchShaderFill::begin() {
    shader.begin();
    shader.setUniform4f("colorA", colorA);
    shader.setUniform4f("colorB", colorB);
    shader.setUniform2f("dir", dir);
    shader.setUniformTexture("noise", noise, 2);
}

void PaintPatchShaderFill::end() {
    shader.end();
};

ofShader& PaintPatchShaderFill::getShader() {
    return shader;
}

#include "GradientStripeShaderFill.hpp"


ofShader GradientStripeShaderFill::shader;
ofShader GradientStripeShaderFill::noiseShader;
ofFbo GradientStripeShaderFill::noise;
ofFbo GradientStripeShaderFill::dummy;
bool GradientStripeShaderFill::isInitialized = false;

GradientStripeShaderFill::GradientStripeShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir) {
    if (!isInitialized) {
        initialize();
        isInitialized = true;
    }
    
    colorA = _colorA;
    colorB = _colorB;
    dir = _dir;
}

void GradientStripeShaderFill::initialize() {
    shader.load("shader/basic.vs", "shader/gradientStripe/gradientStripe.fs");
    noiseShader.load("shader/basic.vs", "shader/gradientStripe/noise.fs");
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

void GradientStripeShaderFill::begin() {
    shader.begin();
    shader.setUniform4f("colorA", colorA);
    shader.setUniform4f("colorB", colorB);
    shader.setUniform2f("dir", dir);
    shader.setUniformTexture("noise", noise, 2);
}

void GradientStripeShaderFill::end() {
    shader.end();
};

ofShader& GradientStripeShaderFill::getShader() {
    return shader;
}

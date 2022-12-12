#include "WaterBleedShaderFill.hpp"


ofShader WaterBleedShaderFill::shader;
ofShader WaterBleedShaderFill::noiseShader;
ofShader WaterBleedShaderFill::blurShader;
ofFbo WaterBleedShaderFill::noise;
ofFbo WaterBleedShaderFill::dummy;
bool WaterBleedShaderFill::isInitialized = false;

WaterBleedShaderFill::WaterBleedShaderFill(ofColor _colorA, ofColor _colorB, ofVec2f _dir, int _nIterations) {
    if (!isInitialized) {
        initialize();
    }
    
    colorA = _colorA;
    colorB = _colorB;
    dir = _dir;
    nIterations = _nIterations == 0 ? 12 : _nIterations;
}

void WaterBleedShaderFill::initialize() {
    isInitialized = true;
    shader.load("shader/basic.vs", "shader/waterBleed/waterBleed.fs");
    noiseShader.load("shader/basic.vs", "shader/waterBleed/noise.fs");
    blurShader.load("shader/basic.vs", "shader/waterBleed/blur.fs");
    noise.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    dummy.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    
    noise.begin();
    ofClear(0, 0, 0, 0);
    noiseShader.begin();
    noiseShader.setUniform2f("res", BUFF_WIDTH, BUFF_HEIGHT);
    dummy.draw(0, 0);
    noiseShader.end();
    noise.end();
}

void WaterBleedShaderFill::preprocess(ofFbo fbo) {
    blurDummy.allocate(fbo.getWidth(), fbo.getHeight(), fboDepth, samplingDepth);
    blur.allocate(fbo.getWidth(), fbo.getHeight(), fboDepth, samplingDepth);
    
    blurDummy.begin();
    ofClear(0, 0, 0, 0);
    blurShader.begin();
    blurShader.setUniform2f("dir", ofVec2f(1, 0));
    fbo.draw(0,0);
    blurShader.end();
    blurDummy.end();
    
    blur.begin();
    ofClear(0, 0, 0, 0);
    blurShader.begin();
    blurShader.setUniform2f("dir", ofVec2f(0, 1));
    blurDummy.draw(0,0);
    blurShader.end();
    blur.end();
}

void WaterBleedShaderFill::begin() {
    shader.begin();
    shader.setUniform4f("colorA", colorA);
    shader.setUniform4f("colorB", colorB);
    shader.setUniform2f("dir", dir);
    shader.setUniformTexture("blur", blur, 3);
    shader.setUniformTexture("noise", noise, 4);
}

void WaterBleedShaderFill::end() {
    shader.end();
};

ofShader& WaterBleedShaderFill::getShader() {
    return shader;
}

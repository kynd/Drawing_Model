
#include "RoughEdgeStrokeStyle.hpp"


bool RoughEdgeStrokeStyle::isInitialized;
ofShader RoughEdgeStrokeStyle::shader;
ofShader RoughEdgeStrokeStyle::printShader;
ofShader RoughEdgeStrokeStyle::noiseShader;
ofFbo RoughEdgeStrokeStyle::noise;
ofFbo RoughEdgeStrokeStyle::dummy;

RoughEdgeStrokeStyle::RoughEdgeStrokeStyle(ofFloatColor _color) {
    color = _color;
    if (!isInitialized) {
        initialize();
    }
}

void RoughEdgeStrokeStyle::initialize() {
    isInitialized = true;
    shader.load("shader/basic.vs", "shader/roughEdgeStroke/stroke.fs");
    printShader.load("shader/basic.vs", "shader/roughEdgeStroke/print.fs");
    noiseShader.load("shader/basic.vs", "shader/roughEdgeStroke/noise.fs");
    
    noise.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    dummy.allocate(BUFF_WIDTH, BUFF_HEIGHT, fboDepth, samplingDepth);
    
    noise.begin();
    ofClear(0, 0, 0, 255);
    noiseShader.begin();
    noiseShader.setUniform2f("res", BUFF_WIDTH, BUFF_HEIGHT);
    dummy.draw(0, 0);
    noiseShader.end();
    noise.end();
}

ofShader& RoughEdgeStrokeStyle::getShader() {
    return shader;
}
ofShader& RoughEdgeStrokeStyle::getPrintShader() {
    return printShader;
}

ofFloatColor RoughEdgeStrokeStyle::getDebugColor() {
    return color;
}

void RoughEdgeStrokeStyle::begin() {
    shader.begin();
    shader.setUniform4f("color", color);
}

void RoughEdgeStrokeStyle::end() {
    shader.end();
};


void RoughEdgeStrokeStyle::beginPrint() {
    printShader.begin();
    printShader.setUniformTexture("noise", noise, 2);
    printShader.setUniform4f("color", color);
};

void RoughEdgeStrokeStyle::endPrint() {
    printShader.end();
};

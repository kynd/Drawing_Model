
#include "BasicStrokeStyle.hpp"


bool BasicStrokeStyle::isInitialized;
ofShader BasicStrokeStyle::shader;
ofShader BasicStrokeStyle::printShader;

BasicStrokeStyle::BasicStrokeStyle(ofFloatColor _color) {
    color = _color;
    if (!isInitialized) {
        isInitialized = true;
        shader.load("shader/basic.vs", "shader/stroke/stroke.fs");
        printShader.load("shader/basic.vs", "shader/stroke/print.fs");
    }
}

ofShader& BasicStrokeStyle::getShader() {
    return shader;
}
ofShader& BasicStrokeStyle::getPrintShader() {
    return printShader;
}

ofFloatColor BasicStrokeStyle::getDebugColor() {
    return color;
}

void BasicStrokeStyle::begin() {
    shader.begin();
    shader.setUniform4f("color", color);
}

void BasicStrokeStyle::end() {
    shader.end();
};


void BasicStrokeStyle::beginPrint() {
    printShader.begin();
    printShader.setUniform4f("color", color);
};

void BasicStrokeStyle::endPrint() {
    printShader.end();
};
